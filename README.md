# VCMP Lua Plugin

As the name suggests, this plugin provides a scripting API for VCMP in Lua (yay!). Please check out the [WIKI](https://github.com/DizzasTeR/VCMP-Lua/wiki) to learn
about the structure of the plugin (its quite easy!)

## Purpose of this project

The purpose of this project is mainly that I love Lua, and I also love C++, therefore to keep my practice in C++ I decided to work on this plugin with one of my
favorite scripting languages (Lua).

# The Lua config file

In your server directory you should place a **luaconfig.ini** file which will allow you to specify some settings the plugin can use. Some of these settings are
optional while some (like specifying atleast 1 script file) is compulsory.

The file structure is as of right now very simple:

```ini
[config]
# Sets experimental mode ON (1) or OFF (0) | Intended for beta-testing and development only. Do not rely for stability
#experimental=1
# Sets the log level, See the Logger page on Wiki for more information
loglevel=0
# Sets the log file. This log file will be used to create daily logs and it will log everything logged by Logger class, regardless of level
logfile=DailyLogs.logs

[modules]
# This is the modules section, here you can opt in to use external modules that the plugin provides. They can be listed and toggled by setting them to a boolean

#moduleName=[true/false]
lanes=false

[scripts]
# This is the scripts section, here you can specify all your script files that you want to run.

# script=path/to/file.lua
script=lua/script.lua
```

# Building the Plugin

## Windows

To build on Windows, download the repository and run the `win-build.bat` file located in the `premake` folder. This will generate a Visual Studio 2022 solution file in the main folder. Open it with Visual Studio and compile using the appropriate configuration:

- **Release32 + Win32** → produces `LuaPlugin_x32.dll`
- **Release + x64** → produces `LuaPlugin_x64.dll`

---

## Linux

### 1. Install Required Dependencies

Run the following command to install the base build tools and libraries:

```bash
sudo apt install -y build-essential gcc g++ make gcc-multilib g++-multilib \
  libc6-dev libc6-dev-i386 zlib1g-dev zlib1g:i386 \
  libncurses6:i386 libtinfo6:i386 libssl-dev rpm
```

Then, install `libpq-dev` according to your **target architecture**:

> ⚠️ **Important:** `libpq-dev` and `libpq-dev:i386` conflict with each other. Install only the one that matches your desired target before compiling.

- For **x86 (32-bit)**:
```bash
  sudo apt install -y libpq-dev:i386
```

- For **x64 (64-bit)**:
```bash
  sudo apt install -y libpq-dev
```

---

### 2. Install Premake5

```bash
cd ~
wget https://github.com/premake/premake-core/releases/download/v5.0.0-beta8/premake-5.0.0-beta8-linux.tar.gz
tar -xzf premake-5.0.0-beta8-linux.tar.gz
sudo mv premake5 /usr/local/bin/premake5
sudo chmod +x /usr/local/bin/premake5
```

---

### 3. Clone and Build the Repository

Clone the repository and navigate into the plugin directory. Then run the appropriate command based on your target architecture:

- For **x86 (32-bit)** *(requires `libpq-dev:i386`)*:
```bash
  premake5 gmake && make config=release32
```

- For **x64 (64-bit)** *(requires `libpq-dev`)*:
```bash
  premake5 gmake && make config=release
```