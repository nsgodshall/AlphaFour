# Repository for AlphaFour Project

AlphaFour is a senior design project for Mechanical Engineering students at UCLA. It is a robot that can play Connect 4 against a human opponent.

## Running the code

To run the code, first create run the Makefile, inside the main directory, enter the following command

`make`

Then, a new file should appear in the `./bin/` folder, you can run this binary file while still inside the main directory by entering the following command


`./bin/alpha4`

## TODO 

Our bible is this 15 year old blog post from some French PhD. candidate https://blog.gamesolver.org 
The biggest learning curve is that the game state is stored inside a single 64-bit integer, rather than a 2D-array.
