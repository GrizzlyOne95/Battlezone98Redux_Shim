#pragma once
// Live paint control maps: a C++ port of scripts/Build-TerrainAutoPaint.py's
// rasterize() for maps the pack has no baked entry for. Pure: no engine, Ogre
// or D3D. Inputs are the same MAT words and HG2 heights the offline builder
// reads; the output is one RGBA control image (four layers) or two (eight).
// Matches the Python output except the variation and ragged-edge noise, which
// use a hash instead of numpy's PCG64 (see Docs/terrain-live-paint.md).

#include <nlohmann/json.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <functional>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace TerrainLivePaint
{
constexpr int kZoneSamples = 256, kCellSamples = 4, kZoneCells = 64, kMeshSampleBias = 2;
constexpr double kSampleMeters = 5.0, kHeightUnitMeters = 0.1, kCellMeters = kCellSamples * kSampleMeters;

// Row-major field of `channels` doubles per cell.
struct Field
{
    int rows = 0, cols = 0, channels = 1;
    std::vector<double> v;
    Field() = default;
    Field(int r, int c, int ch = 1, double fill = 0) : rows(r), cols(c), channels(ch), v(std::size_t(r) * c * ch, fill) {}
    double& at(int r, int c, int k = 0) { return v[(std::size_t(r) * cols + c) * channels + k]; }
    double at(int r, int c, int k = 0) const { return v[(std::size_t(r) * cols + c) * channels + k]; }
};

struct Input
{
    int zonesX = 0, zonesZ = 0;          // file zones (the HG2/MAT header)
    std::vector<uint16_t> cells;         // [zonesZ*64][zonesX*64] MAT words, row 0 = file row 0
    std::vector<uint16_t> plane;         // [zonesZ*256][zonesX*256] heights in 0.1 m units
    std::array<float, 4> bounds{};       // native min X, min Z, max X, max Z
    uint32_t seed = 0;
};

inline double Smoothstep(double low, double high, double x)
{
    const double t = std::clamp((x - low) / (high - low), 0.0, 1.0);
    return t * t * (3 - 2 * t);
}

// Separable Gaussian with edge replication, every channel; blur() in the builder.
inline Field Blur(Field field, double sigma)
{
    if (sigma <= 0) return field;
    const int radius = (std::max)(1, int(std::ceil(sigma * 3)));
    std::vector<double> taps(std::size_t(2 * radius + 1));
    for (int k = -radius; k <= radius; ++k) taps[std::size_t(k + radius)] = std::exp(-0.5 * (k / sigma) * (k / sigma));
    const double sum = std::accumulate(taps.begin(), taps.end(), 0.0);
    for (auto& tap : taps) tap /= sum;
    for (int axis = 0; axis < 2; ++axis)
    {
        Field out(field.rows, field.cols, field.channels);
        const int length = axis == 0 ? field.rows : field.cols;
        for (int r = 0; r < field.rows; ++r)
        for (int c = 0; c < field.cols; ++c)
        for (int t = 0; t <= 2 * radius; ++t)
        {
            const int i = std::clamp((axis == 0 ? r : c) + t - radius, 0, length - 1);
            const double tap = taps[std::size_t(t)];
            for (int k = 0; k < field.channels; ++k)
                out.at(r, c, k) += tap * (axis == 0 ? field.at(i, c, k) : field.at(r, i, k));
        }
        field = std::move(out);
    }
    return field;
}

// numpy.percentile with linear interpolation.
inline double Percentile(std::vector<double> values, double q)
{
    if (values.empty()) return 0;
    std::sort(values.begin(), values.end());
    const double position = q / 100 * double(values.size() - 1);
    const auto low = std::size_t(std::floor(position));
    const auto high = (std::min)(low + 1, values.size() - 1);
    return values[low] + (values[high] - values[low]) * (position - double(low));
}

// numpy.gradient over a 2D grid: central inside, one-sided at the edges.
inline std::pair<Field, Field> Gradient(const Field& f, double spacing)
{
    Field gz(f.rows, f.cols), gx(f.rows, f.cols);
    for (int r = 0; r < f.rows; ++r)
    for (int c = 0; c < f.cols; ++c)
    {
        if (f.rows > 1)
            gz.at(r, c) = r == 0 ? (f.at(1, c) - f.at(0, c)) / spacing :
                r == f.rows - 1 ? (f.at(r, c) - f.at(r - 1, c)) / spacing : (f.at(r + 1, c) - f.at(r - 1, c)) / (2 * spacing);
        if (f.cols > 1)
            gx.at(r, c) = c == 0 ? (f.at(r, 1) - f.at(r, 0)) / spacing :
                c == f.cols - 1 ? (f.at(r, c) - f.at(r, c - 1)) / spacing : (f.at(r, c + 1) - f.at(r, c - 1)) / (2 * spacing);
    }
    return {gz, gx};
}

inline double Degrees(double gz, double gx) { return std::atan(std::hypot(gx, gz)) * 180.0 / 3.14159265358979323846; }

inline std::vector<double> Floats(const nlohmann::json& value) { return value.get<std::vector<double>>(); }

inline std::vector<double> Unit(std::size_t n, std::size_t index)
{
    std::vector<double> out(n, 0.0); out.at(index) = 1; return out;
}

class Generator
{
public:
    Generator(const nlohmann::json& recipe, const Input& input) : recipe_(recipe), in_(input)
    {
        n_ = recipe.at("layers").size();
        if (n_ != 4 && n_ != 8) throw std::runtime_error("live paint recipe needs four or eight layers");
        rows_ = input.zonesZ * kZoneCells; cols_ = input.zonesX * kZoneCells;
        if (input.zonesX < 1 || input.zonesZ < 1 || input.cells.size() != std::size_t(rows_) * cols_ ||
            input.plane.size() != std::size_t(rows_) * kCellSamples * cols_ * kCellSamples)
            throw std::runtime_error("live paint input does not match its zone counts");
        for (std::size_t i = 0; i < n_; ++i) if (recipe["layers"][i].contains("edge")) edges_.push_back(i);
    }

    // Share of MAT cells whose base or next type the recipe does not map. The
    // offline builder refuses a map above 1% (load_map); so does the live hook.
    double UndefinedShare() const
    {
        std::array<bool, 16> mapped{};
        for (const auto& item : recipe_.at("typeWeights").items()) mapped.at(std::size_t(std::stoi(item.key()))) = true;
        std::size_t undefined = 0;
        for (const uint16_t word : in_.cells) undefined += !(mapped[word >> 12 & 15] && mapped[word >> 8 & 15]);
        return double(undefined) / double(in_.cells.size());
    }

    // The builder's noise seed (load_map): fingerprint prefix xor the first variation rule's seed.
    static uint32_t Seed(const nlohmann::json& recipe, const std::string& fingerprint)
    {
        const auto rules = recipe.contains("variation") ? Rules(recipe["variation"]) : nlohmann::json::array();
        return uint32_t(std::stoul(fingerprint.substr(0, 8), nullptr, 16)) ^
            (rules.empty() ? 0u : rules[0].value("seed", 0u));
    }

    // RGBA images of size x size, row 0 at minimum Z: one for four layers, two for eight.
    std::vector<std::vector<uint8_t>> Rasterize(int size) const
    {
        const Field weights = CellField();
        const int n = int(n_);
        Field field(size, size, n);
        std::vector<int> cx(static_cast<std::size_t>(size)), cz(static_cast<std::size_t>(size));
        std::vector<bool> outX(static_cast<std::size_t>(size)), outZ(static_cast<std::size_t>(size));
        const auto& b = in_.bounds;
        for (int i = 0; i < size; ++i)
        {
            const double px = (i + 0.5) / size;
            const double wx = b[0] + px * (double(b[2]) - b[0]), wz = b[1] + px * (double(b[3]) - b[1]);
            const double sx = wx / kSampleMeters + kZoneSamples / 2 * in_.zonesX - kMeshSampleBias;
            const double sz = kZoneSamples / 2 * in_.zonesZ - wz / kSampleMeters - kMeshSampleBias;
            const int rx = int(std::floor(sx / kCellSamples)), rz = int(std::floor(sz / kCellSamples));
            cx[std::size_t(i)] = std::clamp(rx, 0, cols_ - 1); cz[std::size_t(i)] = std::clamp(rz, 0, rows_ - 1);
            outX[std::size_t(i)] = rx < 0 || rx >= cols_; outZ[std::size_t(i)] = rz < 0 || rz >= rows_;
        }
        const auto outside = recipe_.contains("outsideWeights") ? Weights(recipe_["outsideWeights"]) : Unit(n_, 1);
        for (int r = 0; r < size; ++r)
        for (int c = 0; c < size; ++c)
        for (int k = 0; k < n; ++k)
            field.at(r, c, k) = outZ[std::size_t(r)] || outX[std::size_t(c)] ? outside.at(std::size_t(k)) :
                weights.at(cz[std::size_t(r)], cx[std::size_t(c)], k);
        const double mpp = (double(b[2]) - b[0]) / size;
        std::vector<Field> sharp;
        for (const auto i : edges_)
        {
            const auto& edge = recipe_["layers"][i]["edge"];
            Field reach(size, size);
            for (int r = 0; r < size; ++r) for (int c = 0; c < size; ++c) reach.at(r, c) = field.at(r, c, int(i));
            reach = Blur(reach, edge.at("meters").get<double>() / mpp);
            if (edge.value("ragged", 0.0) > 0)
            {
                const Field noise = RaggedNoise(size, mpp, edge.value("raggedMeters", 12.0), in_.seed + 1 + uint32_t(i));
                for (std::size_t p = 0; p < reach.v.size(); ++p) reach.v[p] += edge["ragged"].get<double>() * noise.v[p];
            }
            for (auto& value : reach.v) value = Smoothstep(0.45, 0.55, value);
            sharp.push_back(std::move(reach));
            for (int r = 0; r < size; ++r) for (int c = 0; c < size; ++c) field.at(r, c, int(i)) = 0;
        }
        field = Blur(std::move(field), recipe_.value("blurMeters", 12.0) / mpp);
        std::vector<int> packed(std::size_t(size) * size * n);
        for (int r = 0; r < size; ++r)
        for (int c = 0; c < size; ++c)
        {
            double total = 0;
            for (int k = 0; k < n; ++k) { auto& value = field.at(r, c, k); value = (std::max)(value, 0.0); total += value; }
            for (int k = 0; k < n; ++k)
            {
                auto& value = field.at(r, c, k);
                value = total > 1e-9 ? value / (std::max)(total, 1e-9) : (k == 0 ? 1.0 : 0.0);
            }
            if (!edges_.empty())
            {
                double sum = 0;
                for (const auto& s : sharp) sum += s.at(r, c);
                const double scale = (std::max)(sum, 1.0);
                double edgeTotal = 0;
                for (const auto& s : sharp) edgeTotal += s.at(r, c) / scale;
                for (int k = 0; k < n; ++k) field.at(r, c, k) *= 1 - edgeTotal;
                for (std::size_t e = 0; e < edges_.size(); ++e) field.at(r, c, int(edges_[e])) = sharp[e].at(r, c) / scale;
            }
            for (int k = 0; k < n; ++k)
                packed[(std::size_t(r) * size + c) * n + k] = std::clamp(int(std::nearbyint(field.at(r, c, k) * 255)), 0, 255);
        }
        return Split(Normalize(packed, n), n, std::size_t(size) * size);
    }

    // The builder's control step: bilinear upscale of each channel, then normalise jointly.
    static std::vector<std::vector<uint8_t>> Upscale(const std::vector<std::vector<uint8_t>>& images, int from, int to)
    {
        if (from == to) return images;
        const int n = int(images.size()) * 4;
        std::vector<int> packed(std::size_t(to) * to * n);
        const double scale = double(from) / to;
        for (int r = 0; r < to; ++r)
        for (int c = 0; c < to; ++c)
        {
            const double y = std::clamp((r + 0.5) * scale - 0.5, 0.0, double(from - 1));
            const double x = std::clamp((c + 0.5) * scale - 0.5, 0.0, double(from - 1));
            const int y0 = int(y), x0 = int(x), y1 = (std::min)(y0 + 1, from - 1), x1 = (std::min)(x0 + 1, from - 1);
            const double fy = y - y0, fx = x - x0;
            for (int k = 0; k < n; ++k)
            {
                const auto& image = images[std::size_t(k / 4)];
                const auto px = [&](int yy, int xx) { return double(image[(std::size_t(yy) * from + xx) * 4 + k % 4]); };
                const double value = (px(y0, x0) * (1 - fx) + px(y0, x1) * fx) * (1 - fy) + (px(y1, x0) * (1 - fx) + px(y1, x1) * fx) * fy;
                packed[(std::size_t(r) * to + c) * n + k] = std::clamp(int(std::lround(value)), 0, 255);
            }
        }
        return Split(Normalize(packed, n), n, std::size_t(to) * to);
    }

    // normalize_array: each pixel sums to 255, largest remainders, lower layer first among ties.
    static std::vector<uint8_t> Normalize(const std::vector<int>& pixels, int n)
    {
        std::vector<uint8_t> out(pixels.size());
        std::vector<double> values(std::size_t(n), 0.0);
        std::vector<int> result(std::size_t(n), 0), order(std::size_t(n), 0);
        for (std::size_t p = 0; p < pixels.size() / std::size_t(n); ++p)
        {
            const int* in = &pixels[p * std::size_t(n)];
            long long total = 0;
            for (int k = 0; k < n; ++k) total += in[k];
            if (total == 0) { for (int k = 0; k < n; ++k) out[p * n + k] = k == 0 ? 255 : 0; continue; }
            int sum = 0;
            for (int k = 0; k < n; ++k)
            {
                values[std::size_t(k)] = double(in[k]) * 255 / double(total);
                result[std::size_t(k)] = int(std::floor(values[std::size_t(k)])); sum += result[std::size_t(k)];
            }
            std::iota(order.begin(), order.end(), 0);
            std::stable_sort(order.begin(), order.end(), [&](int a, int b) {
                return values[std::size_t(a)] - result[std::size_t(a)] > values[std::size_t(b)] - result[std::size_t(b)]; });
            for (int rank = 0; rank < n; ++rank) if (rank < 255 - sum) ++result[std::size_t(order[std::size_t(rank)])];
            for (int k = 0; k < n; ++k) out[p * n + k] = uint8_t(result[std::size_t(k)]);
        }
        return out;
    }

private:
    const nlohmann::json& recipe_;
    const Input& in_;
    std::size_t n_ = 4;

    // Every weight vector in a recipe is per layer; a short one would be read past its end.
    std::vector<double> Weights(const nlohmann::json& value) const
    {
        auto weights = Floats(value);
        if (weights.size() != n_) throw std::runtime_error("live paint recipe weights need one value per layer");
        return weights;
    }
    int rows_ = 0, cols_ = 0;
    std::vector<std::size_t> edges_;

    static std::vector<std::vector<uint8_t>> Split(const std::vector<uint8_t>& packed, int n, std::size_t pixels)
    {
        std::vector<std::vector<uint8_t>> images(std::size_t(n / 4), std::vector<uint8_t>(pixels * 4));
        for (std::size_t p = 0; p < pixels; ++p)
        for (int k = 0; k < n; ++k) images[std::size_t(k / 4)][p * 4 + k % 4] = packed[p * n + k];
        return images;
    }

    int Base(int r, int c) const { return (in_.cells[std::size_t(r) * cols_ + c] >> 12) & 15; }

    // cell_weights: a table row per base type, blended toward the next type on transition cells.
    Field CellWeights(const std::vector<std::vector<double>>& table) const
    {
        const int width = int(table.front().size());
        Field out(rows_, cols_, width);
        const double cap = recipe_.at("transition").at("cap").get<double>();
        const double diagonal = recipe_.at("transition").at("diagonal").get<double>();
        for (int r = 0; r < rows_; ++r)
        for (int c = 0; c < cols_; ++c)
        {
            const uint16_t word = in_.cells[std::size_t(r) * cols_ + c];
            const int base = (word >> 12) & 15, other = (word >> 8) & 15;
            const double amount = base == other ? 0.0 : ((word >> 7) & 1) ? diagonal : cap;
            for (int k = 0; k < width; ++k)
                out.at(r, c, k) = table[std::size_t(base)][std::size_t(k)] * (1 - amount) + table[std::size_t(other)][std::size_t(k)] * amount;
        }
        return out;
    }

    std::vector<std::vector<double>> TypeTable(const nlohmann::json& types) const
    {
        const auto fallback = recipe_.contains("undefinedTypeWeights") ? Weights(recipe_["undefinedTypeWeights"]) : Unit(n_, 1);
        std::vector<std::vector<double>> table(16, fallback);
        for (const auto& item : types.items()) table.at(std::size_t(std::stoi(item.key()))) = Weights(item.value());
        return table;
    }

    Field CellHeights() const
    {
        Field out(rows_, cols_);
        const int width = cols_ * kCellSamples;
        for (int r = 0; r < rows_; ++r)
        for (int c = 0; c < cols_; ++c)
        {
            double sum = 0;
            for (int y = 0; y < kCellSamples; ++y) for (int x = 0; x < kCellSamples; ++x)
                sum += in_.plane[std::size_t(r * kCellSamples + y) * width + c * kCellSamples + x];
            out.at(r, c) = sum / (kCellSamples * kCellSamples) * kHeightUnitMeters;
        }
        return out;
    }

    Field CellSlopeDegrees() const
    {
        Field heights(rows_ * kCellSamples, cols_ * kCellSamples);
        for (std::size_t i = 0; i < heights.v.size(); ++i) heights.v[i] = in_.plane[i] * kHeightUnitMeters;
        const auto gradient = Gradient(heights, kSampleMeters);
        Field out(rows_, cols_);
        for (int r = 0; r < heights.rows; ++r)
        for (int c = 0; c < heights.cols; ++c)
            out.at(r / kCellSamples, c / kCellSamples) += Degrees(gradient.first.at(r, c), gradient.second.at(r, c)) / (kCellSamples * kCellSamples);
        return out;
    }

    bool InTypes(const nlohmann::json& rule, int r, int c) const
    {
        if (!rule.contains("types")) return true;
        const int base = Base(r, c);
        for (const auto& t : rule["types"]) if (t.get<int>() == base) return true;
        return false;
    }

    // Integer hash noise in [0, 1): stands in for numpy default_rng(seed).random.
    static double HashNoise(uint32_t seed, uint32_t index)
    {
        uint32_t h = seed * 0x9E3779B1u ^ (index + 0x7F4A7C15u);
        h ^= h >> 16; h *= 0x85EBCA6Bu; h ^= h >> 13; h *= 0xC2B2AE35u; h ^= h >> 16;
        return double(h >> 8) / double(1u << 24);
    }

    Field VariationNoise(double meters, uint32_t seed) const
    {
        Field noise(rows_, cols_);
        for (std::size_t i = 0; i < noise.v.size(); ++i) noise.v[i] = HashNoise(seed, uint32_t(i));
        noise = Blur(std::move(noise), meters / kCellMeters / 2);
        const double low = Percentile(noise.v, 5), high = Percentile(noise.v, 95);
        for (auto& value : noise.v) value = Smoothstep(0.3, 0.7, (value - low) / (std::max)(high - low, 1e-9));
        return noise;
    }

    // ragged_noise: two octaves about -1..1; bilinear instead of PIL bicubic.
    static Field RaggedNoise(int size, double mpp, double meters, uint32_t seed)
    {
        Field out(size, size);
        uint32_t index = 0;
        for (const auto& octave : {std::pair<double, double>{1.0, 0.65}, {0.5, 0.35}})
        {
            const int cells = (std::max)(2, int(std::ceil(size * mpp / (meters * octave.first))) + 1);
            std::vector<double> grid(std::size_t(cells) * cells);
            for (auto& g : grid) g = HashNoise(seed, index++) * 2 - 1;
            const double scale = double(cells) / size;
            for (int r = 0; r < size; ++r)
            for (int c = 0; c < size; ++c)
            {
                const double y = std::clamp((r + 0.5) * scale - 0.5, 0.0, double(cells - 1));
                const double x = std::clamp((c + 0.5) * scale - 0.5, 0.0, double(cells - 1));
                const int y0 = int(y), x0 = int(x), y1 = (std::min)(y0 + 1, cells - 1), x1 = (std::min)(x0 + 1, cells - 1);
                const double fy = y - y0, fx = x - x0;
                const auto g = [&](int yy, int xx) { return grid[std::size_t(yy) * cells + xx]; };
                out.at(r, c) += octave.second * ((g(y0, x0) * (1 - fx) + g(y0, x1) * fx) * (1 - fy) + (g(y1, x0) * (1 - fx) + g(y1, x1) * fx) * fy);
            }
        }
        return out;
    }

    static Field FillDepressions(const Field& heights, double rise = 1e-3)
    {
        const int rows = heights.rows, cols = heights.cols;
        Field filled = heights;
        std::vector<bool> done(heights.v.size(), false);
        using Item = std::pair<double, int>;
        std::priority_queue<Item, std::vector<Item>, std::greater<Item>> queue;
        for (int i = 0; i < rows * cols; ++i)
        {
            const int r = i / cols, c = i % cols;
            if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) { queue.emplace(heights.v[std::size_t(i)], i); done[std::size_t(i)] = true; }
        }
        while (!queue.empty())
        {
            const auto [z, i] = queue.top(); queue.pop();
            const int r = i / cols, c = i % cols;
            for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <= 1; ++dc)
            {
                const int rr = r + dr, cc = c + dc, j = rr * cols + cc;
                if ((dr || dc) && rr >= 0 && rr < rows && cc >= 0 && cc < cols && !done[std::size_t(j)])
                {
                    done[std::size_t(j)] = true;
                    filled.v[std::size_t(j)] = (std::max)(heights.v[std::size_t(j)], z + rise);
                    queue.emplace(filled.v[std::size_t(j)], j);
                }
            }
        }
        return filled;
    }

    struct Erosion { Field area, deposit, scour, fill; };

    static Erosion ErosionFields(const Field& heights)
    {
        const int rows = heights.rows, cols = heights.cols, n = rows * cols;
        const Field smooth = Blur(heights, 0.75);
        const Field filled = FillDepressions(smooth);
        const auto& h = filled.v;
        Erosion out{Field(rows, cols, 1, 1.0), Field(rows, cols), Field(rows, cols), Field(rows, cols)};
        std::vector<double> carried(std::size_t(n), 0.0);
        std::vector<int> order(static_cast<std::size_t>(n));
        std::iota(order.begin(), order.end(), 0);
        std::stable_sort(order.begin(), order.end(), [&](int a, int b) { return h[std::size_t(a)] > h[std::size_t(b)]; });
        std::vector<std::pair<int, double>> lower;
        for (const int i : order)
        {
            const int r = i / cols, c = i % cols;
            lower.clear();
            double total = 0, steepest = 0;
            for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <= 1; ++dc)
            {
                const int rr = r + dr, cc = c + dc;
                if (!(dr || dc) || rr < 0 || rr >= rows || cc < 0 || cc >= cols) continue;
                const double drop = (h[std::size_t(i)] - h[std::size_t(rr * cols + cc)]) / (std::hypot(dr, dc) * kCellMeters);
                if (drop > 0)
                {
                    const double w = drop * drop * drop * drop;
                    lower.emplace_back(rr * cols + cc, w); total += w; steepest = (std::max)(steepest, drop);
                }
            }
            if (lower.empty()) continue;
            auto& carry = carried[std::size_t(i)];
            const double capacity = std::sqrt(out.area.v[std::size_t(i)]) * steepest;
            if (carry > capacity) { const double dropped = 0.5 * (carry - capacity); out.deposit.v[std::size_t(i)] += dropped; carry -= dropped; }
            else { const double picked = 0.3 * (capacity - carry); out.scour.v[std::size_t(i)] += picked; carry += picked; }
            for (const auto& [j, w] : lower)
            {
                out.area.v[std::size_t(j)] += out.area.v[std::size_t(i)] * w / total;
                carried[std::size_t(j)] += carry * w / total;
            }
        }
        for (std::size_t i = 0; i < h.size(); ++i) out.fill.v[i] = h[i] - smooth.v[i];
        return out;
    }

    static Field CoverageMask(const Field& raw, double coverage)
    {
        const std::size_t n = raw.v.size();
        std::vector<std::size_t> order(n);
        std::iota(order.begin(), order.end(), std::size_t(0));
        std::stable_sort(order.begin(), order.end(), [&](std::size_t a, std::size_t b) { return raw.v[a] < raw.v[b]; });
        std::vector<double> rank(n);
        for (std::size_t k = 0; k < n; ++k) rank[order[k]] = double(k) / double((std::max)(n - 1, std::size_t(1)));
        const double floor = (std::max)(0.05 * Percentile(raw.v, 99.5), 1e-12);
        Field out(raw.rows, raw.cols);
        for (std::size_t i = 0; i < n; ++i) out.v[i] = raw.v[i] > floor ? Smoothstep(1 - 2 * coverage, 1 - coverage, rank[i]) : 0.0;
        return out;
    }

    std::vector<std::pair<std::string, Field>> ErosionMasks(const nlohmann::json& erosion) const
    {
        const Field heights = CellHeights();
        const Erosion e = ErosionFields(heights);
        std::vector<std::pair<std::string, Field>> masks;
        if (erosion.contains("channel"))
        {
            const auto& rule = erosion["channel"];
            const auto gradient = Gradient(Blur(heights, 1.5), kCellMeters);
            Field mask(rows_, cols_);
            const double start = std::log(rule.at("startHectares").get<double>()), full = std::log(rule.at("fullHectares").get<double>());
            for (std::size_t i = 0; i < mask.v.size(); ++i)
            {
                const double hectares = e.area.v[i] * kCellMeters * kCellMeters / 10000;
                const double sloped = Smoothstep(0.5, 2, Degrees(gradient.first.v[i], gradient.second.v[i]));
                mask.v[i] = Smoothstep(start, full, std::log(hectares)) * (1 - Smoothstep(0.2, 1, e.fill.v[i])) * sloped;
            }
            masks.emplace_back("channel", std::move(mask));
        }
        if (erosion.contains("deposit")) masks.emplace_back("deposit", CoverageMask(e.deposit, erosion["deposit"].at("coverage").get<double>()));
        if (erosion.contains("scour")) masks.emplace_back("scour", CoverageMask(e.scour, erosion["scour"].at("coverage").get<double>()));
        if (erosion.contains("talus"))
        {
            const auto& rule = erosion["talus"];
            Field steep = CellSlopeDegrees();
            for (auto& value : steep.v) value = Smoothstep(28, 40, value);
            const double sigma = rule.value("radiusMeters", 60.0) / kCellMeters;
            const Field around = Blur(heights, sigma), spread = Blur(steep, sigma);
            Field raw(rows_, cols_);
            for (std::size_t i = 0; i < raw.v.size(); ++i)
                raw.v[i] = heights.v[i] - around.v[i] < 0 ? (std::max)(spread.v[i] - steep.v[i], 0.0) : 0.0;
            masks.emplace_back("talus", CoverageMask(raw, rule.at("coverage").get<double>()));
        }
        for (auto& mask : masks) mask.second = Blur(std::move(mask.second), 0.7);
        return masks;
    }

    // Blend each cell toward `target` by t(r, c).
    template <class Amount>
    static void BlendToward(Field& weights, const std::vector<double>& target, Amount t)
    {
        for (int r = 0; r < weights.rows; ++r)
        for (int c = 0; c < weights.cols; ++c)
        {
            const double a = t(r, c);
            if (a == 0) continue;
            for (int k = 0; k < weights.channels; ++k) weights.at(r, c, k) = weights.at(r, c, k) * (1 - a) + target[std::size_t(k)] * a;
        }
    }

    static nlohmann::json Rules(const nlohmann::json& value)
    {
        return value.is_array() ? value : nlohmann::json::array({value});
    }

    // cell_field: MAT types, then variation, shape, erosion, slope, edge-layer restore.
    Field CellField() const
    {
        const auto& types = recipe_.at("typeWeights");
        const Field matWeights = CellWeights(TypeTable(types));
        Field weights = matWeights;
        const nlohmann::json variations = recipe_.contains("variation") ? Rules(recipe_["variation"]) : nlohmann::json::array();
        for (std::size_t k = 0; k < variations.size(); ++k)
        {
            const auto& variation = variations[k];
            const double amount = variation.value("amount", 0.5);
            const Field patches = VariationNoise(variation.value("meters", 150.0), in_.seed ^ uint32_t(k * 0x9E3779B1ull));
            if (k == 0)
            {
                auto alternate = TypeTable(types);
                for (const auto& item : variation.at("types").items())
                {
                    auto& row = alternate.at(std::size_t(std::stoi(item.key())));
                    const auto target = Weights(item.value());
                    for (std::size_t i = 0; i < row.size(); ++i) row[i] = (1 - amount) * row[i] + amount * target[i];
                }
                const Field other = CellWeights(alternate);
                for (std::size_t i = 0; i < weights.v.size(); ++i)
                {
                    const double p = patches.v[i / n_];
                    weights.v[i] = weights.v[i] * (1 - p) + other.v[i] * p;
                }
                continue;
            }
            std::vector<std::vector<double>> identity(16, std::vector<double>(16, 0.0));
            for (int i = 0; i < 16; ++i) identity[std::size_t(i)][std::size_t(i)] = 1;
            const Field share = CellWeights(identity);
            for (const auto& item : variation.at("types").items())
            {
                const int index = std::stoi(item.key());
                BlendToward(weights, Weights(item.value()), [&](int r, int c) { return patches.at(r, c) * amount * share.at(r, c, index); });
            }
        }
        const nlohmann::json shapes = recipe_.contains("shape") ? Rules(recipe_["shape"]) : nlohmann::json::array();
        for (const auto& shape : shapes)
        {
            const Field cells = CellHeights();
            const Field around = Blur(cells, shape.at("radiusMeters").get<double>() / kCellMeters);
            for (const auto& [key, sign] : {std::pair<const char*, double>{"hollow", -1.0}, {"ridge", 1.0}})
            {
                if (!shape.contains(key)) continue;
                const auto target = Weights(shape[key]);
                const auto t = [&](int r, int c) {
                    return InTypes(shape, r, c) ? shape.value("amount", 0.5) *
                        Smoothstep(0, shape.at("rangeMeters").get<double>(), sign * (cells.at(r, c) - around.at(r, c))) : 0.0; };
                if (!shape.contains("from")) { BlendToward(weights, target, t); continue; }
                const auto source = shape["from"].get<std::vector<int>>();
                for (int r = 0; r < rows_; ++r)
                for (int c = 0; c < cols_; ++c)
                {
                    const double a = t(r, c);
                    double moved = 0;
                    for (const int s : source) { const double m = weights.at(r, c, s) * a; weights.at(r, c, s) -= m; moved += m; }
                    for (std::size_t k = 0; k < n_; ++k) weights.at(r, c, int(k)) += target[k] * moved;
                }
            }
        }
        if (recipe_.contains("erosion"))
        {
            const auto& erosion = recipe_["erosion"];
            const auto masks = ErosionMasks(erosion);
            for (const char* key : {"talus", "deposit", "channel", "scour"})
            {
                if (!erosion.contains(key)) continue;
                const auto& rule = erosion[key];
                const Field* mask = nullptr;
                for (const auto& m : masks) if (m.first == key) mask = &m.second;
                BlendToward(weights, Weights(rule.at("weights")), [&](int r, int c) {
                    return InTypes(rule, r, c) ? rule.value("amount", 0.5) * mask->at(r, c) : 0.0; });
            }
        }
        if (recipe_.contains("slope"))
        {
            const auto& slope = recipe_["slope"];
            const Field degrees = CellSlopeDegrees();
            const double start = slope.at("startDegrees").get<double>(), full = slope.at("fullDegrees").get<double>();
            BlendToward(weights, Weights(slope.at("weights")), [&](int r, int c) { return Smoothstep(start, full, degrees.at(r, c)); });
        }
        if (!edges_.empty())
        {
            for (int r = 0; r < rows_; ++r)
            for (int c = 0; c < cols_; ++c)
            {
                std::vector<double> mat(n_), rest(n_), spare(n_);
                double matTotal = 0, total = 0;
                for (std::size_t k = 0; k < n_; ++k) { matTotal += matWeights.at(r, c, int(k)); total += weights.at(r, c, int(k)); }
                for (std::size_t k = 0; k < n_; ++k)
                {
                    mat[k] = matWeights.at(r, c, int(k)) / (std::max)(matTotal, 1e-12);
                    rest[k] = spare[k] = 0;
                }
                double keep = 0, restTotal = 0;
                for (std::size_t k = 0; k < n_; ++k)
                {
                    const bool edge = std::find(edges_.begin(), edges_.end(), k) != edges_.end();
                    if (edge) { keep += mat[k]; continue; }
                    rest[k] = weights.at(r, c, int(k)) / (std::max)(total, 1e-12); spare[k] = mat[k]; restTotal += rest[k];
                }
                if (restTotal <= 1e-9) rest = spare;
                const double sum = (std::max)(std::accumulate(rest.begin(), rest.end(), 0.0), 1e-12);
                for (std::size_t k = 0; k < n_; ++k) weights.at(r, c, int(k)) = rest[k] / sum * (1 - keep);
                for (const auto e : edges_) weights.at(r, c, int(e)) = mat[e];
            }
        }
        return weights;
    }
};

// Control images for `size` x `size` slices: rasterized at the recipe's
// weightSize (default 1024, as the builder) and upscaled like the builder.
inline std::vector<std::vector<uint8_t>> Generate(const nlohmann::json& recipe, const Input& input, int size)
{
    const int weightSize = (std::min)(recipe.value("weightSize", 1024), size);
    return Generator::Upscale(Generator(recipe, input).Rasterize(weightSize), weightSize, size);
}
}
