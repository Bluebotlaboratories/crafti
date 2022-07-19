#ifndef COMMANDTASK_H
#define COMMANDTASK_H

#include "task.h"
#include "gl.h"
#include <vector>

class CommandTask : public Task
{
public:
    CommandTask();
    virtual ~CommandTask();

    virtual void makeCurrent() override;

    virtual void render() override;
    virtual void logic() override;

private:
    static constexpr int background_offset = 10, background_width = SCREEN_WIDTH - background_offset, background_height = SCREEN_HEIGHT - background_offset, background_inner_offset = 10;
    
    std::vector<std::vector<char*>> commandOutput;
    std::vector<char> command = {'/'};

    TEXTURE *background;
    void executeCommand();
    void logCommandOutput(char *mainLog, char *secondaryLog);
};

extern CommandTask command_task;

#endif // COMMANDTASK_H
