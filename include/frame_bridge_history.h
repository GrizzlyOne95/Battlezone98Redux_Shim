#pragma once
#include "frame_bridge_protocol.h"
#include <array>
#include <algorithm>
#include <cstring>
#include <iterator>

namespace BZROpenShim::FrameBridge
{
    enum class HistoryReason { First, Pair, Missing, Session, Sequence, Time, Convention, Boundary, ExplicitReset };
    inline const char* HistoryReasonName(HistoryReason reason)
    {
        switch (reason)
        {
        case HistoryReason::Pair: return "captured-pair";
        case HistoryReason::Missing: return "missing-camera-depth";
        case HistoryReason::Session: return "producer-session-changed";
        case HistoryReason::Sequence: return "nonconsecutive-captured-frames";
        case HistoryReason::Time: return "invalid-or-long-time-interval";
        case HistoryReason::Convention: return "camera-or-projection-changed";
        case HistoryReason::Boundary: return "depth-boundary-changed";
        case HistoryReason::ExplicitReset: return "explicit-reset";
        default: return "first-observation";
        }
    }
    struct CapturedCameraPair
    {
        bool comparable = false; // Diagnostic continuity, never a DLSS-ready flag.
        HistoryReason reason = HistoryReason::First;
        CameraSnapshot previous{}, current{};
        std::uint64_t previousFrame = 0, currentFrame = 0;
        double intervalSeconds = 0;
    };
    class CameraHistory
    {
    public:
        CapturedCameraPair Push(const SharedFrame& frame, bool reset = false)
        {
            CapturedCameraPair pair{};
            pair.currentFrame = frame.frameId; pair.current = frame.camera;
            if (!ValidDescriptor(frame, frame.producerPid) || !frame.producerPid || !frame.frameId ||
                !frame.captureQpc || !ValidCameraFrame(frame))
            {
                have_ = false; pair.reason = HistoryReason::Missing; return pair;
            }
            if (have_)
            {
                pair.previous = previous_.camera; pair.previousFrame = previous_.frameId;
                if (reset) pair.reason = HistoryReason::ExplicitReset;
                else if (frame.producerPid != previous_.producerPid || frame.qpcFrequency != previous_.qpcFrequency ||
                    frame.textureHandle != previous_.textureHandle || frame.readyFenceHandle != previous_.readyFenceHandle ||
                    frame.depthTextureHandle != previous_.depthTextureHandle ||
                    frame.adapterLuidLow != previous_.adapterLuidLow || frame.adapterLuidHigh != previous_.adapterLuidHigh)
                    pair.reason = HistoryReason::Session;
                else if (frame.frameId <= previous_.frameId || frame.frameId - previous_.frameId != 1)
                    pair.reason = HistoryReason::Sequence;
                else if (frame.captureQpc <= previous_.captureQpc || frame.camera.observationQpc <= previous_.camera.observationQpc ||
                    static_cast<double>(frame.captureQpc - previous_.captureQpc) / frame.qpcFrequency > 0.25)
                    pair.reason = HistoryReason::Time;
                else if (frame.depthCapturedOrdinal != previous_.depthCapturedOrdinal ||
                    frame.depthMatchingClears != previous_.depthMatchingClears ||
                    frame.depthSourceFormat != previous_.depthSourceFormat || frame.depthSourceSamples != previous_.depthSourceSamples ||
                    frame.depthReduction != previous_.depthReduction || frame.camera.stage != previous_.camera.stage)
                    pair.reason = HistoryReason::Boundary;
                else if (frame.width != previous_.width || frame.height != previous_.height ||
                    frame.camera.cameraIdentity != previous_.camera.cameraIdentity ||
                    std::strcmp(frame.camera.name, previous_.camera.name) != 0 ||
                    frame.camera.matrixSource != previous_.camera.matrixSource ||
                    frame.camera.nearClip != previous_.camera.nearClip || frame.camera.farClip != previous_.camera.farClip ||
                    !std::equal(std::begin(frame.camera.projection), std::end(frame.camera.projection), std::begin(previous_.camera.projection)))
                    pair.reason = HistoryReason::Convention;
                else
                {
                    pair.comparable = true; pair.reason = HistoryReason::Pair;
                    pair.intervalSeconds = static_cast<double>(frame.captureQpc - previous_.captureQpc) / frame.qpcFrequency;
                }
            }
            else if (reset) pair.reason = HistoryReason::ExplicitReset;
            previous_ = frame; have_ = true;
            return pair;
        }
        void Clear() { previous_ = {}; have_ = false; }
    private:
        SharedFrame previous_{};
        bool have_ = false;
    };

    using MatrixD = std::array<double, 16>;
    inline MatrixD Multiply(const MatrixD& a, const MatrixD& b)
    {
        MatrixD result{};
        for (unsigned r = 0; r < 4; ++r)
            for (unsigned c = 0; c < 4; ++c)
                for (unsigned k = 0; k < 4; ++k) result[r * 4 + c] += a[r * 4 + k] * b[k * 4 + c];
        return result;
    }
    inline MatrixD ViewProjection(const CameraSnapshot& camera)
    {
        MatrixD view{}, projection{};
        for (unsigned i = 0; i < 16; ++i) { view[i] = camera.view[i]; projection[i] = camera.projection[i]; }
        return Multiply(projection, view);
    }
    inline bool Inverse(const MatrixD& input, MatrixD& inverse)
    {
        double rows[4][8]{};
        for (unsigned r = 0; r < 4; ++r)
            for (unsigned c = 0; c < 4; ++c) { rows[r][c] = input[r * 4 + c]; rows[r][c + 4] = r == c ? 1 : 0; }
        for (unsigned c = 0; c < 4; ++c)
        {
            unsigned pivot = c;
            for (unsigned r = c + 1; r < 4; ++r) if (std::fabs(rows[r][c]) > std::fabs(rows[pivot][c])) pivot = r;
            if (!std::isfinite(rows[pivot][c]) || std::fabs(rows[pivot][c]) < 1e-12) return false;
            if (pivot != c) for (unsigned j = 0; j < 8; ++j) std::swap(rows[c][j], rows[pivot][j]);
            const double divisor = rows[c][c];
            for (unsigned j = 0; j < 8; ++j) rows[c][j] /= divisor;
            for (unsigned r = 0; r < 4; ++r) if (r != c)
            {
                const double scale = rows[r][c];
                for (unsigned j = 0; j < 8; ++j) rows[r][j] -= scale * rows[c][j];
            }
        }
        for (unsigned r = 0; r < 4; ++r)
            for (unsigned c = 0; c < 4; ++c)
            {
                inverse[r * 4 + c] = rows[r][c + 4];
                if (!std::isfinite(inverse[r * 4 + c])) return false;
            }
        return true;
    }
    struct CameraMotionPixel { float x = 0, y = 0, valid = 0; };
    // Static-scene diagnostic only: no object/skinning motion, disocclusion or
    // previous-depth validation. Absolute shader-camera view is required; the
    // camera-relative world origin must not be applied a second time.
    class CameraReprojection
    {
    public:
        bool Prepare(const CapturedCameraPair& pair)
        {
            ready_ = false;
            if (!pair.comparable || !InspectPerspective(pair.current).recognized ||
                !InspectPerspective(pair.previous).recognized ||
                pair.current.width != pair.previous.width || pair.current.height != pair.previous.height ||
                pair.current.matrixSource != pair.previous.matrixSource || pair.current.cameraIdentity != pair.previous.cameraIdentity ||
                pair.current.matrixSource == static_cast<std::uint32_t>(CameraMatrixSource::ViewportRS)) return false;
            MatrixD inverse{};
            if (!Inverse(ViewProjection(pair.current), inverse)) return false;
            transform_ = Multiply(ViewProjection(pair.previous), inverse);
            width_ = pair.current.width; height_ = pair.current.height;
            clearDepth_ = InspectPerspective(pair.current).reversed ? 0.0f : 1.0f;
            ready_ = true; return true;
        }
        CameraMotionPixel Pixel(unsigned x, unsigned y, float depth) const
        {
            if (!ready_ || x >= width_ || y >= height_ || !std::isfinite(depth) || depth < 0 || depth > 1 || depth == clearDepth_) return {};
            const double clip[] = {2.0 * (x + 0.5) / width_ - 1, 1 - 2.0 * (y + 0.5) / height_, depth, 1};
            double previous[4]{};
            for (unsigned r = 0; r < 4; ++r)
                for (unsigned c = 0; c < 4; ++c) previous[r] += transform_[r * 4 + c] * clip[c];
            if (!std::isfinite(previous[3]) || previous[3] <= 1e-12) return {};
            const double px = previous[0] / previous[3], py = previous[1] / previous[3], pz = previous[2] / previous[3];
            if (!std::isfinite(px) || !std::isfinite(py) || !std::isfinite(pz) ||
                px < -1 || px > 1 || py < -1 || py > 1 || pz < 0 || pz > 1) return {};
            return {static_cast<float>((px + 1) * 0.5 * width_ - (x + 0.5)),
                static_cast<float>((1 - py) * 0.5 * height_ - (y + 0.5)), 1};
        }
    private:
        MatrixD transform_{};
        unsigned width_ = 0, height_ = 0;
        float clearDepth_ = 1;
        bool ready_ = false;
    };
}
