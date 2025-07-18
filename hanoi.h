// hanoi.h
// Towers of Hanoi visualization
// Author: Kostadin Slavov a.k.a ThunderHorn
// Version: 1.0

#ifndef HANOI_H
#define HANOI_H

// Metadata
#define VERSION "1.0"
#define AUTHOR  "Kostadin Slavov a.k.a ThunderHorn"
#define TAGS    "Fakultet Avtomatika; Grupa 91; Faculteten Nomer: 012224011"

#define DONUT_COUNT              5
#define TOWER_COUNT              3
#define FRAME_EXTRA_ROWS         2
#define DONUT_MARGIN             2
#define SPEED_MIN_DELAY_US       5000
#define SPEED_MAX_DELAY_US       100000
#define STATIC_DELAY_US          20000
#define PEAK_HEIGHT_OFFSET       1

#define TOWER_SPACING_COLUMNS    20
#define TOWER_BASE_OFFSET        20
#define DONUT_MIN_VISUAL_WIDTH   3
#define DONUT_WIDTH_INCREMENT    2

extern int SPEED_LEVEL;

struct DONUT {
    int width;
};

struct TOWER {
    struct DONUT donuts[DONUT_COUNT];
};

void clear_screen(void);
void init_towers(struct TOWER towers[TOWER_COUNT]);
int find_top_donut(struct TOWER tower);
int find_empty_slot(struct TOWER tower);
void draw_frame(struct TOWER towers[TOWER_COUNT], struct DONUT *floating_donut, int floating_row, int floating_x);
void draw_towers(struct TOWER towers[TOWER_COUNT]);
void move_donut(struct TOWER towers[TOWER_COUNT], int source_tower, int target_tower);
void solve_hanoi(struct TOWER towers[TOWER_COUNT], int donut_count, int source_tower, int auxiliary_tower, int target_tower);

#endif // HANOI_H
