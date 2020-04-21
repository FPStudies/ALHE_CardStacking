#ifndef COMMAND_DIVIDER_CPP
#define COMMAND_DIVIDER_CPP

#include "commandDivider.h"

CommandDivider::DividedWord::DividedWord(const CommandInterpreter& inter)
    :extractedKeyword(), restOfPhrases(), interpreter(inter.copy())
{}

CommandDivider::DividedWord::~DividedWord()
{}

CommandDivider::DividedWord::DividedWord(DividedWord&& other)
    :extractedKeyword(std::move(other.extractedKeyword)), 
    restOfPhrases(std::move(other.restOfPhrases)), 
    interpreter(std::move(other.interpreter))
{}


CommandDivider::DividedWord& CommandDivider::DividedWord::operator=(DividedWord&& other){
    extractedKeyword = std::move(other.extractedKeyword);
    restOfPhrases = std::move(other.restOfPhrases);
    interpreter = std::move(other.interpreter);

    return *this;
}



CommandDivider::CommandDivider()
    :interpreters()
{}

CommandDivider::~CommandDivider()
{}

bool CommandDivider::divideByKeyWords(const std::string& command){
    unsigned int begin = 0, end = 0;
    auto lastInter = interpreters.begin();
    bool commandMayBeValid = false;
    bool isOption = false;
    std::vector<std::unique_ptr<DividedWord>>::iterator iterLast;
    
    for(unsigned int i = 0; i < command.size(); ++i){
        if(command[i] == '-') { // options
            if(!commandMayBeValid) return true;
            isOption = true;
        }
        else if(command[i] == ' '){
            if(begin != end){
                std::string word = command.substr(begin, end - begin);
                if(isOption){
                    if(!(*iterLast)->interpreter->isCommand(word)) return true;
                    (*iterLast)->restOfPhrases.push_back(word);
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
    }
    return false;
}

void CommandDivider::clear(){
    for(auto& it : interpreters){
        it->extractedKeyword.clear();
        it->restOfPhrases.clear();
    }
}


bool CommandDivider::runCommand(const std::string& command, bool clearBuf){
    clear();
    if(divideByKeyWords(command)) return true; // here validate string
    
    for(auto& it : interpreters){
        if(it->interpreter->run(it->extractedKeyword, it->restOfPhrases)) return true;
    }

    if(clearBuf) this->clear();

    return false;
}

bool CommandDivider::loadCommandsFromFile(const std::string path){

    std::ifstream file(path);
    char com[127];

    while(!file.eof()){
        file.getline(com, 127);
        std::string command(com);

        remove_if(command.begin(), command.end(), isspace);

        if(command.empty() == 0) continue;

        if(runCommand(command)) return true;
    }

    file.close();

    return false;
}


bool CommandDivider::addInterpreter(const CommandInterpreter& inter){
    for(auto& it : interpreters){
        if(typeid(*it) == typeid(inter)) return true;
    }

    interpreters.push_back(std::make_unique<DividedWord>(inter));
    return false;
}



#endif