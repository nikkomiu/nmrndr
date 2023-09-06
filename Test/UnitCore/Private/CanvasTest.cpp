#include <gtest/gtest.h>

#include "NMCore/Canvas.hpp"

class NMCanvasTest : public ::testing::Test
{
};

TEST_F(NMCanvasTest, CreateCanvas)
{
    // Given
    NMCanvas canvas;

    // Then
    ASSERT_EQ(canvas.GetWidth(), 10);
    ASSERT_EQ(canvas.GetHeight(), 10);

    for (int y = 0; y < canvas.GetHeight(); ++y)
    {
        for (int x = 0; x < canvas.GetWidth(); ++x)
        {
            ASSERT_EQ(canvas.ReadPixel(x, y), NMColor(0.0f, 0.0f, 0.0f));
        }
    }
}

// Scenario: Can check if canvas is a specific size
TEST_F(NMCanvasTest, IsSize)
{
    // Given
    NMCanvas canvas;

    // Then
    ASSERT_TRUE(canvas.IsSize(10, 10));
    ASSERT_FALSE(canvas.IsSize(20, 20));
    ASSERT_FALSE(canvas.IsSize(10, 20));
}

// Scenario: Can check if canvas is a specific size when resized
TEST_F(NMCanvasTest, IsSize_Resized)
{
    // Given
    NMCanvas canvas;

    // When
    canvas.Resize(20, 20);

    // Then
    ASSERT_FALSE(canvas.IsSize(10, 10));
    ASSERT_TRUE(canvas.IsSize(20, 20));
}

// Scenario: Can check if canvas is a specific size when custom start size
TEST_F(NMCanvasTest, IsSize_CustomStartSize)
{
    // Given
    NMCanvas canvas(20, 20);

    // Then
    ASSERT_FALSE(canvas.IsSize(10, 10));
    ASSERT_TRUE(canvas.IsSize(20, 20));
}

// Scenario: Can resize a canvas
TEST_F(NMCanvasTest, ResizeCanvas)
{
    // Given
    NMCanvas canvas(10, 10);

    // When
    canvas.Resize(20, 30);

    // Then
    ASSERT_EQ(canvas.GetWidth(), 20);
    ASSERT_EQ(canvas.GetHeight(), 30);

    for (int y = 0; y < canvas.GetHeight(); ++y)
    {
        for (int x = 0; x < canvas.GetWidth(); ++x)
        {
            ASSERT_EQ(canvas.ReadPixel(x, y), NMColor(0.0f, 0.0f, 0.0f));
        }
    }
}

// Scenario: Can resize a canvas to a smaller size
TEST_F(NMCanvasTest, ResizeCanvas_Smaller)
{
    // Given
    NMCanvas canvas(10, 10);

    // When
    canvas.Resize(5, 5);

    // Then
    ASSERT_EQ(canvas.GetWidth(), 5);
    ASSERT_EQ(canvas.GetHeight(), 5);

    for (int y = 0; y < canvas.GetHeight(); ++y)
    {
        for (int x = 0; x < canvas.GetWidth(); ++x)
        {
            ASSERT_EQ(canvas.ReadPixel(x, y), NMColor(0.0f, 0.0f, 0.0f));
        }
    }
}

// Scenario: Can resize a canvas when already at that size
TEST_F(NMCanvasTest, ResizeCanvas_SameSize)
{
    // Given
    NMCanvas canvas(10, 10);

    // When
    canvas.Resize(10, 10);

    // Then
    ASSERT_EQ(canvas.GetWidth(), 10);
    ASSERT_EQ(canvas.GetHeight(), 10);

    for (int y = 0; y < canvas.GetHeight(); ++y)
    {
        for (int x = 0; x < canvas.GetWidth(); ++x)
        {
            ASSERT_EQ(canvas.ReadPixel(x, y), NMColor(0.0f, 0.0f, 0.0f));
        }
    }
}

// Scenario: Read pixel fails from canvas when out of bounds on x
TEST_F(NMCanvasTest, ReadPixel_OutOfBoundsX)
{
    // Given
    NMCanvas canvas;

    // When
    NMColor color = canvas.ReadPixel(50, 1);

    // Then
    ASSERT_EQ(color, NMColor(0.0f, 0.0f, 0.0f));
}

// Scenario: Read pixel fails from canvas when out of bounds on y
TEST_F(NMCanvasTest, ReadPixel_OutOfBoundsY)
{
    // Given
    NMCanvas canvas;

    // When
    NMColor color = canvas.ReadPixel(1, 50);

    // Then
    ASSERT_EQ(color, NMColor(0.0f, 0.0f, 0.0f));
}

TEST_F(NMCanvasTest, CreateCanvas_WithWidthAndHeight)
{
    // Given
    NMCanvas canvas(20, 30);

    // Then
    ASSERT_EQ(canvas.GetWidth(), 20);
    ASSERT_EQ(canvas.GetHeight(), 30);

    for (int y = 0; y < canvas.GetHeight(); ++y)
    {
        for (int x = 0; x < canvas.GetWidth(); ++x)
        {
            ASSERT_EQ(canvas.ReadPixel(x, y), NMColor(0.0f, 0.0f, 0.0f));
        }
    }
}

TEST_F(NMCanvasTest, CreateCanvas_WithWidthAndHeightAndColor)
{
    // Given
    NMCanvas canvas(20, 30, NMColor(0.5f, 0.5f, 0.5f));

    // Then
    ASSERT_EQ(canvas.GetWidth(), 20);
    ASSERT_EQ(canvas.GetHeight(), 30);

    for (int y = 0; y < canvas.GetHeight(); ++y)
    {
        for (int x = 0; x < canvas.GetWidth(); ++x)
        {
            ASSERT_EQ(canvas.ReadPixel(x, y), NMColor(0.5f, 0.5f, 0.5f));
        }
    }
}

TEST_F(NMCanvasTest, WritePixel)
{
    // Given
    NMCanvas canvas;

    // When
    canvas.WritePixel(2, 3, NMColor(1.0f, 0.0f, 0.0f));

    // Then
    ASSERT_EQ(canvas.ReadPixel(2, 3), NMColor(1.0f, 0.0f, 0.0f));
}

TEST_F(NMCanvasTest, WritePixel_OutOfBounds)
{
    // Given
    NMCanvas canvas;

    // When
    canvas.WritePixel(50, 1, NMColor(1.0f, 0.0f, 0.0f));
    canvas.WritePixel(1, 50, NMColor(1.0f, 0.0f, 0.0f));

    // Then
    ASSERT_EQ(canvas.ReadPixel(9, 9), NMColor(0.0f, 0.0f, 0.0f));
}

TEST_F(NMCanvasTest, WritePixel_Negative)
{
    // Given
    NMCanvas canvas;

    // When
    canvas.WritePixel(-20, 1, NMColor(1.0f, 0.0f, 0.0f));
    canvas.WritePixel(1, -10, NMColor(1.0f, 0.0f, 0.0f));

    // Then
    ASSERT_EQ(canvas.ReadPixel(0, 0), NMColor(0.0f, 0.0f, 0.0f));
}

TEST_F(NMCanvasTest, ClearCanvas)
{
    // Given
    NMCanvas canvas;

    // When
    canvas.WritePixel(2, 3, NMColor(1.0f, 0.0f, 0.0f));
    canvas.Clear();

    // Then
    ASSERT_EQ(canvas.ReadPixel(3, 2), NMColor(0.0f, 0.0f, 0.0f));
}

TEST_F(NMCanvasTest, ClearCanvas_WithColor)
{
    // Given
    NMCanvas canvas;

    // When
    canvas.WritePixel(2, 3, NMColor(1.0f, 0.0f, 0.0f));
    canvas.Clear(NMColor(0.0f, 1.0f, 0.0f));

    // Then
    ASSERT_EQ(canvas.ReadPixel(3, 2), NMColor(0.0f, 1.0f, 0.0f));
}

TEST_F(NMCanvasTest, ToPPM_Header)
{
    // Given
    NMCanvas canvas(20, 20);

    // When
    auto ppm = canvas.ToPPM();

    // Then
    ASSERT_EQ(ppm.substr(0, 3), "P3\n");
    ASSERT_EQ(ppm.substr(3, 6), "20 20\n");
    ASSERT_EQ(ppm.substr(9, 4), "255\n");
}

TEST_F(NMCanvasTest, ToPPM_Body)
{
    // Given
    NMCanvas canvas(5, 3);
    canvas.WritePixel(0, 0, NMColor(1.5f, 0.0f, 0.0f));
    canvas.WritePixel(2, 1, NMColor(0.0f, 0.5f, 0.0f));
    canvas.WritePixel(4, 2, NMColor(-0.5f, 0.0f, 1.0f));

    // When
    auto ppm = canvas.ToPPM();

    // Then
    std::istringstream ppmStream(ppm);
    std::string ppmLine;
    std::vector<std::string> ppmLines;

    while (std::getline(ppmStream, ppmLine))
    {
        ppmLines.push_back(ppmLine);
    }

    ASSERT_EQ(ppmLines[3], "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    ASSERT_EQ(ppmLines[4], "0 0 0 0 0 0 0 127 0 0 0 0 0 0 0");
    ASSERT_EQ(ppmLines[5], "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}

TEST_F(NMCanvasTest, ToPPM_Body_LineLength)
{
    // Given
    NMCanvas canvas(20, 2);
    canvas.Clear(NMColor(1.0f, 0.8f, 0.6f));
    canvas.WritePixel(0, 0, NMColor(1.0f, 0.2f, 1.0f));
    canvas.WritePixel(8, 0, NMColor(0.25f, 1.0f, 0.3f));
    canvas.WritePixel(0, 1, NMColor(0.0f, 0.0f, 0.0f));
    canvas.WritePixel(1, 1, NMColor(0.3f, 0.8f, 0.8f));

    // When
    auto ppm = canvas.ToPPM();

    // Then
    std::istringstream ppmStream(ppm);
    std::string ppmLine;
    std::vector<std::string> ppmLines;

    while (std::getline(ppmStream, ppmLine))
    {
        ppmLines.push_back(ppmLine);
    }

    // All lines should be at most 70 characters long

    // Pixel Row 1
    ASSERT_EQ(ppmLines[3], "255 51 255 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153");  // 70 characters
    ASSERT_EQ(ppmLines[4], "255 204 153 255 204 153 63 255 76 255 204 153 255 204 153 255 204 153");   // 69 characters
    ASSERT_EQ(ppmLines[5], "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");     // 67 characters
    ASSERT_EQ(ppmLines[6], "153 255 204 153 255 204 153");

    // Pixel Row 2
    ASSERT_EQ(ppmLines[7], "0 0 0 76 204 204 255 204 153 255 204 153 255 204 153 255 204 153 255");  // 68 characters
    ASSERT_EQ(ppmLines[8], "204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153");
    ASSERT_EQ(ppmLines[9], "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
    ASSERT_EQ(ppmLines[10], "153 255 204 153 255 204 153");
}

TEST_F(NMCanvasTest, ToPPM_TerminatedWithNewLine)
{
    // Given
    NMCanvas canvas(5, 3);

    // When
    auto ppm = canvas.ToPPM();

    // Then
    ASSERT_EQ(ppm.substr(ppm.length() - 1, 1), "\n");
}
