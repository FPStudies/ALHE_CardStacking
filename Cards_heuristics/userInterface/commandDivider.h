/**
 * @file commandDivider.h
 * @brief Plik klasy odpowiedzialnej za poprawne wczytywanie poleceń
 * 
 */

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

/**
 * @brief Klasa odpowiedzialna za poprawne wczytanie poleceń
 * 
 */
class CommandDivider{

    /**
     * @brief Struktura agregująca polecenia dla danego interpretatora
     * 
     */
    struct InterpreterEntity{

        /**
         * @brief Struktura przechowująca wczytane polecenia
         * 
         */
        struct Data{

            /**
             * @brief Tryb działania programu
             * 
             */
            std::string extractedKeyword;

            /**
             * @brief Flagi wykonania
             * 
             */
            std::vector<std::string> commands;

            /**
             * @brief Argumenty flag
             * 
             */
            std::vector<std::vector<std::string>> commandsArg;

            /**
             * @brief Stwórz nowy obiekt Data
             * 
             */
            Data();

            /**
             * @brief Usuń obiekt Data
             * 
             */
            ~Data();

            Data(const Data& other) = delete;

            /**
             * @brief Stwórz nowy obiekt Data przenosząć wartości innego
             * 
             * @param other R-referencja na obiekt Data, którego wartości zostaną przeniesione
             */
            Data(Data&& other);

            /**
             * @brief Przenoszący operator przypisania
             * 
             * @param other R-referencja na obiekt Data, którego wartości zostaną przeniesione
             * @return Data& referencja na obiekt Data, któremu przypisano wartości
             */
            Data& operator=(Data&& other);
        };

        /**
         * @brief Zbiór poleceń do interpretacji
         * 
         */
        std::vector<Data> dataToInterpret;

        /**
         * @brief Interpretator poleceń
         * 
         */
        std::unique_ptr<CommandInterpreter> interpreter;

        InterpreterEntity(const InterpreterEntity& other) = delete;

        /**
         * @brief Stwórz nowy obiekt Interpreter Entity
         * 
         * @param inter Interpretator polceń
         */
        InterpreterEntity(const CommandInterpreter& inter);

        /**
         * @brief Usuń obiekt Interpreter Entity
         * 
         */
        ~InterpreterEntity();

        /**
         * @brief Stwórz nowy obiekt Interpreter Entity przenosząć wartości innego
         * 
         * @param other R-referencja na obiekt Interpreter Entity, którego wartości zostaną przeniesione
         */
        InterpreterEntity(InterpreterEntity&& other);

        /**
         * @brief Przenoszący operator przypisania
         * 
         * @param other R-referencja na obiekt Interpreter Entity, którego wartości zostaną przeniesione
         * @return InterpreterEntity& referencja na obiekt Interpreter Entity, któremu przypisano wartości
         */
        InterpreterEntity& operator=(InterpreterEntity&& other);
    };

    /**
     * @brief Zbiór interpretatorów poleceń wraz z agregacją poleceń dla nich
     * 
     */
    std::vector<std::unique_ptr<InterpreterEntity>> interpreters;

   /**
    * @brief Wczytanie słów kluczowych do odpowiednich struktur InterpreterEntity
    * 
    * @param command Strumień z komendą
    * @return true błąd
    * @return false powodzenie
    */
    bool divideByKeyWords(std::stringstream& command);

    /**
     * @brief Wczytanie linii ze strumienia z pominięciem białych znaków na początku
     * 
     * @param extractFrom strumień wejściowy
     * @param extractTo string, do którego zapisany zostanie przetworzony strumień
     */
    void getLine(std::stringstream& extractFrom, std::string& extractTo) const;

    /**
     * @brief Czyszczenie białych znaków przed poleceniem
     * 
     * @param extractFrom strumień wejściowy
     */
    void clearWhitespace(std::stringstream& extractFrom) const;

    /**
     * @brief Wyczyszczenie pamięci agregowanych struktur InterpreterEntity
     * 
     */
    void clear();

public:
    /**
     * @brief Stwórz nowy obiekt Command Divider
     * 
     */
    CommandDivider();

    /**
     * @brief Usuń obiekt Command Divider
     * 
     */
    ~CommandDivider();

    CommandDivider(const CommandDivider& other) = delete;

   /**
    * @brief Wykonuje komendę użytkownika
    * 
    * @param command komenda
    * @param clearBuf opcja wyczyszczenia struktur InterpreterEntity po zakończeniu wykonywania
    * @return true bład
    * @return false powodzenie
    */
    bool runCommand(const std::string& command, bool clearBuf = true);

   /**
    * @brief Wczytanie poleceń z pliku zamiast konsoli
    * 
    * @param path ścieżka do pliku
    * @param clearBuf 
    * @return true błąd
    * @return false powodzenie
    */
    bool loadCommandsFromFile(const std::string path, bool clearBuf = true);

    /**
     * @brief Dodaje interpretator komendy.
     * Tylko jeden interpretator danej klasy może instnieś w shell-u.
     * 
     * @param inter interpretator
     * @return true jeżeli istniał już interpretator danej komendy
     * @return false jeżeli stworzono nowy interpretator komendy
     */
    bool addInterpreter(const CommandInterpreter& inter);

    
};


#endif