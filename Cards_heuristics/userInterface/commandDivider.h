#ifndef COMMAND_DIVIDER_H
#define COMMAND_DIVIDER_H

/** @file commandDivider.h
*   @brief Plik klasy 
*/

#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>

#include "commandInterpreter.h"
/** Klasa odpowiedzialna za poprawne wczytanie poleceñ*/
class CommandDivider{
    /** Struktura agreguj¹ca polecenia*/
    struct InterpreterEntity{
        /** Struktura przechowuj¹ca wczytane polecenia.*/
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
    /** Wczytanie s³ów kluczowych do odpowiednich struktór InterpreterEntity
    *   @return true - b³¹d
    *   @return false - powodzenie
    */
    bool divideByKeyWords(std::stringstream& command);
    /** Wczytanie linii ze strumienia z pominiêciem bia³ych znaków na pocz¹tku*/
    void getLine(std::stringstream& extractFrom, std::string& extractTo) const;
    /** Czyszczenie bia³ych znaków przed poleceniem*/
    void clearWhitespace(std::stringstream& extractFrom) const;
    /** Wyczyszczenie pamiêci agregowanych struktór InterpreterEntity*/
    void clear();

public:
    CommandDivider();
    ~CommandDivider();
    CommandDivider(const CommandDivider& other) = delete;
    /** Wykonuje akcje zwi¹zane z poleceniem ka¿dego z agregowanych interpreterów.
    *   @return true - b³¹d
    *   @return false - powodzenie
    */
    bool runCommand(const std::string& command, bool clearBuf = true);
    /** Wczytanie poleceñ z pliku zamiast konsoli
    *   @return true - b³¹d
    *   @return false - powodzenie
    */
    bool loadCommandsFromFile(const std::string path, bool clearBuf = true);

    /**
     * @brief Dodaje interpreter komendy.
     * 
     * Tylko jeden interpreter danej klasy mo¿e instnieæ w shell-u.
     * 
     * @param inter CommandInterpreter&
     * @return true - je¿eli istnia³ ju¿ interpreter danej komendy
     * @return false - je¿eli stworzono nowy interpreter komendy
     */
    bool addInterpreter(const CommandInterpreter& inter);

    

};


#endif