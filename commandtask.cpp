#include "commandtask.h"

#include "font.h"
#include <map>
#include "worldtask.h"



CommandTask command_task;

std::map<char*, std::vector<char*>> commandHelp = {
    {"/tp", {"TP allows you to teleport a player into oblivion"}}
};

std::map<char*, std::vector<std::vector<char*>>> commandArguments = {
    {"/tp", {{"int", "x coordinate"}, {"int", "y coordinate"}, {"int", "z coordinate"}}}
};

std::map<char*, bool> runnableCommands = {
    {"/tp", true}
};


void CommandTask::executeCommand() {
    // Convert the vector to a char array
    char charConverted[command.size()];

    for (size_t i = 0; i < command.size(); i++) {
        charConverted[i] = command[i];
    }

    logCommandOutput(charConverted);

    if (runnableCommands.find(charConverted) != runnableCommands.end()) {
        //
    } else {
        logCommandOutput("Error: Command not found");
    }
}

CommandTask::CommandTask()
{
    background = newTexture(background_width, background_height, 0, false);
}

CommandTask::~CommandTask()
{
    deleteTexture(background);
}

void CommandTask::makeCurrent()
{
    if(!background_saved)
        saveBackground();

    Task::makeCurrent();
}

void CommandTask::render()
{
    drawBackground();

    const unsigned int x = (background_offset / 2);
    const unsigned int y = (background_offset / 2);
    drawTextureOverlay(*background, 0, 0, *screen, x, y, background->width, background->height);

    drawString("Commands for Crafti v1.4 [C14DB]", 0xFFFF, *screen, x + background_inner_offset, y + background_inner_offset);

    char number[10];
    snprintf(number, sizeof(number), "%d", background_height/fontHeight());

    commandOutput = {
        {command[0], "1"},
        {"there", "2"},
        {"testing", "3"},
        {"stuff", "4"},
        {"there", "5"},
        {"should", "6"},
        {"be", "7"},
        {"a", "8"},
        {"maximum", "9"},
        {"number", "10"},
        {"of", "11"}
    };

    for (size_t i = 0; i < commandOutput.size(); i++) {
        drawString(commandOutput[i][0], 0xFFFF, *screen, x+background_inner_offset, y + background_inner_offset + (fontHeight() * (i+2)));
        drawString(commandOutput[i][1], 0xFFFF, *screen, x+background_inner_offset+(background_width/2), y + background_inner_offset + (fontHeight() * (i+2)));
    }

    drawString(number, 0xFFFF, *screen, x + background_inner_offset + 100, y + background_inner_offset + 100);


    // Draw Bottom Command-Typing Box
    const unsigned int bottom_height = fontHeight()*2;
    const unsigned int bottom_y = (background_height + background_offset/2) - (fontHeight()*2);
    drawTextureOverlay(*background, 0, 0, *screen, x, bottom_y, background->width, bottom_height);

    // Convert the vector to a char array
    char charConverted[command.size()];

    for (size_t i = 0; i < command.size(); i++) {
        charConverted[i] = command[i];
    }

    charConverted[command.size()] = '|';

    drawString(charConverted, 0xFFFF, *screen, x + background_inner_offset, bottom_y + (fontHeight()/2));
}

void CommandTask::logic()
{
    if(key_held_down)
        key_held_down = keyPressed(KEY_NSPIRE_ESC) || keyPressed(KEY_NSPIRE_DIVIDE) || keyPressed(KEY_NSPIRE_A) || keyPressed(KEY_NSPIRE_B) || keyPressed(KEY_NSPIRE_C) || keyPressed(KEY_NSPIRE_D) || keyPressed(KEY_NSPIRE_E) || keyPressed(KEY_NSPIRE_F) || keyPressed(KEY_NSPIRE_G) || keyPressed(KEY_NSPIRE_H) || keyPressed(KEY_NSPIRE_I) || keyPressed(KEY_NSPIRE_J) || keyPressed(KEY_NSPIRE_K) || keyPressed(KEY_NSPIRE_L) || keyPressed(KEY_NSPIRE_M) || keyPressed(KEY_NSPIRE_N) || keyPressed(KEY_NSPIRE_O) || keyPressed(KEY_NSPIRE_P) || keyPressed(KEY_NSPIRE_Q) || keyPressed(KEY_NSPIRE_R) || keyPressed(KEY_NSPIRE_S) || keyPressed(KEY_NSPIRE_T) || keyPressed(KEY_NSPIRE_U) || keyPressed(KEY_NSPIRE_V) || keyPressed(KEY_NSPIRE_W) || keyPressed(KEY_NSPIRE_X) || keyPressed(KEY_NSPIRE_Y) || keyPressed(KEY_NSPIRE_Z) || keyPressed(KEY_NSPIRE_DEL) || keyPressed(KEY_NSPIRE_SPACE) || keyPressed(KEY_NSPIRE_0) || keyPressed(KEY_NSPIRE_1) || keyPressed(KEY_NSPIRE_2) || keyPressed(KEY_NSPIRE_3) || keyPressed(KEY_NSPIRE_4) || keyPressed(KEY_NSPIRE_5) || keyPressed(KEY_NSPIRE_6) || keyPressed(KEY_NSPIRE_7) || keyPressed(KEY_NSPIRE_8) || keyPressed(KEY_NSPIRE_9) || keyPressed(KEY_NSPIRE_NEGATIVE)|| keyPressed(KEY_NSPIRE_PERIOD) || keyPressed(KEY_NSPIRE_ENTER);

    else if (keyPressed(KEY_NSPIRE_ESC) || keyPressed(KEY_NSPIRE_DIVIDE)) {
        world_task.makeCurrent();
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_A)) {
        command.push_back('a');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_B)) {
        command.push_back('b');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_C)) {
        command.push_back('c');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_D)) {
        command.push_back('d');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_E)) {
        command.push_back('e');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_F)) {
        command.push_back('f');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_G)) {
        command.push_back('g');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_H)) {
        command.push_back('h');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_I)) {
        command.push_back('i');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_J)) {
        command.push_back('j');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_K)) {
        command.push_back('k');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_L)) {
        command.push_back('l');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_M)) {
        command.push_back('m');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_N)) {
        command.push_back('n');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_O)) {
        command.push_back('o');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_P)) {
        command.push_back('p');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_Q)) {
        command.push_back('q');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_R)) {
        command.push_back('r');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_S)) {
        command.push_back('s');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_T)) {
        command.push_back('t');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_U)) {
        command.push_back('u');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_V)) {
        command.push_back('v');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_W)) {
        command.push_back('w');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_X)) {
        command.push_back('x');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_Y)) {
        command.push_back('y');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_Z)) {
        command.push_back('z');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_1)) {
        command.push_back('1');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_2)) {
        command.push_back('2');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_3)) {
        command.push_back('3');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_4)) {
        command.push_back('4');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_5)) {
        command.push_back('5');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_6)) {
        command.push_back('6');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_7)) {
        command.push_back('7');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_8)) {
        command.push_back('8');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_9)) {
        command.push_back('9');
        key_held_down = true;
    } else if(keyPressed(KEY_NSPIRE_0)) {
        command.push_back('0');
        key_held_down = true;
    } else if (keyPressed(KEY_NSPIRE_NEGATIVE)) {
        command.push_back('-');
        key_held_down = true;
    } else if (keyPressed(KEY_NSPIRE_PERIOD)) {
        command.push_back('.');
        key_held_down = true;
    } else if (keyPressed(KEY_NSPIRE_SPACE)) {
        command.push_back(' ');
        key_held_down = true;
    } else if (keyPressed(KEY_NSPIRE_DEL) && command.size() > 1) {
        command.pop_back();
        key_held_down = true;
    } else if (keyPressed(KEY_NSPIRE_ENTER)) {
        executeCommand();
        key_held_down = true;
    }
}