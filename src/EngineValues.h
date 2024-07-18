#pragma once

#include <iostream>
#include <algorithm>
#include <SDL.h>

enum class Direction {
	Left,
	Right,
	Up,
	Down
};

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


