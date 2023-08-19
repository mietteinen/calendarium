# A desktop calendar app

A simple and lightweight desktop calendar for keeping track of upcoming activities (that functionality is coming later).

The program is written in C++, and is based on a Tkinter GUI program written by the author of this program as a school project.


# Author

The author of this GUI application is Tomi Miettinen, a second-year Computer Science student.


# How to build and run

## Prerequisites

Before building the application, ensure that you have some version of the Qt binaries installed on your system:

- The easiest method is installing the [Qt OSS](https://www.qt.io/download-qt-installer-oss) framework (preferrably version 5.0.0 or higher)

    - Some version of `qmake` and `make` (should come with Qt).


## Build Instructions

1. Clone or download the project repository from [GitHub](https://github.com/mietteinen/calendar-cpp) to your local machine. To do so, open the terminal and `cd` to the folder you want to clone the project to. Then type the following command:

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

4. Once the project files are generated, you can build the project by running `make`, which is usually installed alongside Qt. This should create an executable for the desired operating system.

    **Note**: The `qmake` and `make` tools have different versions. If your terminal does not find one of the tools, it can usually be found in the Qt installation folder.
   
    - On **Windows** navigate to the Qt installation folder (e.g. `C:\Qt\Qt5.12.12\5.12.12\mingw73_64\bin\`), in which you can find the correct `make` installation. For me it was `mingw32-make`.

    - On **Linux** the tools worked as they should, but they could be found at `~/<user>/Qt/6.1.1/gcc_64/bin/` if needed.
  
6. Now the executable should have been generated in the build output directory. On a Linux machine, navigating to the correct folder and typing `./<executable>` runs the application (replace <executable> with the name, in this case most likely being CalendarCPP). If you are on a Windows machine, just double clicking the newly generated `.exe` does the trick.


## Additional Notes

- If you encounter any build issues or errors, make sure that you have the correct version of the Qt framework installed and that your environment variables (such as `PATH`) are properly set.

- For more detailed information on configuring and building Qt projects with qmake, refer to the [Qt Documentation](https://doc.qt.io/qt-5/qmake-manual.html).

- If you have any questions or need further assistance, please feel free to open an issue in the [project repository](https://github.com/mietteinen/calendar-cpp/issues).
