# Minesweeper game

## Game description.

Minesweeper is a classic logic game in which players have to figure out the location of mines on the playing field. The game is presented in the form of a grid of cells, each of which can be closed, open (with a number or empty) or contain a mine. 
This version of the Minesweeper game is written for the Unix terminal, which allows players to enjoy the game in a text interface. Players interact with the game via the command line, using keys to open cells and set flags.

## Basic rules.

* The player opens cells, starting with one.
* The numbers on open cells indicate the number of mines in neighboring cells.
* You can place flags on suspected mines.
* Opening a cell with a zero automatically opens neighboring cells.

## Description of the project.

This project is a miner game that includes source code, build automation scripts. This makes it easy to install and play the game. 

## Software dependencies.

* C++17
* Make 4.4.1
* libncurses5-dev 
* pkg-config

## Example

<div id="header" align="center">
     <img src="./gif/game.gif" /><br><br>
</div> 

## Authors
pbalykov - developer [github](https://github.com/pbalykov)
