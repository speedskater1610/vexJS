# vexJS - A port of the quick JS engine to be able to run vex robotics through vex v5 c++

## Overview

- QuickJS is a small and embeddable JavaScript engine. It aims to support the latest
[ECMAScript] specification.

This project is a _fork_ of the _fork_ [original QuickJS project] by Fabrice Bellard and Charlie Gordon, after it went dormant, with the intent of reigniting its development.

## Running your code
- make sure that you have vex pros installed if not check that out  
[here](https://pros.cs.purdue.edu/)
- Next go to the vexJS folder *NOTE: not the vex folder inside where your JS code is but instead just the overall folder*
- Next you must make the project with the command `prosv5 make` to create the file that you need.
- Once you make the program you will need to upload it with this command `prosv5 upload --slot X`
- - you can replace the `X` with what slot you are using, if you dont the pros will asume based off of your last used port. 

