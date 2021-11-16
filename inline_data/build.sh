#!/bin/bash

make
gcc -Wall -o hexwrite hexwrite.c
./hexwrite
