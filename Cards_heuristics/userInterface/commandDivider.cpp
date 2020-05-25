#ifndef COMMAND_DIVIDER_CPP
#define COMMAND_DIVIDER_CPP

#include "commandDivider.h"

CommandDivider::InterpreterEntity::Data::Data()
    :extractedKeyword(), commands(), commandsArg()
{}

CommandDivider::InterpreterEntity::Data::~Data()
{}

CommandDivider::InterpreterEntity::Data::Data(Data&& other)
    :extractedKeyword(std::move(other.extractedKeyword)), 
    commands(std::move(other.commands)), 
    commandsArg(std::move(other.commandsArg))
{}

CommandDivider::InterpreterEntity::Data& CommandDivider::InterpreterEntity::Data::operator=(Data&& other){
    extractedKeyword = std::move(other.extractedKeyword);
    commands = std::move(other.commands);
    commandsArg = std::move(other.commandsArg);

    return *this;
}

CommandDivider::InterpreterEntity::InterpreterEntity(const CommandInterpreter& inter)
    :dataToInterpret(), interpreter(inter.clone())
{}

CommandDivider::InterpreterEntity::~InterpreterEntity()
{}

CommandDivider::InterpreterEntity::InterpreterEntity(InterpreterEntity&& other)
    :dataToInterpret(std::move(other.dataToInterpret)),
    interpreter(std::move(other.interpreter))
{}


CommandDivider::InterpreterEntity& CommandDivider::InterpreterEntity::operator=(InterpreterEntity&& other){
    dataToInterpret = std::move(other.dataToInterpret);
    interpreter = std::move(other.interpreter);

    return *this;
}



CommandDivider::CommandDivider()
    :interpreters()
{}

CommandDivider::~CommandDivider()
{}

void CommandDivider::clearWhitespace(std::stringstream& stream) const {
    int getChar;
    while(!stream.eof() && ((getChar = stream.get()) == ' ' || getChar == '\n')) {}
    if(!stream.eof()) stream.unget();
}

void CommandDivider::getLine(std::stringstream& extractFrom, std::string& extractTo) const{
    clearWhitespace(extractFrom);
    std::getline(extractFrom, extractTo);
}

bool CommandDivider::divideByKeyWords(std::stringstream& command){
    std::vector<std::unique_ptr<InterpreterEntity>>::iterator iterLast;
    std::stringstream &ss = command;

    while(!ss.eof()){   // get all commands
        std::string word, tmp;
        getLine(ss, tmp);

        std::stringstream sCommand(tmp);

        bool isKeyword = false;
        bool isFlag = false;
        bool contLoop = false;

        while(!sCommand.eof()){ // get one command at a time
            if(!(sCommand >> word)) return true;

            if(word[0] == '-' && !isKeyword) return true;

            if(word[0] == '-'){ // if flags
                word.erase(0, 1);
                if(word.size() == 0) return true;

                if((*iterLast)->interpreter->isCommand(word)){
                    isFlag = true;
                    (*iterLast)->dataToInterpret.back().commands.push_back(word);
                    (*iterLast)->dataToInterpret.back().commandsArg.push_back(std::vector<std::string>());
                }
                else return true;

                continue;
            }

            if(isKeyword && isFlag){
                (--(*iterLast)->dataToInterpret.back().commandsArg.end())->push_back(word);
                continue;
            }

            for(auto it = interpreters.begin(); it != interpreters.end(); ++it){    // search for keyword
                if((*it)->interpreter->isKeyword(word)){
                    if(isKeyword) return true;
                    isKeyword = true;
                    (*it)->dataToInterpret.push_back(CommandDivider::InterpreterEntity::Data());
                    (*it)->dataToInterpret.back().extractedKeyword = word;
                    iterLast = it;
                    contLoop = true;
                    break;
                }
            }

            if(contLoop){
                contLoop = false;
                continue;
            }

            return true;
        }
    }

    return false;
}

void CommandDivider::clear(){
    for(auto& it : interpreters){
        it->dataToInterpret.clear();  
    }
}


bool CommandDivider::runCommand(const std::string& command, bool clearBuf){
    clear();
    std::stringstream stream(command);

    if(divideByKeyWords(stream)) return true; // here validate string

    for(auto& it : interpreters){
        for(const auto& data : it->dataToInterpret){
            if(it->interpreter->runCommand(data.extractedKeyword, data.commands, data.commandsArg)) return true;
        }
    }

    if(clearBuf) this->clear();

    return false;
}

bool CommandDivider::loadCommandsFromFile(const std::string path, bool clearBuf){
    
    std::ifstream file;
    std::stringstream fileBuf;
    std::string com;

    file.open(path);
    
    if(!file) return true;

    fileBuf << file.rdbuf();
    fileBuf >> std::skipws;

    com = fileBuf.str();

    if(runCommand(com, clearBuf)) return true;

    file.close();

    return false;
}


bool CommandDivider::addInterpreter(const CommandInterpreter& inter){
    for(auto& it : interpreters){
        if(typeid(*it) == typeid(inter)) return true;
    }

    interpreters.push_back(std::make_unique<InterpreterEntity>(inter));
    return false;
}



#endif