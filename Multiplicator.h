//
// Created by Daria on 16.04.2020.
//
#pragma once

#ifndef IVANOVABIGHW_MULTIPLICATOR_H
#define IVANOVABIGHW_MULTIPLICATOR_H
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

class Multiplicator {
public:
    static std::string generateRandomDigits(std::uint32_t);
    static std::string integerToString(std::uint8_t);
    static std::uint8_t integerToChar(std::uint8_t);
    static std::uint8_t charToInteger(std::uint8_t);
    static std::string addition(std::string, std::string);
    static std::string substraction(std::string, std::string);
    static std::string shiftLeft(std::string, std::size_t);
    static std::string shiftRight(std::string, std::size_t);
    static std::uint32_t nextPowerOf2(std::uint32_t);
    static std::string multiplyByOneDigit(std::string, std::uint8_t);

    static std::string gradeSchoolMultiply(std::string, std::string);
    static std::string karatsubaMultiply(std::string, std::string);
    static std::string divideAndConquerMultiply(std::string, std::string);

    static std::chrono::steady_clock::duration measureGradeSchoolMultiply(std::string, std::string);
    static std::chrono::steady_clock::duration measureKaratsubaMultiply(std::string, std::string);
    static std::chrono::steady_clock::duration measureDivideAndConquerMultiply(std::string, std::string);

    static void csvSave(
            std::vector<std::uint32_t>, std::vector<std::chrono::steady_clock::duration>,
            std::vector<std::chrono::steady_clock::duration>, std::vector<std::chrono::steady_clock::duration>);

    static void doTests(std::uint32_t);
};


#endif //IVANOVABIGHW_MULTIPLICATOR_H