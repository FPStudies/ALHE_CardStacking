/**
 * @file testNormal.h
 * @brief Plik klasy podstawowego testu
 * 
 */
#ifndef TEST_NORMAL_H
#define TEST_NORMAL_H

#include "testInterface.h"
#include "testCardsHeuristic.h"

#include <fstream>
#include <iostream>
#include <sstream>

/**
 * @brief Klasa podstawowego testu
 * 
 */
class TestNormal: public TestCardsHeuristic{
	/**
	 * @brief Nazwy trybów działania programu
	 * 
	 */
	const static char* keyword[4];

public:
	/**
	 * @brief Stwórz nowy obiekt Test Normal
	 * 
	 * @param int maksymalna ilość pokoleń
	 */
	TestNormal(const unsigned int& maxNumberOfIterations);

	/**
	 * @brief Usuń obiekt Test Normal
	 * 
	 */
	virtual ~TestNormal();

	/**
	 * @brief Stwórz nowy obiekt Test Normal kopiując inny
	 * 
	 * @param other obiekt do skopiowania
	 */
	TestNormal(const TestNormal& other);

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
	virtual TestNormal* clone() const override;

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