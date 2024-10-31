# Stratego
Classical stratego game with fresh graphics! Game is designed for hot seat, which means 2 players play on 1 computer. Game additionally contains Menu screen which allows to check Game Rules for newcomers :)
There is interesting feature added which sets units on the board in random order in the initial phase, sometimes set proposed by the computer is very interesting. 
Entire interface is based on mouse. Initializing units is done by draggining units into the desired field. 
In case you made a mistake or decided to place your units otherwise, you can use the Remove button after selecting the unit.
When game begins after each move players must approve their turn by clicking End Turn button which will show information box,
that the next player turn is about to begin in order to give players time to change seats.
In my game units are marked as:
 - Flag marked with 'F'
 - Spy is marked as 'S' 
 - Bomb is marked as 'B' \
 All other units are marked by their values, with the exception:
 - '2' is indeed a Scout
 - '3' is indeed a Miner

![Main Menu](https://user-images.githubusercontent.com/62173407/85401749-d268f780-b55a-11ea-9728-bb8ce322a3a0.png?raw=true)

## How to build
To build this application you need:
- C++ compiler with support for C++23 (eg: gcc14)
- CMake
- conan2

If you are using conan2 for the first time detect your profile:
`conan profile detect`

Make sure that your cwd is the project root
```bash
conan install . --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
conan build .
cd build/Debug
./stratego
```


## Acknowledgements
Textures used from this Stratego game:
[Stratego game](https://github.com/nuttywhal/stratego)

Font used from this Battleships game:
[Battleships game](https://github.com/xAdam99/Battleships)

Created with the help of SFML documentation and sources:
[Manage different screens](https://github.com/SFML/SFML/wiki/Tutorial:-Manage-different-Screens)

## Game Screen Shots

- [Main Menu](https://user-images.githubusercontent.com/62173407/85401749-d268f780-b55a-11ea-9728-bb8ce322a3a0.png)
- [Game Rules](https://user-images.githubusercontent.com/62173407/85401823-f4fb1080-b55a-11ea-9339-8af72ac1c9f5.png)
- [Enter Name](https://user-images.githubusercontent.com/62173407/85401858-05ab8680-b55b-11ea-9fc0-2aa28085f6a3.png)
- [Setting The Board](https://user-images.githubusercontent.com/62173407/85401972-2f64ad80-b55b-11ea-81bb-2f78c8d047ed.png)
- [Scout Move](https://user-images.githubusercontent.com/62173407/85402027-44d9d780-b55b-11ea-9de2-3ff096b19e8b.png)
- [Attack Info Box](https://user-images.githubusercontent.com/62173407/85402062-5622e400-b55b-11ea-9d96-9cd896a91d29.png)
