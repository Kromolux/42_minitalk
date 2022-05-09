# 42_minitalk

## Description

The purpose of this project is to code a small data exchange program using UNIX signals. It is an introductory project for the bigger UNIX projects that will appear later on in the cursus.

## Skills

* Rigor
* Unix

## Project instructions

* Name your executable files client and server.
* You have to turn in a Makefile which will compile your source files. It must not
relink.
* You have to handle errors thoroughly. In no way your program should quit unexpectedly (segmentation fault, bus error, double free, and so forth).
* Your program mustn’t have memory leaks.
* You can have one global variable per program (one for the client and one for
the server), but you will have to justify their use.

### In order to complete the mandatory part, you are allowed to use the following functions:

* write
* ft_printf and any equivalent YOU coded
* signal
* sigemptyset
* sigaddset
* sigaction
* kill
* getpid
* malloc
* free
* pause
* sleep
* usleep
* exit
