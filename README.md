# Yakreb Engine

[![GitHub license: MIT](https://img.shields.io/badge/license-MIT%20License-green)](https://raw.githubusercontent.com/PlagueTR/Yakreb/main/LICENSE)

**I do not plan on accepting other contributions to the main repository as I want to learn how everything works.**

## 📖 What's Yakreb Engine?

Yakreb is a simple game engine being written for learning purposes and personal use.

Yakreb is currently compatible with both Windows and Linux. However; it is being developed mainly on Windows, for Windows. Thus, while it runs on Linux, I can not guarantee the same level of support or performance on Linux systems.

Testing and development on Windows is done using Visual Studio 2022, whereas on Linux, CodeLite 17.0.0 with the GCC compiler is used for testing.<br>
This project is built with Premake 5 as the primary build system, so while other IDEs may potentially work, their compatibility can't be guaranteed.

## 📖 Getting Started

**Prerequisites:**

Before you begin, make sure you have Python 3.3 or a later version and venv python package installed on your system.<br>
It is highly recommended to have Visual Studio 2019 or later for Windows and CodeLite for Linux testing and development.

**Setup:**

**1.** Start by cloning the repository with `git clone --recursive https://github.com/PlagueTR/Yakreb`.<br>
&nbsp;    ▫ You can run `git submodule update --init` if the repository was cloned non-recursively.<br>
**2.** Depending on your operating system, run either `SetupWindows.bat` or `SetupLinux.sh` under the `Scripts` folder.<br>
**3.** Depending on your operating system, run either `GenerateWindowsProject.bat` or `GenerateLinuxProject.sh` under the `Scripts` folder.<br>
&nbsp;    ▫ You can rerun these project generation scripts if you want to regenerate the project files or have made any changes.

More information will be added as the engine gets developed.
