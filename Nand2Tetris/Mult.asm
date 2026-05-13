// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// sets sum address to 0
@sum
M=0     //sum=0

// sets i address to 1
@i
M=1     //i=1

// creates a loop position to jump to and iterate over
(LOOP)
// subtracts ram[0] from i
// if value is greater than 0 jumps to END
@i    
D=M     //D=i
@R0
D=D-M   //D=i-R0
@END
D;JGT   // if(i-R0) > 0 goto END

// adds ram[1] to overall sum with each iteration
// adds 1 to i address with each iteration
// unconditional jump back to LOOP to continue iterations
@R1
D=M     //D=R1
@sum
M=D+M   //sum+=R1
@i
M=M+1   //i=i+1
@LOOP
0;JMP   //Goto LOOP

// creates end of loop position
// ram[2] is set to the final sum value
(END)
@sum    
D=M     //D=sum
@R2
M=D     //R2=D