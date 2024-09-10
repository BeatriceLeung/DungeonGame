# 2d Dungeon Crawler #
A 2D cpp game where your party has to cross the dungeon while fighting back monsters in turn-based combat. This was my final project of a class on intermediate C++ a few years ago, and I used polymorphism/inheritance to grant different character classes different abilities in battle and travel:

- Novices have a luck stat that will decrease the rates of strong monsters appearing
- Knights have a armor stat that will reduce the damage taken from monsters as well as the ability to equip weapons dropped from monsters for increased attack.
- Wizards have the ability to fully heal any alive party member.

Defeating monsters will grant all party members EXP points, which can level-up your characters for increased health and other stats relevant to the character type. Once characters are killed, they cannot be revived.

Create as many members for your party as you like and fight your way to the end of the dungeon on a grid size of your choice.

# To Run #
- Clone this repository `cd the/path/of/this/file`
- Run the makefile with `make`
- Run the executable generated `./main`

