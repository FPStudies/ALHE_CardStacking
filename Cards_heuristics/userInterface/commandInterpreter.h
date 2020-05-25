/**
 * @file commandInterpreter.h
 * @brief Plik klasy interpretatora poleceń.
 * 
 */

#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <string>

/**
 * @brief Klasa interpretatora poleceń. 
 * Wykorzystywana do rozpoznawania słów kluczowych z wczytanego polecenia i odpowiedniej zmiany działania programu.
 * 
 */
class CommandInterpreter{

public:
    /**
     * @brief Stwórz nowy obiekt Command Interpreter
     * 
     */
    CommandInterpreter() {};

    /**
     * @brief Usuń obiekt Command Interpreter
     * 
     */
    virtual ~CommandInterpreter() {};

    CommandInterpreter(const CommandInterpreter& other) = delete;

    /**
     * @brief Wykonanie akcji związanych z poleceniem.
     * Może być wywoływana rekurencyjnie.
     * 
     * @param keyword tryb działania programu
     * @param flags kolejne flagi wykonania
     * @param dataToFlags argumenty flag wykonania
     * @return true jeżeli nie znaleziono polecenia albo nie ma już więcej operacji do wykonania, przydatne w rekurencji
     * @return false w innych wypadkach
     */
    virtual bool runCommand(const std::string& keyword, const std::vector<std::string>& flags, const std::vector<std::vector<std::string>>& dataToFlags) = 0;
    
    /**
     * @brief Sprawdzenie czy string jest słowem kluczowym
     * 
     * @param word sprawdzany string
     * @return true jest słowem kluczowym
     * @return false nie jest słowem kluczowym
     */
    virtual bool isKeyword(const std::string& word) const = 0;

    /**
     * @brief Sprawdzenie czy string jest komendą
     * 
     * @param command sprawdzany string
     * @return true jest komendą
     * @return false nie jest komendą
     */
    virtual bool isCommand(const std::string& command) const = 0;

    /*
     * @brief 
     * 
     * @param command 
     * @param string 
     * @return true 
     * @return false 
     */
    //virtual bool expectedStringAfterCommand(const std::string& command, const std::string& string) const = 0;

    /**
     * @brief Kopiowanie obiektu CommandInterpreter
     * 
     * @return CommandInterpreter* wskaźnik na powstałą kopię
     */
    virtual CommandInterpreter* clone() const = 0;
};

#endif