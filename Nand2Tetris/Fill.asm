// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(BEGIN)
	// Set keyboard to address for keyboard input value.
	@24576
	D=A             // D stores 24576
	@keyboard       
	M=D             // keyboard = 24576
(CHECK_KEYBOARD)
	// Set current to last screen pixel map.
	@24575
	D=A            // D stores 24575 			
	@current
	M=D           // current = 24575
	// If keyboard is pressed, fill the screen.
	@keyboard
	A=M          // A = keyboard
	D=M			// D stores keyboard
	@fillvalue
	M=-1        // fillvalue = -1
	@DRAW
	D;JNE       // jump to draw if D does not equal 0
	// Otherwise, clear the screen.
	@fillvalue
	M=0        // sets fillvalue to 0
(DRAW)
	// Fill or clear current pixel, depending on fillvalue.
	@fillvalue
	D=M		   // D stores fillvalue
	@current
	A=M       // A = current
	M=D       // current = fillvalue stored in D
	// If current pixel map is first pixel map there is nothing left to draw, so
	//jump back to keyboard check.
	@current
	D=M       // D stores current
	@16384
	D=D-A    // D = 16384 subtracted from current stored in D
	@CHECK_KEYBOARD
	D;JLE   // jump to CHECK_KEYBOARD if D <= 0
	// Decrement current pixel map.
	@current
	M=M-1   // current = current - 1
	// Continue drawing next pixel map.
	@DRAW   
	0;JMP  // jump to DRAW