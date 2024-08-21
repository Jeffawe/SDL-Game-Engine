#pragma once

#include <iostream>
#include <algorithm>
#include <SDL.h>
#include <sstream>
#include <string>

enum class Direction {
	Left,
	Right,
	Up,
	Down
};

/**
 * @brief Prints a value with optional custom text before and/or after it.
 *
 * This function outputs the provided value to the standard output stream.
 * You can specify custom text to be printed before and/or after the value.
 * If no custom text is provided, the value is printed as-is.
 *
 * @tparam T The type of the value to be printed.
 * @param value The value to print.
 * @param before Optional custom text to print before the value. Defaults to an empty string.
 * @param after Optional custom text to print after the value. Defaults to an empty string.
 */
template<typename T>
static void print(const T& value, const std::string& before = "", const std::string& after = "") {
    // Create a string stream to format the output
    std::ostringstream oss;
    oss << before << value << after;

    // Print the formatted output
    std::cout << oss.str() << std::endl;
}

struct Vector2{
    int x, y;

    Vector2() = default;

    // Constructor
    Vector2(int _x, int _y) : x(_x), y(_y) {}

    Vector2 operator+(const Vector2& otherVector) const {
        return Vector2(x + otherVector.x, y + otherVector.y);
    }

    bool operator>(const Vector2& otherVector) const {
        return (x > otherVector.x && y > otherVector.y);
    }

    bool operator>=(const Vector2& otherVector) const {
        return (x >= otherVector.x && y >= otherVector.y);
    }

    bool operator<(const Vector2& otherVector) const {
        return (x < otherVector.x && y < otherVector.y);
    }

    bool operator<=(const Vector2& otherVector) const {
        return (x <= otherVector.x && y <= otherVector.y);
    }

    bool operator==(const Vector2& otherVector) const {
        return (x == otherVector.x && y == otherVector.y);
    }

    bool operator!=(const Vector2& otherVector) const {
        return (x != otherVector.x && y != otherVector.y);
    }

    Vector2& operator=(const Vector2& otherVector) {
        if (this == &otherVector) return *this;
        x = otherVector.x;
        y = otherVector.y;
        return *this;
    }

    Vector2 operator*(int integerValue) const {
        return Vector2(x * integerValue, y * integerValue);
    }

    Vector2 operator-(const Vector2& otherVector) const {
        return Vector2(x - otherVector.x, y - otherVector.y);
    }

    Vector2 operator/(int integerValue) const {
        return Vector2(x / integerValue, y / integerValue);
    }

    struct HashFunction {
        size_t operator()(const Vector2& vec) const {
            return std::hash<int>()(vec.x) ^ std::hash<int>()(vec.y);
        }
    };

    // Static members declaration
    static const Vector2 zero;
    static const Vector2 unit;
};

// Function to convert string to lowercase
static std::string toLower(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}


