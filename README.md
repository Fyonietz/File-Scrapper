
---

# 📂 File-Scrapper

**File-Scrapper** is a modern C++ utility for scraping files from a given directory and exporting the results to a specified output file. It’s lightweight, easy to integrate, and comes with sample code to help you get started quickly.

---

## 🚀 Features

* ✅ Scrape all files from a specified directory
* ✅ Save results to a custom output file
* ✅ Easy-to-follow sample code and scripts
* ✅ Fast and efficient C++ implementation
* ✅ Cross-platform support (Windows & Linux)
* ✅ GUI file dialogs using tinyfiledialogs

---

## 🛠️ Technology Stack

* **C++** – Core language for high-performance file operations
* **tinyfiledialogs** – Cross-platform file dialog library
* **nlohmann/json** – Modern JSON library for C++
* **CMake** – Cross-platform build automation support
* **GTK3** – GUI toolkit for Linux file dialogs

---

## 📁 Usage

### Prerequisites

**For Linux:**
- CMake (version 3.10 or higher)
- GCC/G++ compiler
- GTK3 development libraries
- pkg-config

**Quick Installation:**
```bash
# Use the provided script to install dependencies automatically
./scripts/install-deps.sh

# Verify your system meets all requirements
./scripts/check-system.sh
```

**Manual Installation:**

Install dependencies on Ubuntu/Debian:
```bash
sudo apt update
sudo apt install cmake build-essential libgtk-3-dev pkg-config
```

Install dependencies on Fedora/RHEL:
```bash
sudo dnf install cmake gcc-c++ gtk3-devel pkgconfig
```

Install dependencies on Arch Linux:
```bash
sudo pacman -S cmake gcc gtk3 pkgconf
```

**For Windows:**
- CMake
- Visual Studio or MinGW

### Building and Running

#### Quick Start (Linux)
```bash
# One-command setup, build, and run
./scripts/quick-start.sh
```

#### Manual Build Process

1. Clone the repository:

   ```bash
   git clone https://github.com/Fyonietz/File-Scrapper.git
   cd File-Scrapper
   ```

2. Build the project:

   **On Linux:**
   ```bash
   ./scripts/build.sh
   ```

   **On Windows:**
   ```bash
   cd .\scripts
   .\build.cmd
   ```

3. Run the application:

   **On Linux:**
   ```bash
   # GUI mode (file dialogs)
   ./scripts/start.sh
   
   # Command-line mode (for headless or when dialogs don't work)
   ./scripts/start.sh /path/to/input/folder /path/to/output.json
   
   # Direct execution
   ./Sea /path/to/input/folder /path/to/output.json
   ```

   **On Windows:**
   ```bash
   .\Sea 
   ```

---

## 🎯 Usage Modes

### GUI Mode
The default mode uses graphical file dialogs for folder and file selection:
```bash
./Sea
# or
./scripts/start.sh
```

### Command-Line Mode
For headless systems, automation, or when GUI dialogs don't work:
```bash
./Sea <input_folder> <output_file.json>

# Practical examples:
./Sea /usr/bin system_executables.json           # System binaries
./Sea ~/.local/bin user_apps.json                # User applications  
./Sea /opt opt_software.json                     # Optional software
./Sea /usr/games games.json                      # System games
./Sea ~/Applications local_apps.json             # macOS-style apps folder
```

**⚠️ Performance Tips:**
- Use specific directories rather than scanning the entire filesystem
- Avoid very broad paths like `/` or `../../` as they can be very slow
- For system-wide scans, use targeted directories like `/usr/bin`, `/usr/local/bin`

### Output Format
The application generates a JSON file with the following structure:
```json
{
    "app_lists": [
        {
            "application_name": {
                "app_location": "/full/path/to/executable",
                "app_image": "/Assets/icon/application_name.png"
            }
        }
    ]
}
```

**Behavior differences:**
- **Windows**: Searches for files with a specific extension (e.g., `.exe`)
- **Linux**: Searches for executable files (files with execute permission)

### Quick Example
```bash
# Run the example script to see File-Scrapper in action
./scripts/example.sh
```

---

## 🔧 Troubleshooting

### Linux Issues

**Issue: GUI dialogs not appearing or application hanging**
```bash
# Solution: Use command-line mode instead
./Sea /path/to/input/folder /path/to/output.json

# Or check if zenity is installed (required for GUI dialogs)
sudo apt install zenity        # Ubuntu/Debian
sudo dnf install zenity        # Fedora/RHEL
sudo pacman -S zenity          # Arch Linux
```

**Issue: Permission denied errors or very slow scanning**
```bash
# Solution: Use more specific directories instead of filesystem root
./Sea /usr/bin system_apps.json           # System executables
./Sea ~/.local/bin user_apps.json         # User applications
./Sea /opt apps_opt.json                  # Optional applications

# Avoid scanning very broad directories like:
# ./Sea / output.json                     # DON'T: scans entire filesystem
# ./Sea ../../ output.json                # DON'T: too broad scope
```

**Issue: "gtk+-3.0 not found" during build**
```bash
# Solution: Install GTK3 development libraries
sudo apt install libgtk-3-dev  # Ubuntu/Debian
sudo dnf install gtk3-devel    # Fedora/RHEL
sudo pacman -S gtk3            # Arch Linux
```

**Issue: "CMake version too old"**
```bash
# Solution: Install a newer version of CMake
sudo apt install cmake        # Usually installs latest from repos
# Or install from CMake official website for latest version
```

**Issue: "Permission denied" when running scripts**
```bash
# Solution: Make scripts executable
chmod +x scripts/*.sh
```

**Issue: "Sea executable not found"**
```bash
# Solution: Build the project first
./scripts/build.sh
```

### General Issues

**Issue: File dialogs not working on headless systems**
- File-Scrapper requires a GUI environment (X11/Wayland) to display file dialogs
- For headless systems, consider modifying the code to use command-line arguments instead

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

## 💡 Contributing

Pull requests and issues are welcome! Feel free to open discussions for new features or improvements.

---
### 👥 Contributors

[@DityaPerdana/File-Scrapper](https://github.com/DityaPerdana/File-Scrapper). << **Linux Version**

---
