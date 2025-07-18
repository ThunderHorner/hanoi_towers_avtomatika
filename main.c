#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "hanoi.h"


int SPEED_LEVEL = 5;

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

int compute_animation_delay() {
    int animation_range = SPEED_MAX_DELAY_US - SPEED_MIN_DELAY_US;
    return SPEED_MAX_DELAY_US - ((SPEED_LEVEL - 1) * animation_range / 9);
}

void initialize_towers(struct TOWER towers[TOWER_COUNT]) {
    for (int tower_index = 0; tower_index < TOWER_COUNT; tower_index++) {
        for (int donut_index = 0; donut_index < DONUT_COUNT; donut_index++) {
            towers[tower_index].donuts[donut_index].width = (tower_index == 0) ? donut_index : -1;
        }
    }
}

int locate_top_donut(struct TOWER tower) {
    for (int position = 0; position < DONUT_COUNT; position++) {
        if (tower.donuts[position].width != -1) return position;
    }
    return -1;
}

int locate_empty_slot(struct TOWER tower) {
    for (int position = DONUT_COUNT - 1; position >= 0; position--) {
        if (tower.donuts[position].width == -1) return position;
    }
    return -1;
}

int compute_tower_center_column(int tower_index) {
    return TOWER_BASE_OFFSET + TOWER_SPACING_COLUMNS * tower_index;
}

void render_donut_at_column(int center_column, int donut_width, int color_code) {
    int visual_width = DONUT_MIN_VISUAL_WIDTH + DONUT_WIDTH_INCREMENT * donut_width;
    int starting_column = center_column - (visual_width / 2);

    printf("\033[%dG", starting_column + 1);
    printf("\033[38;5;%dm", color_code);
    printf("[");
    for (int fill_index = 0; fill_index < visual_width - 2; fill_index++) printf("=");
    printf("]");
    printf("\033[0m");
}

void render_frame(struct TOWER towers[TOWER_COUNT], struct DONUT *floating_donut, int floating_row, int floating_column) {
    clear_screen();

    printf("[ TOWERS OF HANOI ]\n");
    printf("Author: %s\n", AUTHOR);
    printf("TAGS: %s\n", TAGS);
    printf("Version: %s\n", VERSION);
    printf("Speed Level: %d\n\n", SPEED_LEVEL);

    int frame_height = DONUT_COUNT + FRAME_EXTRA_ROWS;
    int max_visual_width = DONUT_MIN_VISUAL_WIDTH + DONUT_WIDTH_INCREMENT * (DONUT_COUNT - 1);

    for (int row_index = frame_height + 2; row_index >= 0; row_index--) {
        for (int tower_index = 0; tower_index < TOWER_COUNT; tower_index++) {
            int tower_center = compute_tower_center_column(tower_index);
            int leftmost_column = tower_center - max_visual_width / 2;

            printf("\033[%dG", leftmost_column + 1);

            if (row_index == 0) {
                for (int col = 0; col < max_visual_width; col++) printf("-");
            } else if (row_index <= frame_height) {
                int donut_width = -1;
                if (row_index <= DONUT_COUNT) {
                    donut_width = towers[tower_index].donuts[DONUT_COUNT - row_index].width;
                }

                if (donut_width == -1) {
                    for (int col = 0; col < max_visual_width; col++) {
                        printf(col == max_visual_width / 2 ? "|" : " ");
                    }
                } else {
                    int color_code = 196 + (donut_width * 5) % 36;
                    if (color_code > 231) color_code = 231;
                    render_donut_at_column(tower_center, donut_width, color_code);
                }
            } else {
                for (int col = 0; col < max_visual_width; col++) printf(" ");
            }
        }

        if (floating_donut && row_index == floating_row) {
            int color_code = 196 + (floating_donut->width * 5) % 36;
            if (color_code > 231) color_code = 231;
            render_donut_at_column(floating_column, floating_donut->width, color_code);
        }

        printf("\n");
    }
}

void render_towers(struct TOWER towers[TOWER_COUNT]) {
    render_frame(towers, NULL, -1, -1);
    usleep(STATIC_DELAY_US);
}

void animate_move(struct TOWER towers[TOWER_COUNT], int source_tower, int target_tower) {
    int src_top = locate_top_donut(towers[source_tower]);
    int tgt_empty = locate_empty_slot(towers[target_tower]);

    if (src_top == -1 || tgt_empty == -1) return;

    int tgt_top = locate_top_donut(towers[target_tower]);
    if (tgt_top != -1 &&
        towers[source_tower].donuts[src_top].width > towers[target_tower].donuts[tgt_top].width)
        return;

    struct DONUT moving_donut = towers[source_tower].donuts[src_top];
    towers[source_tower].donuts[src_top].width = -1;

    int src_row = DONUT_COUNT - src_top;
    int tgt_row = DONUT_COUNT - tgt_empty;
    int peak_row = DONUT_COUNT + PEAK_HEIGHT_OFFSET;
    int fly_over_row = DONUT_COUNT + FRAME_EXTRA_ROWS + 1;
    int delay = compute_animation_delay();

    int src_col = compute_tower_center_column(source_tower);
    int tgt_col = compute_tower_center_column(target_tower);
    int step = (tgt_col > src_col) ? 1 : -1;

    for (int row = src_row; row <= peak_row; row++)
        render_frame(towers, &moving_donut, row, src_col), usleep(delay);

    for (int col = src_col; col != tgt_col; col += step)
        render_frame(towers, &moving_donut, fly_over_row, col), usleep(delay * 2);

    for (int row = peak_row; row >= tgt_row; row--)
        render_frame(towers, &moving_donut, row, tgt_col), usleep(delay);

    towers[target_tower].donuts[tgt_empty] = moving_donut;
    render_towers(towers);
}

void solve_hanoi(struct TOWER towers[TOWER_COUNT], int donut_count, int src_tower, int aux_tower, int tgt_tower) {
    if (!donut_count) return;

    solve_hanoi(towers, donut_count - 1, src_tower, tgt_tower, aux_tower);
    animate_move(towers, src_tower, tgt_tower);
    solve_hanoi(towers, donut_count - 1, aux_tower, src_tower, tgt_tower);
}

int main() {
    struct TOWER towers[TOWER_COUNT];

    printf("Select speed (1=slowest, 10=fastest): ");
    scanf("%d", &SPEED_LEVEL);
    if (SPEED_LEVEL < 1) SPEED_LEVEL = 1;
    if (SPEED_LEVEL > 10) SPEED_LEVEL = 10;

    initialize_towers(towers);
    render_towers(towers);
    sleep(1);

    solve_hanoi(towers, DONUT_COUNT, 0, 1, 2);

    printf("\n*** PUZZLE SOLVED! ***\n\n");
}
