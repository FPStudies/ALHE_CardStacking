#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string>

class CommandInterpreter{

public:
    CommandInterpreter() {};
    ~CommandInterpreter() {};
    CommandInterpreter(const CommandInterpreter& other) = delete;

    /**
     * @brief Performs actions that correspond to this command.
     * Can be used in recursion to extract key phrases of commands such as flags.
     * 
     * @param command 
     * @return true if command was not found or there is no other operations to perform. This is useful in recursion.
     * @return false otherwise.
     */
    virtual bool runCommand(const std::string& keyword, const std::vector<std::string>& flags, const std::vector<std::vector<std::string>>& dataToFlags) = 0;

    virtual bool isKeyword(const std::string& word) const = 0;

    virtual bool isCommand(const std::string& command) const = 0;

    virtual bool expectedStringAfterCommand(const std::string& command, const std::string& string) const = 0;

    virtual CommandInterpreter* clone() const = 0;
};

#endif