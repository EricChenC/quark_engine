#pragma once

#include <glm/glm.hpp>

struct Ray
{
    glm::vec3 direction;
    glm::vec3 origion;
};


struct Rect
{    

/// <summary>
/// static method
/// </summary>
public:
    static Rect MinMaxRect(float xmin, float ymin, float xmax, float ymax) {
        return Rect(xmin, ymin, xmax, ymax);
    }

    static Rect Zero() {
        return Rect(0, 0, 0, 0);
    }


public:
    Rect() 
    {
    }

    Rect(const float& x, const float& y, const float& width, const float& height) 
        :x_(x),
        y_(y),
        width_(width),
        height_(height)
    {
    }

    bool Contains(const glm::vec2& point) {
        return true;
    }

    bool Contains(const glm::vec3& point) {
        return true;
    }

    bool Contains(const glm::vec3& point, bool allowInverse) {
        return true;
    }


    bool Overlaps(const Rect& rect) {
        return true;
    }

    bool Overlaps(const Rect& rect, bool allowInverse) {
        return true;
    }

    void Set(const float& x, const float& y, const float& width, const float& height) {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
    }




public:
    float x_;

    float y_;

    float width_;

    float height_;

    float center_;

    glm::vec2 max_;

    glm::vec2 min_;

    /// <summary>
    /// The X and Y position of the rectangle.
    /// </summary>
    glm::vec2 position_;

    glm::vec2 size_;

    float xMax_;

    float xMin_;

    float yMax_;

    float yMin_;

};