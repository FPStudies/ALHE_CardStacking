#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string>

class CommandInterpreter{

public:
    /**
     * @brief Performs actions that correspond to this command.
     * Can be used in recursion to extract key phrases of commands such as flags.
     * 
     * @param command 
     * @return true if command was not found or there is no other operations to perform. This is useful in recursion.
     * @return false otherwise.
     */
    virtual bool run(const std::string& command, const std::vector<std::string>& other) = 0;

    virtual bool isKeyword(const std::string& word) const = 0;

    virtual bool isCommand(const std::string& word) const = 0;

    virtual CommandInterpreter* copy() const = 0;

    CommandInterpreter(const CommandInterpreter&) = delete;
};

#endif