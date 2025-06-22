# ISLAH Framework

**ISLAH** is a lightweight template framework for developing cross-platform C++ applications using **SFML**.  
It aims to simplify app development by providing a clean screen/component architecture and avoiding GUI-related overhead — especially for game-style or graphics-heavy apps.

## Why ISLAH?

C++ is fast, SFML is powerful — but writing clean, structured GUI apps in SFML (especially cross-platform) is often messy. ISLAH helps by:

- Reducing boilerplate
- Simplifying screen and component management
- Providing a ready-to-go template with minimal performance cost

## Project Structure

```

islah/
│
├── src/                 # All C++ source files
│   ├── common/          # Common utilities (already written)
│   ├── components/      # UI/game components (extendable)
│   ├── screen/          # Scene/screen system (you implement here)
│   └── main.cpp         # Entry point (you can ignore)
│
├── include/             # Assets like fonts (copied with build)
├── built/               # Created by run.bat, contains your final .exe
├── run.bat              # Builds and runs the app (use this)
└── README.md

```

You don’t need to modify `main.cpp` or most core files unless necessary.

## How to Use

1. **Download the release ZIP** (recommended)  
   OR  
   Clone the repo (https://github.com/Muhammad-Ayyan-no1/ISLAH-app-Framework-TEMPLATE-sfml.git) if you want to contribute:

```

gh repo clone Muhammad-Ayyan-no1/ISLAH-app-Framework-TEMPLATE-sfml
```

--- ( OR ) ---

```
git clone https://github.com/Muhammad-Ayyan-no1/ISLAH-app-Framework-TEMPLATE-sfml.git
```

read the NOTE file if , in the cloned or downlaoded file
warning this repo uses IOSL license which prohibits unethical tasks using or with this repo and soo on

2. **Write your code**:

- Add scenes in `src/screen/`
- Add components in `src/components/`

3. **Double-click `run.bat`** on Windows:

- Compiles the app
- Creates the `built/` folder
- Copies assets from `include/` and runs the final `.exe`

You can delete the `built/` folder any time. It will be recreated by `run.bat`.

## Features

- No DLLs — completely static build
- Clean architecture using scenes and components
- Minimal external dependencies
- Cross-platform ready (with some setup)

## TODOs

This project started as a personal tool, now open to the community.  
A list of development goals can be found in the `TODO` file.

All contributions must follow the project’s ethical and legal guidelines.

## AI-Generated Code Policy

While some boilerplate and test code may have been generated with the help of language models, all final code is written or reviewed by a human developer.
(This readme file was rephrased by chatgpt 4o free version 6/22/2025)

## Versioning and Stability

This is an early version. Although it's technically "v1," it’s based on several prior internal iterations.

- The API may change frequently.
- Forks must comply with the license terms.
- Stability will improve after core APIs settle.

## Contributions

Forks, issues, and pull requests are welcome.  
Use it, build on it, and help improve it.
