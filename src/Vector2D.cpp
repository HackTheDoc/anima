#include "include/Game/Components/Vector2D.h"

const Vector2D Vector2D::ZERO = {0,0};

Vector2D::Vector2D() {
    x = 0;
    y = 0;
}

Vector2D::Vector2D(int x, int y) {
    this->x = x;
    this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vec) {
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

Vector2D& Vector2D::Substract(const Vector2D& vec) {
    this->x -= vec.x;
    this->y -= vec.y;

    return *this;
}

Vector2D& Vector2D::Mutliply(const Vector2D& vec) {
    this->x *= vec.x;
    this->y *= vec.y;

    return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec) {
    this->x /= vec.x;
    this->y /= vec.y;

    return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
    return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
    return v1.Substract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
    return v1.Mutliply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
    return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
    return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
    return this->Substract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec) {
    return this->Mutliply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec) {
    return this->Divide(vec);
}

Vector2D Vector2D::operator*(const int i) const {
    return Vector2D{this->x * i, this->y * i};
}

Vector2D& Vector2D::Zero() {
    this->x = 0;
    this->y = 0;
    return *this;
}

bool operator==(const Vector2D& v1, const Vector2D& v2) {
    return v1.x == v2.x && v1.y == v2.y;
}

bool operator!=(const Vector2D& v1, const Vector2D& v2) {
    return v1.x != v2.x || v1.y != v2.y;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
    stream << "(" << vec.x << ", " << vec.y << ")";
    return stream;
}
