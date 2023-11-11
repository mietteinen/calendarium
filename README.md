# A desktop calendar app

A simple and lightweight desktop calendar for keeping track of upcoming activities (that functionality is coming later).

The program is written in C++, and is based on a Tkinter GUI program written by the author of this program as a school project.


# Author

The author of this GUI application is Tomi Miettinen, a second-year Computer Science student.


# How to build and run

## Prerequisites

To be able to build this project, you have to have make, qmake, and the Qt Core Libraries installed. Follow the instructions below to acquire them.
<details>
<summary>Linux</summary>

1. Install the dependencies via your system's package manager:

   <p><h5> Debian/Ubuntu </h5></p>

    ```shell
    sudo apt-get install make qtbase5-dev
    ```

2. Run `qmake --version` and `make --version` to make sure the tools are working as they should.
    - You may have to restart your shell session by reopening the terminal.
</details>

<details>
<summary>Windows</summary>

1. Download the [Qt OSS Installer](https://www.qt.io/download-qt-installer-oss) and run it.
2. When the installer prompts you to pick an installation, make a custom one.
3. Uncheck every box and check `{QT VERSION} -> MinGW x.x.x 64-bit` (recommended Qt version `>= 5.12.2`)
    - **Optional**: You can install the whole Qt Creator IDE if you desire. It should install all required packages.
4. Press 'Next' and wait for the installation to finish.
5. Add `C:\Qt\{QT VERSION}\{MINGW VERSION}\bin` and `C:\Qt\Tools\{MINGW VERSION}\bin` to `PATH`.
    - If you picked a drive other than `C:\`, adjust accordingly.
6. Run `qmake -version` and `mingw32-make -version` to make sure the tools are working as they should.
</details>

## Build Instructions

1. Clone or download the project repository from [GitHub](https://github.com/mietteinen/calendar-cpp) to your local machine. To clone the project, open the terminal and `cd` to the folder you want to clone the project to. Then type the following command:

    ``` shell
    git clone https://github.com/mietteinen/calendar-cpp.git
    ```

2. Navigate to the project directory.

   ``` shell
    cd calendar-cpp
    ```

3. Run the following command to generate the project files using qmake:
    
    ``` shell
   qmake
   ```
   This command generates the necessary makefiles or build files based on the `.pro` file in the project directory.

4. Once the project files are generated, you can build the project by running `make`. This is usually different for Linux and Windows.

   - **Linux**: `make`
   - **Windows**: `mingw32-make`  
<br>

5. Now the executable should have been generated in the directory. On a Linux machine, type `./CalendarCPP` to run the program. If you are on a Windows machine, just double clicking the newly generated `CalendarCPP.exe` does the trick.

6. You can clean unnecessary files from the folder with `make clean` or `mingw32-make clean`.

**Note**: Depending on your MinGW installation, the version can vary. If you're having problems with running `mingw32-make` on Windows, navigate to the installation folder (e.g. `C:\Qt\Tools\mingw810_64\bin\`), in which you can find the correct `make` installation. For me it was `mingw32-make`. Make sure this directory is also in your PATH variable.

## Additional Notes

- If you encounter any build issues or errors, make sure that you have the correct version of the Qt framework installed and that your environment variables (such as `PATH`) are properly set.

- If you have any questions or need further assistance, please feel free to open an issue in the [project repository](https://github.com/mietteinen/calendar-cpp/issues).
