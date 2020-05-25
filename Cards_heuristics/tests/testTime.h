/**
 * @file testTime.h
 * @brief Plik klasy testu z pomiarem czasu
 * 
 */

#ifndef TEST_TIME_H
#define TEST_TIME_H

#include "testCardsHeuristic.h"

#include <chrono>

/**
 * @brief Klasa testu z pomiarem czasu
 * 
 */
class TestTime: public TestCardsHeuristic{
	/**
	 * @brief Nazwy trybów działania programu
	 * 
	 */
    const static char* keyword[3];

public:
	/**
	 * @brief Stwórz nowy obiekt Test Time
	 * 
	 * @param int maksymalna ilość pokoleń
	 */
    TestTime(const unsigned int& maxNumberOfIterations);

	/**
	 * @brief Usuń obiekt Test Time
	 * 
	 */
	virtual ~TestTime();

	/**
	 * @brief Stwórz nowy obiekt Test Time kopiując inny
	 * 
	 * @param other obiekt do skopiowania
	 */
	TestTime(const TestTime& other);

	/**
	 * @brief Uruchom odpowiedni test metody genetycznej
	 * 
	 * @param keyword nazwa trybu działania
	 * @param path ścieżka do pliku z poleceniami
	 */
    virtual int runTest(const std::string& keyword, const std::string& path) override;

	/**
	 * @brief Uruchom test metody genetycznej
	 * 
	 * @param path ścieżka do pliku z poleceniami
	 */
	virtual void runTestBasic(const std::string& path) override;

	/**
	 * @brief Uruchom test algorytmu genetycznego z minimalnym wypisem do strumienia
	 * 
	 * @param path ścieżka do pliku z poleceniami
	 * @return int reprezentacja wyniku
	 */
	virtual int runTestSilent(const std::string& path) override;

	/**
	 * @brief Uruchom test algorytmu zachłannego
	 * 
	 * @param path ścieżka do pliku z poleceniami
	 */
	virtual void runTestHeuristic(const std::string& path) override;

	/**
	 * @brief Uruchom test algorytmu z minimalnym wypisem do strumienia
	 * 
	 * @param path ścieżka do pliku z poleceniami
	 * @return int reprezentacja wyniku
	 */
	virtual int runTestHeuristicSilent(const std::string& path) override;

	/**
	 * @brief Kopiowanie obiektu klasy TestNormal
	 * 
	 * @return TestNormal* wskaźnik na kopię
	 */
	virtual TestTime* clone() const override;

	/**
	 * @brief Sprawdź czy string jest trybem działania programu
	 * 
	 * @param word string
	 * @return true jest
	 * @return false nie jest
	 */
	virtual bool isKeyword(const std::string& word) const override; 

};


#endif