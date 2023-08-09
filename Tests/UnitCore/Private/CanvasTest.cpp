#include "CanvasTest.hpp"

#include "Canvas.hpp"

TEST_F(NMCanvasTest, CreateCanvas)
{
    // Given
    NMCanvas canvas;

    // When
    auto& pixelData = canvas.GetPixelData();

    // Then
    ASSERT_EQ(canvas.GetWidth(), 10);
    ASSERT_EQ(canvas.GetHeight(), 10);

    // Ensure each column has 10 rows
    ASSERT_EQ(pixelData.size(), 10);

    for (auto& row : pixelData)
    {
        // Ensure each row has 10 pixels
        ASSERT_EQ(row.size(), 10);

        // Ensure each pixel is black by default
        for (auto& pixel : row)
        {
            ASSERT_EQ(pixel, NMColor(0.0f, 0.0f, 0.0f));
        }
    }
}

TEST_F(NMCanvasTest, CreateCanvas_WithWidthAndHeight)
{
    // Given
    NMCanvas canvas(20, 30);

    // When
    auto& pixelData = canvas.GetPixelData();

    // Then
    ASSERT_EQ(canvas.GetWidth(), 20);
    ASSERT_EQ(canvas.GetHeight(), 30);

    // Ensure each column has 30 rows
    ASSERT_EQ(pixelData.size(), 30);

    for (auto& row : pixelData)
    {
        // Ensure each row has 20 pixels
        ASSERT_EQ(row.size(), 20);

        // Ensure each pixel is black by default
        for (auto& pixel : row)
        {
            ASSERT_EQ(pixel, NMColor(0.0f, 0.0f, 0.0f));
        }
    }
}

TEST_F(NMCanvasTest, CreateCanvas_WithWidthAndHeightAndColor)
{
    // Given
    NMCanvas canvas(20, 30, NMColor(0.5f, 0.5f, 0.5f));

    // When
    auto& pixelData = canvas.GetPixelData();

    // Then
    ASSERT_EQ(canvas.GetWidth(), 20);
    ASSERT_EQ(canvas.GetHeight(), 30);

    // Ensure each column has 30 rows
    ASSERT_EQ(pixelData.size(), 30);

    for (auto& row : pixelData)
    {
        // Ensure each row has 20 pixels
        ASSERT_EQ(row.size(), 20);

        // Ensure each pixel is red by default
        for (auto& pixel : row)
        {
            ASSERT_EQ(pixel, NMColor(0.5f, 0.5f, 0.5f));
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
    ASSERT_EQ(canvas.GetPixelData()[3][2], NMColor(1.0f, 0.0f, 0.0f));
}

TEST_F(NMCanvasTest, WritePixel_OutOfBounds)
{
    // Given
    NMCanvas canvas;

    // When
    canvas.WritePixel(20, 30, NMColor(1.0f, 0.0f, 0.0f));

    // Then
    ASSERT_EQ(canvas.GetPixelData()[9][9], NMColor(0.0f, 0.0f, 0.0f));
}

TEST_F(NMCanvasTest, ClearCanvas)
{
    // Given
    NMCanvas canvas;

    // When
    canvas.WritePixel(2, 3, NMColor(1.0f, 0.0f, 0.0f));
    canvas.Clear();

    // Then
    ASSERT_EQ(canvas.GetPixelData()[3][2], NMColor(0.0f, 0.0f, 0.0f));
}

TEST_F(NMCanvasTest, ClearCanvas_WithColor)
{
    // Given
    NMCanvas canvas;

    // When
    canvas.WritePixel(2, 3, NMColor(1.0f, 0.0f, 0.0f));
    canvas.Clear(NMColor(0.0f, 1.0f, 0.0f));

    // Then
    ASSERT_EQ(canvas.GetPixelData()[3][2], NMColor(0.0f, 1.0f, 0.0f));
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
