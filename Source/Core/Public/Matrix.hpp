#pragma once

#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "Math.hpp"

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

    bool operator==(const NMMatrix& other) const
    {
        if (width != other.width || height != other.height)
        {
            return false;
        }

        for (std::size_t i = 0; i < data.size(); ++i)
        {
            if (!nmmath::FloatEquals(data[i], other.data[i]))
            {
                return false;
            }
        }

        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const NMMatrix& matrix)
    {
        os << std::setprecision(3) << std::fixed;

        // get the largest number of digits in the matrix
        int maxDigits = 0;
        for (auto& val : matrix.data)
        {
            auto digits = static_cast<int>(std::to_string(val).length());
            if (digits > maxDigits)
            {
                maxDigits = digits;
            }
        }

        for (std::size_t y = 0; y < matrix.height; ++y)
        {
            os << "| ";
            for (std::size_t x = 0; x < matrix.width; ++x)
            {
                auto idx = y * matrix.width + x;
                os << std::setw(maxDigits - 2) << matrix.data[idx] << " ";
            }
            os << "|\n";
        }

        return os;
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