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
/** Klasa odpowiedzialna za poprawne wczytanie polece�*/
class CommandDivider{
    /** Struktura agreguj�ca polecenia*/
    struct InterpreterEntity{
        /** Struktura przechowuj�ca wczytane polecenia.*/
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
    /** Wczytanie s��w kluczowych do odpowiednich strukt�r InterpreterEntity
    *   @return true - b��d
    *   @return false - powodzenie
    */
    bool divideByKeyWords(std::stringstream& command);
    /** Wczytanie linii ze strumienia z pomini�ciem bia�ych znak�w na pocz�tku*/
    void getLine(std::stringstream& extractFrom, std::string& extractTo) const;
    /** Czyszczenie bia�ych znak�w przed poleceniem*/
    void clearWhitespace(std::stringstream& extractFrom) const;
    /** Wyczyszczenie pami�ci agregowanych strukt�r InterpreterEntity*/
    void clear();

public:
    CommandDivider();
    ~CommandDivider();
    CommandDivider(const CommandDivider& other) = delete;
    /** Wykonuje akcje zwi�zane z poleceniem ka�dego z agregowanych interpreter�w.
    *   @return true - b��d
    *   @return false - powodzenie
    */
    bool runCommand(const std::string& command, bool clearBuf = true);
    /** Wczytanie polece� z pliku zamiast konsoli
    *   @return true - b��d
    *   @return false - powodzenie
    */
    bool loadCommandsFromFile(const std::string path, bool clearBuf = true);

    /**
     * @brief Dodaje interpreter komendy.
     * 
     * Tylko jeden interpreter danej klasy mo�e instnie� w shell-u.
     * 
     * @param inter CommandInterpreter&
     * @return true - je�eli istnia� ju� interpreter danej komendy
     * @return false - je�eli stworzono nowy interpreter komendy
     */
    bool addInterpreter(const CommandInterpreter& inter);

    

};


#endif