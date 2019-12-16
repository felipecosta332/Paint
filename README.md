# The Paint Project

Federal University of Rio Grande do Norte (UFRN) programming project of the "Introduction to the Programming Techniques" class (From portuguese "Introdução às Técnicas de Programação", also known as ITP). The purpose of the project is to develop a program that creates, reads and manipulates .ppm image files. The orientations and deadline requirements were given by Professor André Maurício Cunha Campos, teacher of the ITP class (2019.2 semester).

# How to compile the program

If you are running Linux on your machine, open the terminal and follow the steps:

    - Access the "src" directory.
    - Type in the following command on the terminal: "gcc -o main main.c fileio.c draw.c vector.c text.c -lm".
    - Press return.

# How to run the program

Before you run the program, make sure the following requirements are fulfilled:

    - You have downloaded or cloned the repository in your machine.
    - The "files" directory has a "input.txt" file.
    - The "main.c" source code file in the "src" directory is compiled.

To run the program, follow the steps:

    - Access the "src" directory.
    - If you are going to run the program using the "input.txt" file, type in the commands you want in the "input.txt" file. There will be instructions inside the file explaining each command available. There are also preset scripts that you can copy and paste in the "input.txt" file to use or simply read them as examples. These scripts are inside the "scripts" directory.
    - If you are going to run the program using the terminal, type in "terminal" in the first line of the "input.txt" file and press return, then save the "input.txt" file. After you start running the program, all commands and its respective parameters will be entered in the terminal. The program will stop running once you enter "end" in the terminal command line.
    - Type in the following command on the terminal: "./main".
    - Press return.

# Commands and Parameters

# Deadlines

First Delivery (25/10/2019)
- Necessary data types (typedef, structs and enums).
- Program modularization (which .c and .h files).
- File specification reading.
- PPM image generation.

Second Delivery (01/11/2019)
- Line drawing.
- Polygon drawing.

Third Delivery (08/11/2019)
- Circle drawing.
- Color filling.

Final Delivery (22/11/2019)
- Extra elements implementation, defined by the group itself.

Late Delivery (27/11/2019)
- Delivery of any part that was not presented. Points will be decreased on this delivery.