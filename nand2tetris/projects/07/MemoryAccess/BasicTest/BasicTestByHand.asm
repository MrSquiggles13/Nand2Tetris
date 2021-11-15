// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/06/add/Add.asm

// Convert BasicTest to Asm by hand

//***initialize pointer variables***

//initialize stack
@256
D=A
@SP
M=D
//initialize local
@300
D=A
@LCL
M=D
//initialize argument
@400
D=A
@ARG
M=D
//initialize this
@3000
D=A
@THIS
M=D
//initialize that
@3010
D=A
@THAT
M=D
//initialize temp
@5
D=A
@TEMP
M=D

// push constant 10
@10			//access constant 10
D=A			//store value 10
@SP			//access stack pointer
A=M			//set address to stack
M=D			//store D which has value constant 10 on top of stack
@SP			//access stack pointer
M=M+1		//increment stack pointer by 1

// pop local 0
@0			//access index
D=A			//store index value
@LCL		//access local
D=D+M		//increase base local to index
@R13		//access temp register
M=D			//store local index in register
@SP			//access stack pointer
AM=M-1		//access top of stack
D=M			//store value in top of stack in register
@R13		//access pointer to local 0
A=M			//go to address of local 0
M=D			//put value of top of stack into local 0

// push constant 21
@21			//access constant 21
D=A			//store value 21 into D
@SP			//access stack pointer
A=M			//go to top of stack
M=D			//insert value 21 into top of stack
@SP			//access stack pointer
M=M+1		//increment stack pointer by 1

// push constant 22
@22			//access constant 22
D=A			//store value 22 into D
@SP			//access stack pointer
A=M			//go to top of stack
M=D			//insert value 22 into top of stack
@SP			//access stack pointer
M=M+1		//increment stack pointer by 1

// pop argument 2
@2			//access index
D=A			//store index value
@ARG		//access argument base
D=D+M		//get pointer to arg 2
@R13		//access temp register
M=D			//store arg 2 pointer
@SP			//access stack pointer
AM=M-1		//decrement stack pointer 1 access new stack pointer
D=M			//store top stack value
@R13		//access arg 2 pointer value
A=M			//move to arg 2 memory address
M=D			//store top of stack value into arg 2

// pop argument 1
@1			//access index
D=A			//store index value
@ARG		//access argument base
D=D+M		//get pointer to arg 1
@R13		//access temp register
M=D			//store arg 1 pointer
@SP			//access stack pointer
AM=M-1		//decrement stack pointer 1 access new stack pointer
D=M			//store top stack value
@R13		//access arg 1 pointer value
A=M			//move to arg 1 memory address
M=D			//store top of stack value into arg 1

//push constant 36
@36			//access constant 36
D=A			//store 36 into register
@SP			//access stack pointer
A=M			//go to stack memory
M=D			//store 36 on top of stack
@SP			//access stack pointer
M=M+1		//increment stack pointer

// pop this 6
@6			//access index
D=A			//store index value
@THIS		//access argument base
D=D+M		//get pointer to this 6
@R13		//access temp register
M=D			//store this 6 pointer
@SP			//access stack pointer
AM=M-1		//decrement stack pointer 1 access new stack pointer
D=M			//store top stack value
@R13		//access this 6 pointer value
A=M			//move to this 6 memory address
M=D			//store top of stack value into this 6

//push constant 42
@42			//access constant 42
D=A			//store 42 into register
@SP			//access stack pointer
A=M			//go to stack memory
M=D			//store 42 on top of stack
@SP			//access stack pointer
M=M+1		//increment stack pointer

//push constant 45
@45			//access constant 45
D=A			//store 45 into register
@SP			//access stack pointer
A=M			//go to stack memory
M=D			//store 45 on top of stack
@SP			//access stack pointer
M=M+1		//increment stack pointer

// pop that 5
@5			//access index
D=A			//store index value
@THAT		//access argument base
D=D+M		//get pointer to that 5
@R13		//access temp register
M=D			//store that 5 pointer
@SP			//access stack pointer
AM=M-1		//decrement stack pointer 1 access new stack pointer
D=M			//store top stack value
@R13		//access that 5 pointer value
A=M			//move to that 5 memory address
M=D			//store top of stack value into that 5

// pop that 2
@2			//access index
D=A			//store index value
@THAT		//access argument base
D=D+M		//get pointer to that 2
@R13		//access temp register
M=D			//store that 2 pointer
@SP			//access stack pointer
AM=M-1		//decrement stack pointer 1 access new stack pointer
D=M			//store top stack value
@R13		//access that 2 pointer value
A=M			//move to that 2 memory address
M=D			//store top of stack value into that 2

//push constant 510
@510		//access constant 510
D=A			//store 510 into register
@SP			//access stack pointer
A=M			//go to stack memory
M=D			//store 510 on top of stack
@SP			//access stack pointer
M=M+1		//increment stack pointer

// pop temp 6
@6			//access index
D=A			//store index value
@TEMP		//access argument base
D=D+M		//get pointer to temp 6
@R13		//access temp register
M=D			//store temp 6 pointer
@SP			//access stack pointer
AM=M-1		//decrement stack pointer 1 access new stack pointer
D=M			//store top stack value
@R13		//access temp 6 pointer value
A=M			//move to temp 6 memory address
M=D			//store top of stack value into temp 6

//push local 0
@0			//access index
D=A			//store index value
@LCL		//access local pointer
A=D+M		//add index to base pointer
D=M
@SP			//access stack pointer
A=M			//go to top of stack
M=D			//put local 0 on top of stack
@SP			//access stack pointer
M=M+1		//increment stack pointer

//push that 5
@5			//access index
D=A			//store index value
@THAT		//access that pointer
A=D+M		//add index to base pointer
D=M
@SP			//access stack pointer
A=M			//go to top of stack
M=D			//put that 5 on top of stack
@SP			//access stack pointer
M=M+1		//increment stack pointer

//add
@SP
AM=M-1
D=M
@SP
A=M-1
M=D+M


//push argument 1
@1
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1

//sub
@SP
AM=M-1
D=M
@SP
A=M-1
M=M-D

//push this 6
@6
D=A
@THIS
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1

//push this 6
@6
D=A
@THIS
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1

//add
@SP
AM=M-1
D=M
@SP
A=M-1
M=D+M

//sub
@SP
AM=M-1
D=M
@SP
A=M-1
M=M-D

//push temp 6
@6
D=A
@TEMP
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1

//add
@SP
AM=M-1
D=M
@SP
A=M-1
M=D+M