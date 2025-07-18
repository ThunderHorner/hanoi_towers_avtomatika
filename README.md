# Towers of Hanoi Visualization

🗼 Animated terminal visualization of the classic **Towers of Hanoi puzzle**, with smooth animations, configurable speed, and beautifully aligned, colored donuts.

---

### ✨ Features
- Fully animated visualization in terminal
- Smooth "fly-over" movement for donuts
- Bright, readable colors with perfect centering
- Configurable speed (levels 1–10)
- Dynamic layout based on donut count

---

### 📝 Author
Kostadin Slavov a.k.a ThunderHorn  
Fakultet Avtomatika; Grupa 91; Faculteten Nomer: 012224011  
Version: 1.0

---

### ⚙️ Requirements
- Standard C compiler (e.g. `gcc`)
- POSIX terminal (supports ANSI escape codes)

---

### 🔧 Build
```bash
gcc -Wall -o hanoi main.c
```

Or with a `Makefile` (optional):
```bash
make
```

---

### 🚀 Run
```bash
./hanoi
```

At startup, you will be prompted to select speed:
```
Select speed (1=slowest, 10=fastest):
```

---

### 🔩 Configuration
You can adjust these constants in `hanoi.h`:

| Constant | Purpose |
| -------- | ------- |
| DONUT_COUNT | Number of donuts (default 10) |
| TOWER_COUNT | Number of towers (default 3) |
| SPEED_MIN_DELAY_US / SPEED_MAX_DELAY_US | Animation delay bounds |
| TOWER_SPACING_COLUMNS | Horizontal spacing between towers |
| DONUT_MIN_VISUAL_WIDTH | Minimum donut width in columns |
| DONUT_WIDTH_INCREMENT | Width increment per donut |

---

### 🖋️ Notes
- This project emphasizes clean code style following "Uncle Bob" principles:
    - Self-explanatory function and variable names
    - No cryptic magic numbers
    - Well-structured header and implementation files

---

### ❤️ License
MIT License  
Feel free to use, modify, and share.
