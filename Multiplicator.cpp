#include "Multiplicator.h"
#include <math.h>

std::string Multiplicator::generateRandomDigits(std::uint32_t numberOfDigits)
{
    static std::string digits = "0123456789";

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(0, digits.size() - 1);

    std::string s;

    for (std::int64_t i = 0; i < numberOfDigits; i++)
    {
        s.push_back(digits.at(dist(mt)));
    }

    return s;
}

std::string Multiplicator::integerToString(std::uint8_t n)
{
    std::string s;

    if (n > 9)
    {
        s.append(1, integerToChar(n / 10));
        s.append(1, integerToChar(n % 10));
    }
    else
    {
        s.append(1, integerToChar(n));
    }

    return s;
}

std::uint8_t Multiplicator::integerToChar(std::uint8_t n)
{
    return n + '0';
}

std::uint8_t Multiplicator::charToInteger(std::uint8_t c)
{
    return c - '0';
}

std::string Multiplicator::addition(std::string a, std::string b)
{
    auto maxLength = std::max(a.length(), b.length());
    auto newLength = maxLength + 1;

    a.insert(a.begin(), newLength - a.length(), '0');
    b.insert(b.begin(), newLength - b.length(), '0');

    std::string c(newLength, '0');
    auto carry = 0;

    for (std::int64_t i = newLength - 1; i >= 0; i--)
    {
        auto diff = charToInteger(a[i]) + charToInteger(b[i]) + carry;

        if (diff > 9)
        {
            diff -= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        c[i] = integerToChar(diff);
    }

    c.erase(0, c.find_first_not_of('0'));

    if (c.length() == 0)
    {
        return "0";
    }

    return c;
}

std::string Multiplicator::substraction(std::string a, std::string b)
{
    auto maxLength = std::max(a.length(), b.length());
    auto newLength = maxLength + 1;

    a.insert(a.begin(), newLength - a.length(), '0');
    b.insert(b.begin(), newLength - b.length(), '0');

    std::string c(newLength, '0');
    auto carry = 0;

    for (std::int64_t i = newLength - 1; i >= 0; i--) {
        auto diff = charToInteger(a[i]) - charToInteger(b[i]) - carry;

        if (diff < 0)
        {
            diff += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        c[i] = integerToChar(diff);
    }

    c.erase(0, c.find_first_not_of('0'));

    if (c.length() == 0)
    {
        return "0";
    }

    return c;
}

std::string Multiplicator::shiftLeft(std::string a, std::size_t n)
{
    a.insert(a.end(), n, '0');
    return a;
}

std::string Multiplicator::shiftRight(std::string a, std::size_t n)
{
    a.insert(a.begin(), n, '0');
    return a;
}

std::string Multiplicator::multiplyByOneDigit(std::string a, std::uint8_t b)
{
    std::string c(a.length(), '0');
    std::vector<uint64_t> vec_c(a.length());
    auto carry = 0;

    for (std::int64_t i = a.length() - 1; i >= 0; i--)
    {
        vec_c[i] = charToInteger(a[i]) * b;

        vec_c[i] += carry;

        if (vec_c[i] >= 10)
        {
            carry = vec_c[i] / 10;
            vec_c[i] %= 10;
        }
        else
        {
            carry = 0;
        }
    }

    for (std::int64_t i = 0; i < c.length(); i++)
    {
        c[i] = integerToChar(vec_c[i]);
    }

    if (carry > 0)
    {
        c = shiftRight(c, 1);
        c[0] = integerToChar(carry);
    }

    return c;
}

std::string Multiplicator::gradeSchoolMultiply(std::string a, std::string b)
{
    std::string c(a.length() + b.length(), '0');

    auto j = 0;

    for (std::int64_t i = a.length() - 1; i >= 0; i--) {
        auto p = multiplyByOneDigit(b, charToInteger(a[i]));
        p = shiftLeft(p, j);
        c = addition(c, p);
        j += 1;
    }

    return c;
}

std::uint32_t Multiplicator::nextPowerOf2(std::uint32_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

std::string Multiplicator::karatsubaMultiply(std::string x, std::string y)
{
    auto maxLength = std::max(x.length(), y.length());
    auto v = nextPowerOf2(maxLength);
    auto n = v / 2;
    x.insert(0, v - x.length(), '0');
    y.insert(0, v - y.length(), '0');

    if (v == 1)
    {
        return integerToString(charToInteger(x[0]) * charToInteger(y[0]));
    }
    else
    {
        auto a = x.substr(0, n);
        auto b = x.substr(n);
        auto c = y.substr(0, n);
        auto d = y.substr(n);
        auto ac = karatsubaMultiply(a, c);
        auto bd = karatsubaMultiply(d, b);
        auto pq = karatsubaMultiply(addition(a, b), addition(c, d));
        auto abdc = substraction(pq, addition(ac, bd));
        return addition(shiftLeft(ac, n * 2), addition(shiftLeft(abdc, n), bd));
    }
}
std::string Multiplicator::divideAndConquerMultiply(std::string x, std::string y)
{
    auto maxLength = std::max(x.length(), y.length());
    auto v = nextPowerOf2(maxLength);
    auto n = v / 2;

    x.insert(0, v - x.length(), '0');
    y.insert(0, v - y.length(), '0');

    if (v == 1)
    {
        return integerToString(charToInteger(x[0]) * charToInteger(y[0]));
    }
    else
    {
        auto a = x.substr(0, n);
        auto b = x.substr(n);
        auto c = y.substr(0, n);
        auto d = y.substr(n);
        auto ac = divideAndConquerMultiply(a, c);
        auto bd = divideAndConquerMultiply(d, b);
        auto ad = divideAndConquerMultiply(a, d);
        auto bc = divideAndConquerMultiply(b, c);
        auto adbc = substraction(ad, bc);
        return addition(shiftLeft(ac, n * 2), addition(shiftLeft(adbc, n), bd));
    }
}

std::chrono::steady_clock::duration Multiplicator::measureGradeSchoolMultiply(std::string a, std::string b)
{
    auto begin = std::chrono::steady_clock::now();
    gradeSchoolMultiply(a, b);
    auto end = std::chrono::steady_clock::now();
    return (end - begin);
}

std::chrono::steady_clock::duration Multiplicator::measureKaratsubaMultiply(std::string a, std::string b)
{
    auto begin = std::chrono::steady_clock::now();
    karatsubaMultiply(a, b);
    auto end = std::chrono::steady_clock::now();
    return (end - begin);
}

std::chrono::steady_clock::duration Multiplicator::measureDivideAndConquerMultiply(std::string a, std::string b)
{
    auto begin = std::chrono::steady_clock::now();
    divideAndConquerMultiply(a, b);
    auto end = std::chrono::steady_clock::now();
    return (end - begin);
}

void Multiplicator::csvSave(
        std::vector<std::uint32_t> numberOfDigits,
        std::vector<std::chrono::steady_clock::duration> averageGradeSchoolMultiplyDurations,
        std::vector<std::chrono::steady_clock::duration> averageKaratsubaMultiplyDurations,
        std::vector<std::chrono::steady_clock::duration> averageDivideAndConquerMultiplyDurations)
{

    std::ofstream csvFile;
    csvFile.open("results.csv");

    for (std::int64_t i = 0; i < numberOfDigits.size(); i++)
    {
        csvFile
                << numberOfDigits.at(i) << ","
                << std::chrono::duration_cast<std::chrono::milliseconds>(averageGradeSchoolMultiplyDurations.at(i)).count() << ","
                << std::chrono::duration_cast<std::chrono::milliseconds>(averageKaratsubaMultiplyDurations.at(i)).count() << ","
                << std::chrono::duration_cast<std::chrono::milliseconds>(averageDivideAndConquerMultiplyDurations.at(i)).count()
                << std::endl;
    }

    csvFile.close();
}

void Multiplicator::doTests(std::uint32_t totalNumberOfDigits)
{
    std::vector<std::uint32_t> numberOfDigits;
    std::vector<std::chrono::steady_clock::duration> averageGradeSchoolMultiplyDurations;
    std::vector<std::chrono::steady_clock::duration> averageKaratsubaMultiplyDurations;
    std::vector<std::chrono::steady_clock::duration> averageDivideAndConquerMultiplyDurations;

    for (std::int64_t i = 1; i <= totalNumberOfDigits; i++)
    {
        std::chrono::steady_clock::duration averageGradeSchoolMultiplyDuration{};
        std::chrono::steady_clock::duration averageKaratsubaMultiplyDuration{};
        std::chrono::steady_clock::duration averageDivideAndConquerMultiplyDuration{};
        auto tries = 3;
        for (std::int64_t j = 0; j < tries; j++)
        {
            auto a = generateRandomDigits(i);
            auto b = generateRandomDigits(i);
            auto gradeSchoolMultiplyDuration = measureGradeSchoolMultiply(a, b);
            auto karatsubaMultiplyDuration = measureKaratsubaMultiply(a, b);
            auto divideAndConquerMultiplyDuration = measureDivideAndConquerMultiply(a, b);

            averageGradeSchoolMultiplyDuration += gradeSchoolMultiplyDuration;
            averageKaratsubaMultiplyDuration += karatsubaMultiplyDuration;
            averageDivideAndConquerMultiplyDuration += divideAndConquerMultiplyDuration;
        }

        averageGradeSchoolMultiplyDuration /= tries;
        averageKaratsubaMultiplyDuration /= tries;
        averageDivideAndConquerMultiplyDuration /= tries;

        numberOfDigits.push_back(i);
        averageGradeSchoolMultiplyDurations.push_back(averageGradeSchoolMultiplyDuration);
        averageKaratsubaMultiplyDurations.push_back(averageKaratsubaMultiplyDuration);
        averageDivideAndConquerMultiplyDurations.push_back(averageDivideAndConquerMultiplyDuration);

        if(i < 100)
        {
            i+=25;
        }
        if(i >= 100 && i<1000)
        {
            i+=100;
        }
        if(i >= 1000 && i<10000)
        {
            i+=1000;
        }
        if(i >= 10000 && i<50000)
        {
            i+=10000;
        }
    }

    csvSave(numberOfDigits,
            averageGradeSchoolMultiplyDurations,
            averageKaratsubaMultiplyDurations,
            averageDivideAndConquerMultiplyDurations);
}
