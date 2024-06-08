#pragma once

enum class Direction {
	Left,
	Right,
	Up,
	Down
};

struct Vector2 {
	int x, y;

	Vector2() = default;

	// Constructor
	Vector2(int _x, int _y) : x(_x), y(_y) {}

	Vector2 operator+(const Vector2 otherVector) const {
		return Vector2(x + otherVector.x, y + otherVector.y);
	}

	Vector2 operator*(const int integerValue) const {
		return Vector2(x * integerValue, y * integerValue);
	}

	Vector2 operator-(const Vector2 otherVector) const {
		return Vector2(x - otherVector.x, y - otherVector.y);
	}

	Vector2 operator/(const int integerValue) const {
		return Vector2(x / integerValue, y / integerValue);
	}
};

// Function to convert string to lowercase
static std::string toLower(const std::string& str) {
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}
