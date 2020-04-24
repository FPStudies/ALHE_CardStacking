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
    struct InterpreterEntity{
        struct Data{
            std::string extractedKeyword;
            std::vector<std::string> commands;
            std::vector<std::vector<std::string>> commandsArg;

            Data();
            ~Data();
            Data(const Data& other) = delete;
            Data(Data&& other);
            Data& operator=(Data&& other);
        };

        std::vector<Data> dataToInterpret;
        std::unique_ptr<CommandInterpreter> interpreter;

        InterpreterEntity(const InterpreterEntity& other) = delete;
        InterpreterEntity(const CommandInterpreter& inter);
        ~InterpreterEntity();
        InterpreterEntity(InterpreterEntity&& other);
        InterpreterEntity& operator=(InterpreterEntity&& other);
    };

    std::vector<std::unique_ptr<InterpreterEntity>> interpreters;

    bool divideByKeyWords(std::stringstream& command);
    void getLine(std::stringstream& extractFrom, std::string& extractTo) const;
    void clearWhitespace(std::stringstream& extractFrom) const;
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