# 🎮 Tank War

<div align="center">

```
████████╗ █████╗ ███╗   ██╗██╗  ██╗    ██╗    ██╗ █████╗ ██████╗ 
╚══██╔══╝██╔══██╗████╗  ██║██║ ██╔╝    ██║    ██║██╔══██╗██╔══██╗
   ██║   ███████║██╔██╗ ██║█████╔╝     ██║ █╗ ██║███████║██████╔╝
   ██║   ██╔══██║██║╚██╗██║██╔═██╗     ██║███╗██║██╔══██║██╔══██╗
   ██║   ██║  ██║██║ ╚████║██║  ██╗    ╚███╔███╔╝██║  ██║██║  ██║
   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝     ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝
```

*A classic artillery-style turn-based strategy game built in C++*

[![Language](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://www.microsoft.com/windows)
[![Made with Love](https://img.shields.io/badge/Made%20with-❤️-red?style=for-the-badge)](https://github.com)

</div>

---

## 📖 About

Tank War is a console-based artillery game where two players battle it out by calculating the perfect angle and velocity to destroy their opponent's tank. Featuring realistic parabolic projectile physics, dynamic terrain destruction, and explosive animations, this game brings classic turn-based tank warfare to your terminal!

### ✨ Key Features

- 🎯 **Physics-Based Projectile System**
  - Real parabolic trajectory calculations
  - Adjustable angle (0-180°) and velocity controls
  - Gravity-based projectile motion using kinematic equations

- 🗺️ **Procedural Terrain Generation**
  - Unique randomly generated battlefields every game
  - Seed-based terrain using sinusoidal wave functions
  - No two battles are ever the same!

- 💥 **Dynamic Terrain Destruction**
  - Terrain deforms on impact
  - Realistic blast radius
  - Explosive visual effects

- 🎨 **Colorful ASCII Graphics**
  - Beautiful colored console rendering
  - Detailed tank sprites with dynamic turret positioning
  - Animated explosions and projectile trails

- ⚙️ **Game Features**
  - Turn-based multiplayer (2 players)
  - Health and fuel management systems
  - Save/Load game functionality
  - Customizable controls
  - Visual aiming system
  - Real-time HUD with stats display

---

## 🎮 Gameplay

### Objective
Destroy your opponent's tank by accurately calculating projectile trajectories. Each player takes turns adjusting their tank's firing angle and projectile velocity to land the perfect shot!

### Game Mechanics

**Physics System:**
- The game uses real projectile motion formulas:
  - Range: `R = (v² × sin(2θ)) / g`
  - Max Height: `H = (v² × sin²θ) / (2g)`
  - Time of Flight: `T = (2v × sinθ) / g`
- Gravity constant: `9.81 m/s²`

**Turn Structure:**
1. Adjust your tank's position (uses fuel)
2. Set firing angle (0-180 degrees)
3. Set projectile velocity
4. Fire and watch the parabolic trajectory!
5. Terrain destruction occurs on impact

---

## 🎯 Controls

### Default Controls

| Action | Key |
|--------|-----|
| Move Tank Left | `←` Left Arrow |
| Move Tank Right | `→` Right Arrow |
| Increase Angle | `↑` Up Arrow |
| Decrease Angle | `↓` Down Arrow |
| Increase Velocity | `W` |
| Decrease Velocity | `S` |
| Fire! | `F` |
| Main Menu | `ESC` |

*Controls are fully customizable through the in-game settings menu!*

---

## 🚀 Getting Started

### Prerequisites

- Windows OS (uses Windows.h for console manipulation)
- C++ compiler (MinGW, MSVC, or similar)
- Terminal/Console with UTF-8 support

### Compilation

```bash
g++ main.cpp -o TankWar.exe
```

### Running the Game

```bash
./TankWar.exe
```

The game will launch in fullscreen mode automatically!

---

## 🏗️ Technical Details

### Project Structure

```
Tank-War/
│
├── main.cpp           # Complete game source code
├── savegame.dat       # Binary save file (generated at runtime)
├── controls.dat       # Custom control settings (generated at runtime)
└── README.md          # This file
```

### Core Components

**Data Structures:**
- `Tanks` struct: Stores tank properties (position, health, fuel, angle, velocity)
- `Controls` struct: Customizable key bindings
- `ground[]` array: Terrain height map (150 width)

**Key Systems:**
- **Rendering Engine**: Uses Windows Console API for colored output and cursor control
- **Terrain Generator**: Sine/cosine wave-based procedural generation with multiple seed variants
- **Physics Engine**: Kinematic equations for projectile motion
- **Collision Detection**: Character-based collision checking
- **Save System**: Binary file I/O for game state persistence

### Features in Detail

**Terrain System:**
- 150x34 character display area
- 11 different terrain seeds for variety
- Dynamic height calculation using wave functions
- Real-time terrain modification on projectile impact

**Tank System:**
- 7-character wide tank sprite
- Dynamic barrel angle visualization
- Turret adapts to terrain tilt (flat, upward, downward)
- Position-based on terrain height

**Projectile System:**
- Frame-by-frame trajectory calculation
- Visual bullet trail rendering
- Collision detection with terrain and enemy tanks
- Damage calculation based on proximity to impact

---

## 🎨 Screenshots

```
          ▄███████████████████████
        ▄███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓
      ▄███████████████████████████
    ▄██████████████████████████▀  
  ▄██████████████████████████▀    
 █▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█
 █  ▄▀▀▄  ▄▀▀▄  ▄▀▀▄  ▄▀▀▄  ▄▀▀▄  █
 ▀▄▄▀  ▀▄▄▀  ▀▄▄▀  ▀▄▄▀  ▀▄▄▀  ▀▄▄▀ 
```

---

## 🎓 Educational Value

This project demonstrates several important programming concepts:

- **Game Loop Architecture**: Event-driven input handling
- **2D Graphics**: Console-based rendering techniques
- **Physics Simulation**: Real-world projectile motion
- **Procedural Generation**: Algorithm-based content creation
- **Binary I/O**: Save/load system implementation
- **State Management**: Turn-based game flow
- **Collision Detection**: Spatial calculations
- **Memory Management**: Struct-based data organization

---

## 🔮 Future Enhancements

Potential features for future versions:
- [ ] AI opponent mode
- [ ] Power-ups and special ammunition
- [ ] Multiple terrain types (snow, desert, moon)
- [ ] Wind effects on projectiles
- [ ] Multiplayer over network
- [ ] Sound effects
- [ ] Replay system
- [ ] Tournament mode with bracket system

---

## 📝 Notes

- Game auto-saves when returning to main menu (ESC key)
- Save files are stored in the same directory as the executable
- Fullscreen mode is automatically enabled for best experience
- Terrain is regenerated for each new game

---

## 🤝 Contributing

This is a first-semester academic project, but suggestions and improvements are welcome! Feel free to fork the repository and submit pull requests.

---

## 📜 License

This project is open source and available for educational purposes.

---

## 👨‍💻 Author

Created as a first-semester C++ programming project.

---

<div align="center">

**Enjoy the battle! 🎯💥**

*"The trajectory of success requires precise calculations and explosive execution!"*

</div>
