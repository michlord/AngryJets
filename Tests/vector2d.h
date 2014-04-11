#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class Vector2D
{

public:
    Vector2D(float x = 0, float y = 0);
    ~Vector2D() {}

    void Rotate( const float angle );
    float Magnitude() const;
    float Normalize();
    float DotProduct( const Vector2D& v2 ) const;
    float CrossProduct( const Vector2D& v2 ) const;
    Vector2D Project(const Vector2D& v2) const;
    Vector2D GetRightHandOrthogonalVector();
    Vector2D GetLeftHandOrthogonalVector();

    static Vector2D Zero();
    static float Distance( const Vector2D& v1, const Vector2D& v2);
    static float DistanceSquared( const Vector2D& v1, const Vector2D& v2);

    Vector2D& operator= ( const Vector2D& v2 );

    Vector2D& operator+= ( const Vector2D& v2 );
    Vector2D& operator-= ( const Vector2D& v2 );
    Vector2D& operator*= ( const float scalar);
    Vector2D& operator/= ( const float scalar);

    const Vector2D operator+( const Vector2D &v2 ) const;
    const Vector2D operator-( const Vector2D &v2 ) const;
    const Vector2D operator*( const float scalar ) const;
    const Vector2D operator/( const float scalar ) const;

    bool operator== ( const Vector2D& v2 ) const;
    bool operator!= ( const Vector2D& v2 ) const;

public:
    float x, y;
};

#endif // VECTOR2D_H
