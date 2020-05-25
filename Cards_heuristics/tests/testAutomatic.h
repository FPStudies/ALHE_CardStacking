// /**
//  * @file testNormal.h
//  * @brief Plik klasy testu seryjnego
//  * 
//  */
// #ifndef TEST_AUTO_H
// #define TEST_AUTO_H

// #include "testCardsHeuristic.h"

// #include <chrono>

// /**
//  * @brief Klasa testu seryjnego
//  * 
//  */
// class TestAuto : public TestCardsHeuristic {
// 	/**
// 	 * @brief Nazwa trybu działania programu
// 	 * 
// 	 */
// 	const static char* keyword[1];

// public:
// 	TestAuto(const unsigned int& maxNumberOfIterations);
// 	virtual ~TestAuto();
// 	TestAuto(const TestAuto other);

// 	virtual void runTest(const std::string& path) override;
// 	virtual TestAuto* clone() const override;

// 	virtual bool isKeyword(const std::string& word) const override;

// };


// #endif
