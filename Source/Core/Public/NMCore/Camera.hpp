#pragma once

#include <memory>
#include <random>

#include "Canvas.hpp"
#include "NMM/Matrix.hpp"
#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "RT/Ray.hpp"
#include "ThreadPool.hpp"
#include "World.hpp"

class NMCamera
{
public:

    NMCamera(std::size_t hSize, std::size_t vSize, float fov) : hSize(hSize), vSize(vSize), fov(fov)
    {
        UpdatePixelSize();
    }

    ~NMCamera() {}

    inline std::size_t GetHSize() const { return hSize; }
    inline std::size_t GetVSize() const { return vSize; }

    inline float GetFOV() const { return fov; }

    float GetPixelSize() const { return pixelSize; }

    inline const NMMatrix& GetTransform() const { return transform; }

    inline void SetTransform(const NMMatrix& transform) { this->transform = transform; }

    NMRay RayForPixel(std::size_t px, std::size_t py)
    {
        // The offset from the edge of the canvas to the pixel's center
        float xOffset = (static_cast<float>(px) + 0.5f) * pixelSize;
        float yOffset = (static_cast<float>(py) + 0.5f) * pixelSize;

        // The untransformed coordinates of the pixel in world space.
        // (Remember that the camera looks toward -z, so +x is to the *left*.)
        float worldX = halfWidth - xOffset;
        float worldY = halfHeight - yOffset;

        // Using the camera matrix, transform the canvas point and the origin,
        // and then compute the ray's direction vector.
        // (Remember that the canvas is at z=-1)
        NMMatrix inverseTransform = transform.Inverse();
        NMPoint pixel = inverseTransform * NMPoint(worldX, worldY, -1.0f);
        NMPoint origin = inverseTransform * NMPoint(0.0f, 0.0f, 0.0f);
        NMVector direction = pixel - origin;

        direction.Normalize();

        return NMRay(origin, direction);
    }

    /**
     * @brief Render the world to a canvas.
     * @note This method will block until rendering is complete.
     * @param world The world to render to the canvas.
     * @param threadCount The number of threads to use for rendering (0 = use all available threads).
     * @return The rendered canvas.
     */
    inline NMCanvas Render(const NMWorld& world, std::size_t threadCount = 0)
    {
        NMCanvas image(hSize, vSize);
        Render(world, &image, threadCount);
        return image;
    }

    /**
     * @brief Render the world to a canvas.
     * @note This method will block until rendering is complete.
     * @param world The world to render to the canvas.
     * @param image The canvas to render to.
     * @param threadCount The number of threads to use for rendering (0 = use all available threads).
     *                    A negative value will use all available threads minus the absolute value of the parameter.
     * @return The rendered canvas.
     */
    void Render(const NMWorld& world, NMCanvas* image, std::size_t threadCount = 0)
    {
        if (pool)
        {
            throw std::runtime_error("Camera is already rendering");
        }

        if (threadCount <= 0)
        {
            threadCount = std::thread::hardware_concurrency() + threadCount;
        }

        pool = new ThreadPool(threadCount);

        // Generate a list of indices to render and shuffle them
        std::vector<std::size_t> indices;
        for (std::size_t i = 0; i < hSize * vSize; ++i)
        {
            indices.push_back(i);
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g);

        for (std::size_t i = 0; i < indices.size(); ++i)
        {
            std::size_t index = indices[i];
            std::size_t x = index % hSize;
            std::size_t y = index / hSize;
            pool->Enqueue(
                [this, &world, &image, x, y]
                {
                    NMRay ray = RayForPixel(x, y);
                    NMColor color = world.ColorAt(ray);
                    image->WritePixel(x, y, color);
                });
        }

        // // Sequentially render each pixel
        // for (std::size_t y = 0; y < vSize; ++y)
        // {
        //     for (std::size_t x = 0; x < hSize; ++x)
        //     {
        //         pool->Enqueue(
        //             [this, &world, &image, x, y]
        //             {
        //                 NMRay ray = RayForPixel(x, y);
        //                 NMColor color = world.ColorAt(ray);
        //                 image->WritePixel(x, y, color);
        //             });
        //     }
        // }
        delete pool;
        pool = nullptr;
    }

    /**
     * @brief Stop rendering the world to a canvas.
     * @note This method will return immediately, but the thread running Render() will block until cancel has completed.
     */
    void StopRender()
    {
        if (pool)
        {
            pool->Cancel();
        }
    }

protected:

    std::size_t hSize;
    std::size_t vSize;
    float fov;

    float halfWidth;
    float halfHeight;

    float pixelSize;

    NMMatrix transform = NMMatrix::Identity4x4();

    ThreadPool* pool = nullptr;

    void UpdatePixelSize()
    {
        float halfView = tanf(fov / 2.0f);
        float aspect = static_cast<float>(hSize) / static_cast<float>(vSize);

        if (aspect >= 1.0f)
        {
            halfWidth = halfView;
            halfHeight = halfView / aspect;
        }
        else
        {
            halfWidth = halfView * aspect;
            halfHeight = halfView;
        }

        pixelSize = (halfWidth * 2.0f) / static_cast<float>(hSize);
    }
};
