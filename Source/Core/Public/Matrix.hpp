#pragma once

#include <limits>
#include <vector>

class NMMatrix
{
public:

    NMMatrix() : NMMatrix(4, 4) {}

    NMMatrix(std::size_t width, std::size_t height, const float& value = 0.0f) : width(width), height(height)
    {
        data.resize(width * height, value);
    }

    NMMatrix(const std::vector<std::vector<float>>& multiDimensionalData)
    {
        height = multiDimensionalData.size();
        width = multiDimensionalData[0].size();

        data.resize(width * height);
        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                data[y * width + x] = multiDimensionalData[y][x];
            }
        }
    }

    NMMatrix(std::size_t width, std::size_t height, const std::vector<float>& data)
        : width(width), height(height), data(data)
    {
    }

    inline std::size_t GetWidth() const { return width; }
    inline std::size_t GetHeight() const { return height; }

    inline float Get(std::size_t x, std::size_t y) const
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }

        return data[y * width + x];
    }

    inline void Set(std::size_t x, std::size_t y, float value)
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            data[y * width + x] = value;
        }
    }

protected:

    std::size_t width;
    std::size_t height;
    std::vector<float> data;
};
