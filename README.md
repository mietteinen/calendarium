# A desktop calendar app

A simple desktop calendar for keeping track of upcoming activities (that functionality is coming later).

The program is written in C++, and is based on a school Tkinter GUI project written by the author of this program.

# How to build and run

## Prerequisites

Before building the application, ensure that you have the following prerequisites installed on your system:

- [Qt](https://www.qt.io/download) framework (version 4.0.0 or higher)

## Build Instructions

1. Clone or download the project repository from [GitHub](https://github.com/mietteinen/calendar-cpp) to your local machine.

2. Open a terminal or command prompt and navigate to the project directory.

3. Run the following command to generate the project files using qmake:
    
    ``` shell
   qmake
   ```
   This command generates the necessary makefiles or build files based on the .pro file in the project directory.

4. Once the project files are generated, you can build the project using the appropriate build command for your platform. For example:

    - **Linux/macOS**: Run the `make` command.
    - **Windows**: Open the generated Visual Studio solution (`calendar-cpp.sln`) and build it using Visual Studio. Alternatively, you can use the `nmake` command from the Visual Studio command prompt.
  
5. Now the executable should have been generated in the build output directory. On a Linux machine, navigating to the correct folder and typing `./calendar-cpp` runs the application. If you are on a Windows machine, typing `calendar-cpp.exe` should do the trick.

## Additional Notes

- If you encounter any build issues or errors, make sure that you have the correct version of the Qt framework installed and that your environment variables (such as `PATH`) are properly set.

- For more detailed information on configuring and building Qt projects with qmake, refer to the [Qt Documentation](https://doc.qt.io/qt-5/qmake-manual.html).

- If you have any questions or need further assistance, please feel free to open an issue in the [project repository](https://github.com/mietteinen/calendar-cpp/issues).
