# sudoku Solver Esp Microcontroller
sudoku solver using ESP8266 microcontoller and ILI9341 touch screen lcd using Arduino IDE C++

description:
sudoku solver/player on ili9341 touch screen and esp8266 micrcontroller where you can create your own board or get a random board and then either use the solver 
to find the answer or solve it yourself and then use the checker to see if your soluton is correct. The solver uses backtracking but the solver is optimized so
that it first fills in some or all of the board (depending on board difficulty) using basic sudoku solving techniques that use process of elimination. These 
techniques are a lot less intense then backtracking so I used them to decrease the work that the backtracking has to do. The checker calls the solve function to solve
the original board and then compares the users board to that board. If both match then the user's answer is correct then "correct" is printed to the LCD screen, other
wise "incorrect".

If you want to try this out make sure you have the libraries and make sure the wiring is correct. There are lots of problems that arise from not wiring correctly 
or not having a stable input voltage. Recommended to have capacitor at input to smooth out voltage but usually its unecessary if your connected to a stable
source.(doesn't hurt to have the capacitor though).

Also all screens need to be calibrated. The values I used are according to the screen that I used. I tapped the 4 corners of the screen and printed the coordinates
and used those coords to create a grid system to place the sudoku board and the buttons. Those coordinates may be different for you and might have to be changed but
I think it might not be necessary because I ran the program on another screen and it worked. 

The reason I used the esp 8266 is because it is a lot faster than arduino and can handle the backtracking a lot better. I did optimize the code so that much of the 
board or even all of it is filled in before the backtracking (depending on board difficulty) which does minimize a lot of the work the backtracking has to do but
even with the optimizations it is still slow on Arduino. ESP microcontrollers are also cheap and they have wifi so they are very versatile.
