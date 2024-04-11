#pragma once

#include <iostream>

/// @brief classic 2D vector class
class Vector2D {
public:
    int x;
    int y;

    Vector2D();
    Vector2D(const int x, const int y);

    Vector2D& Add(const Vector2D& vec);
    Vector2D& Substract(const Vector2D& vec);
    Vector2D& Mutliply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);

    Vector2D operator*(const int i) const;
    Vector2D& Zero();
    bool isZero();

    friend bool operator==(const Vector2D& v1, const Vector2D& v2);
    friend bool operator!=(const Vector2D& v1, const Vector2D& v2);
    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
};
