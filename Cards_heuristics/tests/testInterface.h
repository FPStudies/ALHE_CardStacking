/**
 * @file testInterface.h
 * @brief Plik klasy interfejsu testów
 * 
 */

#ifndef TEST_INTERFACE_H
#define TEST_INTERFACE_H


#include <iostream>
#include <limits>

/**
 * @brief Klasa interfejsu testów
 * 
 */
class TestInterface
{
public:
	/**
	 * @brief Stwórz nowy obiekt Test Interface
	 * 
	 */
	TestInterface() {};

	/**
	 * @brief Usuń obiekt Test Interface
	 * 
	 */
	~TestInterface() {};

	TestInterface(const TestInterface& other) = delete;

	/*
	 * @brief Uruchom test
	 * 
	 * @param path ścieżka do pliku z poleceniami
	 */
	//virtual void runTest(const std::string& path) = 0;

	/**
	 * @brief Skopiuj obiekt klasy TestInterface
	 * 
	 * @return TestInterface* wskaźnik na kopię
	 */
	virtual TestInterface* clone() const = 0;

	/**
	 * @brief Sprawdź czy parametry algorytmu są prawidłowe
	 * 
	 * @return true są
	 * @return false nie są
	 */
	virtual bool isDataValid() const = 0;
};


#endif