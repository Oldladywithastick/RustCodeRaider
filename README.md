# RustCodeRaider
A simple SMFL-based program to optimize code raiding in the game Rust.
It tracks progress over time and can jump to specific Lines of the total of 10000 Lines of available code lock numbers. It also improves efficiency with teammates a lot as you can coordinate more easily

1. Download all the files (you dont need the font if you want to supply your own)
2. Install SMFL in MSYS2 Terminal using: pacman -S mingw-w64-x86_64-sfml
3. Compile using: g++ coderaider.cpp -lsfml-graphics -lsfml-window -lsfml-system


Problems: 
-Window resizing is currently bugged, but you can work around it (going to fix this someday)
-Pressing escape while entering a line to jump to also closes the program (going to fix this soon)

