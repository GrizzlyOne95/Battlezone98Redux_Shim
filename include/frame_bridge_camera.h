#pragma once
#include <cmath>
#include <cstdint>
#include <type_traits>
#include <initializer_list>
#include <cstddef>
#include <limits>
#include <utility>

namespace BZROpenShim::FrameBridge
{
    enum class CameraStatus : std::uint32_t { Unavailable = 0, Observed = 1, Invalid = 2 };
    enum class CameraMatrixSource : std::uint32_t { Unknown = 0, ViewportRS = 1, CameraForShaders = 2, Synthetic = 3 };
    inline const char* CameraMatrixSourceName(std::uint32_t source)
    {
        switch (static_cast<CameraMatrixSource>(source))
        {
        case CameraMatrixSource::ViewportRS: return "viewport-rs";
        case CameraMatrixSource::CameraForShaders: return "camera-for-shaders";
        case CameraMatrixSource::Synthetic: return "synthetic";
        default: return "unknown";
        }
    }
    // Exported Ogre viewport/camera getters at the capture boundary, not proof
    // of the camera used by every earlier draw in this depth texture. The
    // CameraForShaders source retains the absolute camera view; it does not
    // include per-renderable or camera-relative parameter overrides.
    struct CameraSnapshot
    {
        std::uint32_t status;
        std::uint32_t width, height, matrixSource;
        std::uint64_t cameraIdentity; // Diagnostic identity only; never dereference outside producer.
        char name[64];
        float view[16]; // Ogre row-major; column-vector multiplication.
        float projection[16]; // Convention is explicit in matrixSource; never infer it from layout.
        float nearClip, farClip; // farClip=0 means infinite in Ogre.
        std::uint32_t stage; // 0=Present, 1=pre-clear observation.
        std::uint32_t clearOrdinal;
        std::uint64_t observationQpc;
    };
    static_assert(std::is_standard_layout_v<CameraSnapshot>);
    static_assert(sizeof(CameraSnapshot) == 240);
    static_assert(sizeof(float) == 4 && std::numeric_limits<float>::is_iec559);
    static_assert(offsetof(CameraSnapshot, view) == 88);
    static_assert(offsetof(CameraSnapshot, matrixSource) == 12);
    static_assert(offsetof(CameraSnapshot, observationQpc) == 232);

    inline bool ValidCameraSnapshot(const CameraSnapshot& camera)
    {
        if (camera.status != static_cast<std::uint32_t>(CameraStatus::Observed) ||
            camera.matrixSource < static_cast<std::uint32_t>(CameraMatrixSource::ViewportRS) ||
            camera.matrixSource > static_cast<std::uint32_t>(CameraMatrixSource::Synthetic) ||
            !camera.cameraIdentity || !camera.observationQpc || !camera.width || !camera.height ||
            camera.width > 8192 || camera.height > 8192 || camera.name[63] != 0 ||
            camera.stage > 1 || camera.clearOrdinal > 8 ||
            (camera.stage == 0 && camera.clearOrdinal != 0) || (camera.stage == 1 && camera.clearOrdinal == 0) ||
            !std::isfinite(camera.nearClip) || camera.nearClip <= 0 || !std::isfinite(camera.farClip) ||
            (camera.farClip != 0 && camera.farClip <= camera.nearClip)) return false;
        for (unsigned i = 0; i < 16; ++i)
            if (!std::isfinite(camera.view[i]) || !std::isfinite(camera.projection[i]) ||
                std::fabs(camera.view[i]) > 1e10f || std::fabs(camera.projection[i]) > 1e10f) return false;
        for (unsigned i = 0; i < 63 && camera.name[i]; ++i)
            if (camera.name[i] < 32 || camera.name[i] > 126 || camera.name[i] == '"' || camera.name[i] == '\\') return false;
        if (std::fabs(camera.view[12]) > 0.0001f || std::fabs(camera.view[13]) > 0.0001f ||
            std::fabs(camera.view[14]) > 0.0001f || std::fabs(camera.view[15] - 1) > 0.0001f) return false;
        const float* v = camera.view;
        const double determinant = static_cast<double>(v[0]) * (v[5] * v[10] - v[6] * v[9]) -
            static_cast<double>(v[1]) * (v[4] * v[10] - v[6] * v[8]) +
            static_cast<double>(v[2]) * (v[4] * v[9] - v[5] * v[8]);
        if (std::fabs(determinant) <= 1e-6) return false;
        // Projection need not be the recognized centered perspective form,
        // but zero/singular matrices cannot be meaningful observations.
        double matrix[4][4]{};
        for (unsigned row = 0; row < 4; ++row)
            for (unsigned column = 0; column < 4; ++column)
                matrix[row][column] = camera.projection[row * 4 + column];
        for (unsigned column = 0; column < 4; ++column)
        {
            unsigned pivot = column;
            for (unsigned row = column + 1; row < 4; ++row)
                if (std::fabs(matrix[row][column]) > std::fabs(matrix[pivot][column])) pivot = row;
            if (std::fabs(matrix[pivot][column]) <= 1e-12) return false;
            if (pivot != column)
                for (unsigned j = 0; j < 4; ++j) std::swap(matrix[column][j], matrix[pivot][j]);
            for (unsigned row = column + 1; row < 4; ++row)
            {
                const double scale = matrix[row][column] / matrix[column][column];
                for (unsigned j = column + 1; j < 4; ++j) matrix[row][j] -= scale * matrix[column][j];
                matrix[row][column] = 0;
            }
        }
        return true;
    }

    struct ProjectionFacts
    {
        bool recognized = false;
        bool reversed = false;
        int forwardSign = 0;
        double nearDepth = 0, farDepth = 0, aspect = 0, verticalFovDegrees = 0;
    };
    // Classify only centered perspective matrices. Do not reinterpret an
    // unrecognized, oblique, orthographic or transposed matrix as usable depth.
    inline ProjectionFacts InspectPerspective(const CameraSnapshot& camera)
    {
        ProjectionFacts result{};
        if (!ValidCameraSnapshot(camera)) return result;
        const auto* p = camera.projection;
        const unsigned zeros[] = {1, 2, 3, 4, 6, 7, 8, 9, 12, 13, 15};
        for (unsigned i : zeros) if (std::fabs(p[i]) > 0.0001f) return result;
        if (std::fabs(p[0]) < 1e-6 || std::fabs(p[5]) < 1e-6 || std::fabs(p[14]) < 1e-6) return result;
        const double nearClip = camera.nearClip;
        const double farClip = camera.farClip ? camera.farClip : nearClip * 1e6;
        for (int sign : {-1, 1})
        {
            const double nearW = p[14] * sign * nearClip;
            const double farW = p[14] * sign * farClip;
            if (nearW <= 0 || farW <= 0) continue;
            const double nearDepth = (p[10] * sign * nearClip + p[11]) / nearW;
            const double farDepth = (p[10] * sign * farClip + p[11]) / farW;
            const bool standard = std::fabs(nearDepth) < 0.0001 && std::fabs(farDepth - 1) < 0.0001;
            const bool reversed = std::fabs(nearDepth - 1) < 0.0001 && std::fabs(farDepth) < 0.0001;
            if (!standard && !reversed) continue;
            result.recognized = true;
            result.reversed = reversed;
            result.forwardSign = sign;
            result.nearDepth = nearDepth;
            result.farDepth = farDepth;
            result.aspect = std::fabs(static_cast<double>(p[5]) / p[0]);
            result.verticalFovDegrees = 2 * std::atan(1 / std::fabs(static_cast<double>(p[5]))) * 180 / 3.141592653589793;
            break;
        }
        return result;
    }
}
