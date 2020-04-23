#ifndef COMMAND_DIVIDER_H
#define COMMAND_DIVIDER_H

#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>

#include "commandInterpreter.h"

class CommandDivider{
    struct DividedWord{
        std::string extractedKeyword;
        std::vector<std::string> commands;
        std::vector<std::vector<std::string>> commandsArg;
        std::unique_ptr<CommandInterpreter> interpreter;

        DividedWord(const DividedWord& other) = delete;
        DividedWord(const CommandInterpreter& inter);
        ~DividedWord();
        DividedWord(DividedWord&& other);
        DividedWord& operator=(DividedWord&& other);
    };

    std::vector<std::unique_ptr<DividedWord>> interpreters;

    bool divideByKeyWords(std::stringstream& command);
    void clear();

public:
    CommandDivider();
    ~CommandDivider();
    CommandDivider(const CommandDivider& other) = delete;

    bool runCommand(const std::string& command, bool clearBuf = true);
    bool loadCommandsFromFile(const std::string path, bool clearBuf = true);

    /**
     * @brief Adds a command interpreter that is used when keyword matches.
     * 
     * Only one interpreter with given class can be in shell.
     * 
     * @param inter 
     * @return true 
     * @return false 
     */
    bool addInterpreter(const CommandInterpreter& inter);

    

};


#endif