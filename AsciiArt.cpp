#include "AsciiArt.h"
#include <iostream>

const char* gameOverTxt[8] =
{
    "+----------------------------------------------------------------------+",
    "|  _______ _______ _______ _______    _______ _     _ _______ ______   |",
    "| (_______|_______|_______|_______)  (_______|_)   (_|_______|_____ \\  |",
    "|  _   ___ _______ _  _  _ _____      _     _ _     _ _____   _____) ) |",
    "| | | (_  |  ___  | ||_|| |  ___)    | |   | | |   | |  ___) |  __  /  |",
    "| | |___) | |   | | |   | | |_____   | |___| |\\ \\ / /| |_____| |  \\ \\  |",
    "|  \\_____/|_|   |_|_|   |_|_______)   \\_____/  \\___/ |_______)_|   |_| |",
    "+----------------------------------------------------------------------+"
};

const char* youWonTxt[8] =
{
    "+------------------------------------------------------+",
    "|  _     _ _______ _     _    _  _  _ _______ _______  |",
    "| | |   | (_______|_)   (_)  (_)(_)(_|_______|_______) |",
    "| | |___| |_     _ _     _    _  _  _ _     _ _     _  |",
    "| |_____  | |   | | |   | |  | || || | |   | | |   | | |",
    "|  _____| | |___| | |___| |  | || || | |___| | |   | | |",
    "| (_______|\\_____/ \\_____/    \\_____/ \\_____/|_|   |_| |",
    "+------------------------------------------------------+"
};

const char* title[32] =

{
     " _____                                                                                                      _____ ",
    "( ___ )----------------------------------------------------------------------------------------------------( ___ )",
     " |   |                                                                                                      |   | ",
     " |   |  ____                                                                                                |   | ",
     " |   | /\\  _`\\                                                                                              |   | ",
     " |   | \\ \\ \\/\\ \\  __  __    ___      __      __    ___     ___     ____                                     |   |",
     " |   |  \\ \\ \\ \\ \\/\\ \\/\\ \\ /' _ `\\  /'_ `\\  /'__`\\ / __`\\ /' _ `\\  /',__\\                                    |   |",
     " |   |   \\ \\ \\_\\ \\ \\ \\_\\ \\/\\ \\/\\ \\/\\ \\L\\ \\/\\  __//\\ \\L\\ \\/\\ \\/\\ \\/\\__, `\\                                   |   | ",
     " |   |    \\ \\____/\\ \\____/\\ \\_\\ \\_\\ \\____ \\ \\____\\ \\____/\\ \\_\\ \\_\\/\\____/                                   |   |",
     " |   |     \\/___/  \\/___/  \\/_/\\/_/\\/___L\\ \\/____/\\/___/  \\/_/\\/_/\\/___/                                    |   |",
     " |   |                               /\\____/                                                                |   |",
     " |   |                               \\_/__/                                                                 |   |",
     " |   |                    __                                                                                |   |",
     " |   |                   /\\ \\                                                                               |   |",
     " |   |    __      ___    \\_\\ \\                                                                              |   |",
     " |   |  /'__`\\  /' _ `\\  /'_` \\                                                                             |   | ",
     " |   | /\\ \\L\\.\\_/\\ \\/\\ \\/\\ \\L\\ \\                                                                            |   |",
     " |   | \\ \\__/.\\_\\ \\_\\ \\_\\ \\___,_\\                                                                           |   |",
     " |   |  \\/__/\\/_/\\/_/\\/_/\\/__,_ /                                                                           |   |",
     " |   |                                                                                                      |   |",
     " |   |                                                                                                      |   |",
     " |   |        __         ___    ___          __                                                             |   |",
     " |   |       /\\ \\__  __ /\\_ \\  /\\_ \\        /\\ \\                                                            |   |",
     " |   |   ____\\ \\ ,_\\/\\_\\\\//\\ \\ \\//\\ \\       \\_\\ \\  __  __    ___      __      __    ___     ___     ____    |   |",
     " |   |  /',__\\\\ \\ \\/\\/\\ \\ \\ \\ \\  \\ \\ \\      /'_` \\/\\ \\/\\ \\ /' _ `\\  /'_ `\\  /'__`\\ / __`\\ /' _ `\\  /',__\\   |   | ",
     " |   | /\\__, `\\\\ \\ \\_\\ \\ \\ \\_\\ \\_ \\_\\ \\_   /\\ \\L\\ \\ \\ \\_\\ \\/\\ \\/\\ \\/\\ \\L\\ \\/\\  __//\\ \\L\\ \\/\\ \\/\\ \\/\\__, `\\  |   | ",
     " |   | \\/\\____/ \\ \\__\\\\ \\_\\/\\____\\/\\____\\  \\ \\___,_\\ \\____/\\ \\_\\ \\_\\ \\____ \\ \\____\\ \\____/\\ \\_\\ \\_\\/\\____/  |   |",
     " |   |  \\/___/   \\/__/ \\/_/\\/____/\\/____/   \\/__,_ /\\/___/  \\/_/\\/_/\\/___L\\ \\/____/\\/___/  \\/_/\\/_/\\/___/   |   | ",
     " |   |                                                                /\\____/                               |   | ",
     " |   |                                                                \\_/__/                                |   | ",
     " |___|                                                                                                      |___| ", 
    "(_____)----------------------------------------------------------------------------------------------------(_____)"
};

void DisplayAsciiArt(const char** asciiArt, int length, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < length; j++)
        {
            std::cout << asciiArt[i][j];
        }
        std::cout << std::endl;
    }
}