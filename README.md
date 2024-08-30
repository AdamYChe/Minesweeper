# Minesweeper

Minesweeper is a classic game with a simple premise. Players attempt to reveal all tiles, minus the ones that have mines underneath them. Clicking on one of the mines will end the game, and mines are randomly dispersed through a board. The premise of minesweeper is to use strategy and critical thinking to successfully navigate the dangers of the mines.

Tiles on the board have either a mine or no mine underneath. Left clicking a tile with a mine causes the game to end in a loss. If all non-mine tiles are revealed, the player wins. If a non-mine tile gets revealed, the amount of mines adjacent to that mine are displayed on the tile; when there are no adjacent mines, all non-mine tiles next to the clicked tile will be revealed. This repeats recursively until the game is won or all clicked tiles have adjacent mines. The player is able to right click to place flags to assist in deducing mine locations. 

The player can reset the game by clicking the face at the bottom of the screen. The bottom left contains a counter that initially displays the amount of mines on the board, and goes down with each flag placed down. Flags can be taken away by right clicking again on placed flags. A debug menu that reveals all mine tiles is to the right of the face. Additionally, test boards exist with guarenteed mine spawns. 

![image](https://github.com/user-attachments/assets/407096f1-e769-4990-af39-c40455c15934)


## How to Run Minesweeper
1. Download GCC 7.3.0 MinGW (SEH) - 64-bit, and decompress this into C:\Libraries.
2. Add path ```C:\Libraries\SFML-2.5.1``` as variable ```SFML_INSTALL``` to system variables.
3. Add binary path ```C:\Libraries\SFML-2.5.1\bin``` to the ```PATH``` system variable.
4. Clone the repository from GitHub into a CLion Project.*
5. Compile and run the minesweeper executable to play Minesweeper.
6. When finished playing, click the X in the top right of the window to terminate the game.

\*If you decide to use an IDE different from CLion, the executeable may not run depending on the C++ installation. Changing some directory information in the CMakeLists.txt file may be required to successfully run the executeable.
