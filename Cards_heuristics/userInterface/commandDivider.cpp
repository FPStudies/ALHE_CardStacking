#ifndef COMMAND_DIVIDER_CPP
#define COMMAND_DIVIDER_CPP

#include "commandDivider.h"

CommandDivider::DividedWord::DividedWord(const CommandInterpreter& inter)
    :extractedKeyword(), commands(), interpreter(inter.clone())
{}

CommandDivider::DividedWord::~DividedWord()
{}

CommandDivider::DividedWord::DividedWord(DividedWord&& other)
    :extractedKeyword(std::move(other.extractedKeyword)), 
    commands(std::move(other.commands)), 
    interpreter(std::move(other.interpreter))
{}


CommandDivider::DividedWord& CommandDivider::DividedWord::operator=(DividedWord&& other){
    extractedKeyword = std::move(other.extractedKeyword);
    commands = std::move(other.commands);
    interpreter = std::move(other.interpreter);

    return *this;
}



CommandDivider::CommandDivider()
    :interpreters()
{}

CommandDivider::~CommandDivider()
{}

bool CommandDivider::divideByKeyWords(std::stringstream& command){
    //unsigned int begin = 0, end = 0;
    //auto lastInter = interpreters.begin();
    //bool commandMayBeValid = false;
    //bool isOption = false;
    std::vector<std::unique_ptr<DividedWord>>::iterator iterLast;
    std::stringstream &ss = command;
    std::string word, tmp;

    while(!ss.eof()){   // get all commands
        std::getline(ss, tmp);
        std::stringstream sCommand(tmp);
        sCommand >> std::skipws;

        bool isKeyword = false;
        bool isFlag = false;

        while(!sCommand.eof()){ // get one command at a time
            sCommand >> word;
            if(word[0] == '-' && !isKeyword) return true;

            if(word[0] == '-'){ // if flags
                word.erase(0, 1);
                if(word.size() == 0) return true;

                if((*iterLast)->interpreter->isCommand(word)){
                    isFlag = true;
                    (*iterLast)->commands.push_back(word);
                    (*iterLast)->commandsArg.push_back(std::vector<std::string>());
                }
                else return true;

                continue;
            }

            if(isKeyword && isFlag){
                (--(*iterLast)->commandsArg.end())->push_back(word);
                continue;
            }

            for(auto it = interpreters.begin(); it != interpreters.end(); ++it){    // search for keyword
                if((*it)->interpreter->isKeyword(word)){
                    if(isKeyword) return true;
                    isKeyword = true;
                    (*it)->extractedKeyword = word;
                    iterLast = it;
                    continue;
                }
            }

            return true;
        }
    }

    
    
    /*for(unsigned int i = 0; i < command.size(); ++i){
        if(isOption) return true;   // there was '-' and after that space
        else if(command[i] == '-') { // options
            if(!commandMayBeValid) return true;
            isOption = true;
        }
        else if(command[i] == ' '){ // end of options or some word

        }
        else {  // if there wasn`t space or '-', so there is some word
            ++end;
            isOption = false;
        }


        if(command[i] == '-') { // options
            if(!commandMayBeValid) return true;
            isOption = true;
        }
        else if(command[i] == ' '){
            if(begin != end){
                std::string word = command.substr(begin, end - begin);
                if(isOption){
                    if(!(*iterLast)->interpreter->isCommand(word)) return true;
                    (*iterLast)->commands.push_back(word);
                }
                else{   // if it is not an option but command name
                    for(auto it = interpreters.begin(); it != interpreters.end(); ++it){
                        if((*it)->interpreter->isKeyword(word)){
                            commandMayBeValid = true;
                            lastInter = it;
                            (*it)->extractedKeyword = word;
                            iterLast = it;
                        }
                        else return true; // do not found that phrase
                    }
                }
            }

            begin = i;
            end = i;
        }
        else {
            ++end;
            isOption = false;
        }
    }*/
    return false;
}

void CommandDivider::clear(){
    for(auto& it : interpreters){
        it->extractedKeyword.clear();
        it->commands.clear();
    }
}


bool CommandDivider::runCommand(const std::string& command, bool clearBuf){
    clear();
    std::stringstream stream(command);

    if(divideByKeyWords(stream)) return true; // here validate string
    
    for(auto& it : interpreters){
        if(it->interpreter->runCommand(it->extractedKeyword, it->commands, it->commandsArg)) return true;
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

    interpreters.push_back(std::move(std::make_unique<DividedWord>(inter)));
    return false;
}



#endif