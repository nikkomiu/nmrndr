#pragma once

#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "NMM/Tuple.hpp"
#include "NMM/Util.hpp"

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

    NMMatrix operator*(const NMMatrix& other) const
    {
        if (width != other.height)
        {
            return NMMatrix();
        }

        std::vector<float> resultData(width * other.height);

        // TODO: solve this without cubic complexity
        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < other.width; ++x)
            {
                float sum = 0.0f;
                for (std::size_t i = 0; i < width; ++i)
                {
                    sum += Get(i, y) * other.Get(x, i);
                }
                resultData[y * other.width + x] = sum;
            }
        }

        return NMMatrix(other.width, height, resultData);
    }

    NMTuple operator*(const NMTuple& tuple) const
    {
        if (width != 4 || height != 4)
        {
            return NMTuple();
        }

        NMMatrix tupleMatrix(1, 4, {tuple.GetX(), tuple.GetY(), tuple.GetZ(), tuple.GetW()});

        auto resultMatrix = *this * tupleMatrix;

        return NMTuple(resultMatrix.Get(0, 0), resultMatrix.Get(0, 1), resultMatrix.Get(0, 2), resultMatrix.Get(0, 3));
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
        if (x >= width || y >= height)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }

        return data[y * width + x];
    }

    inline void Set(std::size_t x, std::size_t y, float value)
    {
        if (x < width && y < height)
        {
            data[y * width + x] = value;
        }
    }

    void Transpose()
    {
        if (width != height)
        {
            return;
        }

        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = y + 1; x < width; ++x)
            {
                std::swap(data[y * width + x], data[x * width + y]);
            }
        }
    }

    float Determinant()
    {
        if (width != height)
        {
            return std::numeric_limits<float>::quiet_NaN();
        }

        if (width == 2)
        {
            return data[0] * data[3] - data[1] * data[2];
        }

        float determinant = 0.0f;
        for (std::size_t x = 0; x < width; ++x)
        {
            determinant += data[x] * Cofactor(0, x);
        }

        return determinant;
    }

    inline bool IsInvertible()
    {
        return !nmmath::FloatEquals(Determinant(), 0.0f);
    }

    NMMatrix Inverse()
    {
        if (!IsInvertible())
        {
            return NMMatrix();
        }

        std::vector<float> resultData(width * height);

        auto determinant = Determinant();
        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                auto cofactor = Cofactor(y, x);
                resultData[x * width + y] = cofactor / determinant;
            }
        }

        return NMMatrix(width, height, resultData);
    }

    NMMatrix Submatrix(std::size_t row, std::size_t column)
    {
        if (width != height)
        {
            return NMMatrix();
        }

        std::size_t idx = 0;
        std::vector<float> resultData((width - 1) * (height - 1));
        for (std::size_t y = 0; y < height; ++y)
        {
            if (y == row)
            {
                continue;
            }

            for (std::size_t x = 0; x < width; ++x)
            {
                if (x == column)
                {
                    continue;
                }

                resultData[idx] = data[y * width + x];
                idx++;
            }
        }

        return NMMatrix(width - 1, height - 1, resultData);
    }

    float Minor(std::size_t row, std::size_t column)
    {
        return Submatrix(row, column).Determinant();
    }

    float Cofactor(std::size_t row, std::size_t column)
    {
        auto minor = Minor(row, column);
        if ((row + column) % 2 == 1)
        {
            minor *= -1.0f;
        }

        return minor;
    }

    static NMMatrix Identity3x3()
    {
        return NMMatrix(3, 3, {1.0f, 0.0f, 0.0f,
                               0.0f, 1.0f, 0.0f,
                               0.0f, 0.0f, 1.0f});
    }

    static NMMatrix Identity4x4()
    {
        return NMMatrix(4, 4, {1.0f, 0.0f, 0.0f, 0.0f,
                               0.0f, 1.0f, 0.0f, 0.0f,
                               0.0f, 0.0f, 1.0f, 0.0f,
                               0.0f, 0.0f, 0.0f, 1.0f});
    }

protected:

    std::size_t width;
    std::size_t height;
    std::vector<float> data;
};
