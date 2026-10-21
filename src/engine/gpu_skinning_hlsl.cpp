// Pure HLSL transform for the experimental GPU skinning path. No Win32, no
// Ogre, no process state: deterministic functions of their inputs.

#include "gpu_skinning_hlsl.h"

#include <cctype>
#include <cstddef>
#include <cstdio>
#include <vector>

namespace BZROpenShim
{
    namespace GpuSkinning
    {
        namespace
        {
            bool IsIdentChar(char c)
            {
                return std::isalnum(static_cast<unsigned char>(c)) != 0 || c == '_';
            }

            // Same length as the input, with every comment character replaced
            // by a space, so searches skip comments and offsets stay valid
            // for edits applied to the original text.
            std::string MaskComments(const std::string& text)
            {
                std::string masked = text;
                size_t i = 0;
                while (i < masked.size())
                {
                    if (masked[i] == '/' && i + 1 < masked.size() && masked[i + 1] == '/')
                    {
                        while (i < masked.size() && masked[i] != '\n')
                            masked[i++] = ' ';
                    }
                    else if (masked[i] == '/' && i + 1 < masked.size() && masked[i + 1] == '*')
                    {
                        while (i < masked.size() &&
                               !(masked[i] == '*' && i + 1 < masked.size() && masked[i + 1] == '/'))
                        {
                            if (masked[i] != '\n')
                                masked[i] = ' ';
                            ++i;
                        }
                        if (i < masked.size())
                        {
                            masked[i++] = ' ';
                            if (i < masked.size())
                                masked[i++] = ' ';
                        }
                    }
                    else
                    {
                        ++i;
                    }
                }
                return masked;
            }

            size_t SkipSpace(const std::string& text, size_t pos)
            {
                while (pos < text.size() && std::isspace(static_cast<unsigned char>(text[pos])))
                    ++pos;
                return pos;
            }

            // Last identifier ending at or before `end` (exclusive), skipping
            // whitespace; empty if the preceding non-space is not an identifier.
            std::string IdentBefore(const std::string& text, size_t end, size_t* start = nullptr)
            {
                size_t pos = end;
                while (pos > 0 && std::isspace(static_cast<unsigned char>(text[pos - 1])))
                    --pos;
                const size_t identEnd = pos;
                while (pos > 0 && IsIdentChar(text[pos - 1]))
                    --pos;
                if (start)
                    *start = pos;
                return text.substr(pos, identEnd - pos);
            }

            bool EqualsNoCase(const std::string& a, const char* b)
            {
                size_t i = 0;
                for (; i < a.size() && b[i] != '\0'; ++i)
                {
                    if (std::toupper(static_cast<unsigned char>(a[i])) !=
                        std::toupper(static_cast<unsigned char>(b[i])))
                    {
                        return false;
                    }
                }
                return i == a.size() && b[i] == '\0';
            }

            // HLSL semantics are case-insensitive and may carry an index;
            // "POSITION" and "POSITION0" name the same input.
            bool SemanticIs(const std::string& semantic, const char* base)
            {
                std::string trimmed = semantic;
                while (!trimmed.empty() &&
                       std::isdigit(static_cast<unsigned char>(trimmed.back())))
                {
                    const bool zero = trimmed.back() == '0';
                    trimmed.pop_back();
                    if (!zero)
                        return false;
                }
                return EqualsNoCase(trimmed, base);
            }

            struct SignatureParam
            {
                std::string type;
                std::string name;
                std::string semantic;
                bool isOutput = false;
                bool conditional = false;
            };

            // Splits the masked parameter list at top-level commas and
            // classifies each `[qualifiers] type name : SEMANTIC` entry.
            // Preprocessor lines are dropped, but a parameter that sits inside
            // an #if block is flagged as conditional.
            std::vector<SignatureParam> ParseSignature(const std::string& sig)
            {
                std::vector<SignatureParam> params;
                std::string current;
                int ifDepth = 0;
                bool currentConditional = false;
                size_t lineStart = 0;
                auto flush = [&]() {
                    // Tokenise the accumulated parameter text.
                    std::vector<std::string> tokens;
                    std::string semantic;
                    const size_t colon = current.find(':');
                    std::string decl = current.substr(0, colon);
                    if (colon != std::string::npos)
                    {
                        semantic = current.substr(colon + 1);
                        size_t b = SkipSpace(semantic, 0);
                        size_t e = b;
                        while (e < semantic.size() && IsIdentChar(semantic[e]))
                            ++e;
                        semantic = semantic.substr(b, e - b);
                    }
                    size_t p = 0;
                    while (p < decl.size())
                    {
                        p = SkipSpace(decl, p);
                        size_t e = p;
                        while (e < decl.size() && !std::isspace(static_cast<unsigned char>(decl[e])))
                            ++e;
                        if (e > p)
                            tokens.push_back(decl.substr(p, e - p));
                        p = e;
                    }
                    if (tokens.size() >= 2)
                    {
                        SignatureParam param;
                        param.name = tokens.back();
                        param.type = tokens[tokens.size() - 2];
                        // Arrays such as `lightPosition[MAX_LIGHTS]` keep their
                        // brackets on the name; strip them.
                        const size_t bracket = param.name.find('[');
                        if (bracket != std::string::npos)
                            param.name = param.name.substr(0, bracket);
                        for (size_t t = 0; t + 2 < tokens.size(); ++t)
                        {
                            if (tokens[t] == "out" || tokens[t] == "inout")
                                param.isOutput = true;
                        }
                        param.semantic = semantic;
                        param.conditional = currentConditional;
                        params.push_back(param);
                    }
                    current.clear();
                    currentConditional = false;
                };

                for (size_t i = 0; i <= sig.size(); ++i)
                {
                    const bool atEnd = i == sig.size();
                    if (!atEnd && i == lineStart)
                    {
                        const size_t first = SkipSpace(sig, i);
                        if (first < sig.size() && sig[first] == '#')
                        {
                            size_t lineEnd = sig.find('\n', first);
                            if (lineEnd == std::string::npos)
                                lineEnd = sig.size();
                            const std::string directive = sig.substr(first + 1, lineEnd - first - 1);
                            size_t d = SkipSpace(directive, 0);
                            size_t de = d;
                            while (de < directive.size() && IsIdentChar(directive[de]))
                                ++de;
                            const std::string word = directive.substr(d, de - d);
                            if (word == "if" || word == "ifdef" || word == "ifndef")
                                ++ifDepth;
                            else if (word == "endif" && ifDepth > 0)
                                --ifDepth;
                            i = lineEnd;
                            lineStart = lineEnd + 1;
                            continue;
                        }
                    }
                    if (atEnd || sig[i] == ',')
                    {
                        flush();
                        continue;
                    }
                    if (sig[i] == '\n')
                        lineStart = i + 1;
                    if (!std::isspace(static_cast<unsigned char>(sig[i])) && ifDepth > 0)
                        currentConditional = true;
                    current.push_back(sig[i]);
                }
                return params;
            }

            const char* kRowSuffix[3] = {"0", "1", "2"};
            const char* kLane[4] = {"x", "y", "z", "w"};
        }

        unsigned long long HashText(const std::string& text)
        {
            unsigned long long hash = 1469598103934665603ULL;
            for (unsigned char c : text)
            {
                hash ^= c;
                hash *= 1099511628211ULL;
            }
            return hash;
        }

        SkinnedSourceResult MakeSkinnedVertexSource(
            const std::string& source,
            const std::string& entryPoint,
            int weightsPerVertex,
            int maxBones)
        {
            SkinnedSourceResult result;
            if (entryPoint.empty())
            {
                result.error = "empty entry point";
                return result;
            }
            if (weightsPerVertex < kMinWeightsPerVertex || weightsPerVertex > kMaxWeightsPerVertex)
            {
                result.error = "unsupported weights per vertex";
                return result;
            }
            if (maxBones < 1 || maxBones > 256)
            {
                result.error = "unsupported bone count";
                return result;
            }

            const std::string masked = MaskComments(source);

            // Exactly one `<entry> (` definition-or-call site. HLSL entry
            // points are never called from the same file, so more than one
            // hit means a conditional duplicate this transform cannot reason
            // about.
            size_t openParen = std::string::npos;
            int hits = 0;
            for (size_t pos = masked.find(entryPoint); pos != std::string::npos;
                 pos = masked.find(entryPoint, pos + 1))
            {
                if (pos > 0 && IsIdentChar(masked[pos - 1]))
                    continue;
                const size_t after = pos + entryPoint.size();
                if (after < masked.size() && IsIdentChar(masked[after]))
                    continue;
                const size_t paren = SkipSpace(masked, after);
                if (paren >= masked.size() || masked[paren] != '(')
                    continue;
                ++hits;
                if (IdentBefore(masked, pos) != "void")
                {
                    result.error = "entry point does not return void";
                    return result;
                }
                openParen = paren;
            }
            if (hits != 1)
            {
                result.error = hits == 0 ? "entry point not found" : "entry point found more than once";
                return result;
            }

            size_t closeParen = std::string::npos;
            int depth = 0;
            for (size_t i = openParen; i < masked.size(); ++i)
            {
                if (masked[i] == '(')
                    ++depth;
                else if (masked[i] == ')' && --depth == 0)
                {
                    closeParen = i;
                    break;
                }
            }
            if (closeParen == std::string::npos)
            {
                result.error = "unbalanced entry signature";
                return result;
            }
            const size_t openBrace = SkipSpace(masked, closeParen + 1);
            if (openBrace >= masked.size() || masked[openBrace] != '{')
            {
                result.error = "entry body not found";
                return result;
            }

            const std::vector<SignatureParam> params =
                ParseSignature(masked.substr(openParen + 1, closeParen - openParen - 1));
            const SignatureParam* position = nullptr;
            const SignatureParam* normal = nullptr;
            for (const SignatureParam& param : params)
            {
                if (param.semantic.empty())
                    continue;
                // TANGENT/BINORMAL pass through unskinned: Ogre's software
                // blend leaves them in bind pose as well.
                if (SemanticIs(param.semantic, "BLENDINDICES") ||
                    SemanticIs(param.semantic, "BLENDWEIGHT"))
                {
                    result.error = "entry already declares " + param.semantic;
                    return result;
                }
                if (param.isOutput)
                    continue;
                if (SemanticIs(param.semantic, "POSITION"))
                {
                    if (position)
                    {
                        result.error = "more than one POSITION input";
                        return result;
                    }
                    position = &param;
                }
                else if (SemanticIs(param.semantic, "NORMAL"))
                {
                    if (normal)
                    {
                        result.error = "more than one NORMAL input";
                        return result;
                    }
                    normal = &param;
                }
            }
            if (!position)
            {
                result.error = "no POSITION input";
                return result;
            }
            if (position->conditional || (normal && normal->conditional))
            {
                result.error = "POSITION or NORMAL input is conditional";
                return result;
            }
            if (position->type != "float3" && position->type != "float4")
            {
                result.error = "unsupported POSITION type " + position->type;
                return result;
            }
            if (normal && normal->type != "float3" && normal->type != "float4")
            {
                result.error = "unsupported NORMAL type " + normal->type;
                return result;
            }

            char buffer[160];
            std::string inputs;
            std::snprintf(buffer, sizeof(buffer),
                          "\n\tuniform float4 %s[%d],", kBonePaletteUniform, maxBones * 3);
            inputs += buffer;
            inputs += "\n\tin uint4 osGpuSkinIndices : BLENDINDICES,";
            inputs += "\n\tin float4 osGpuSkinWeights : BLENDWEIGHT,";

            const std::string& pos = position->name;
            std::string body = "\n\t// OpenShim GPU skinning: same blend as Ogre's software path.\n\t{\n";
            body += "\t\tfloat4 osGpuSkinSrc = float4(" + pos + ".xyz, 1.0);\n";
            body += "\t\tfloat3 osGpuSkinPos = float3(0.0, 0.0, 0.0);\n";
            if (normal)
            {
                body += "\t\tfloat3 osGpuSkinSrcN = " + normal->name + ".xyz;\n";
                body += "\t\tfloat3 osGpuSkinNrm = float3(0.0, 0.0, 0.0);\n";
            }
            for (int w = 0; w < weightsPerVertex; ++w)
            {
                body += "\t\t{\n";
                body += std::string("\t\t\tuint osGpuSkinRow = osGpuSkinIndices.") + kLane[w] + " * 3;\n";
                body += std::string("\t\t\tfloat osGpuSkinW = osGpuSkinWeights.") + kLane[w] + ";\n";
                for (int r = 0; r < 3; ++r)
                {
                    body += std::string("\t\t\tfloat4 osGpuSkinR") + kRowSuffix[r] + " = " +
                            kBonePaletteUniform + "[osGpuSkinRow + " + kRowSuffix[r] + "];\n";
                }
                body += "\t\t\tosGpuSkinPos += float3(dot(osGpuSkinR0, osGpuSkinSrc), "
                        "dot(osGpuSkinR1, osGpuSkinSrc), dot(osGpuSkinR2, osGpuSkinSrc)) * osGpuSkinW;\n";
                if (normal)
                {
                    body += "\t\t\tosGpuSkinNrm += float3(dot(osGpuSkinR0.xyz, osGpuSkinSrcN), "
                            "dot(osGpuSkinR1.xyz, osGpuSkinSrcN), dot(osGpuSkinR2.xyz, osGpuSkinSrcN)) * osGpuSkinW;\n";
                }
                body += "\t\t}\n";
            }
            if (position->type == "float4")
                body += "\t\t" + pos + " = float4(osGpuSkinPos, 1.0);\n";
            else
                body += "\t\t" + pos + " = osGpuSkinPos;\n";
            if (normal)
            {
                // Ogre's Vector3::normalise divides only a non-zero length.
                body += "\t\tfloat osGpuSkinLen = sqrt(dot(osGpuSkinNrm, osGpuSkinNrm));\n";
                body += "\t\tif (osGpuSkinLen > 0.0)\n\t\t\tosGpuSkinNrm /= osGpuSkinLen;\n";
                body += "\t\t" + normal->name + ".xyz = osGpuSkinNrm;\n";
            }
            body += "\t}\n";

            result.positionParam = pos;
            result.normalParam = normal ? normal->name : std::string();
            result.source.reserve(source.size() + inputs.size() + body.size());
            result.source.append(source, 0, openParen + 1);
            result.source += inputs;
            result.source.append(source, openParen + 1, openBrace + 1 - (openParen + 1));
            result.source += body;
            result.source.append(source, openBrace + 1, std::string::npos);
            result.ok = true;
            return result;
        }

        SkinnedSourceResult MakeInstancedSkinnedVertexSource(const std::string& skinnedSource, int maxBones)
        {
            SkinnedSourceResult result;
            if (maxBones < 1 || maxBones > 256)
            {
                result.error = "max bones out of range";
                return result;
            }
            std::string upper = skinnedSource;
            for (char& c : upper)
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            if (upper.find(kInstanceBaseSemantic) != std::string::npos)
            {
                result.error = "source already uses TEXCOORD15";
                return result;
            }

            const std::string palette = std::string("uniform float4 ") + kBonePaletteUniform + "[";
            const size_t paletteAt = skinnedSource.find(palette);
            if (paletteAt == std::string::npos || skinnedSource.find(palette, paletteAt + 1) != std::string::npos)
            {
                result.error = "bone palette not found exactly once";
                return result;
            }
            const size_t countAt = paletteAt + palette.size();
            const size_t countEnd = skinnedSource.find(']', countAt);
            if (countEnd == std::string::npos)
            {
                result.error = "bone palette size not closed";
                return result;
            }
            const std::string weightsInput = "in float4 osGpuSkinWeights : BLENDWEIGHT,";
            const size_t weightsAt = skinnedSource.find(weightsInput);
            if (weightsAt == std::string::npos || weightsAt < countEnd)
            {
                result.error = "blend weight input not found";
                return result;
            }

            std::string out = skinnedSource.substr(0, countAt) + std::to_string(maxBones * 3);
            out.append(skinnedSource, countEnd, weightsAt + weightsInput.size() - countEnd);
            out += std::string("\n\tin float ") + kInstanceBaseInput + " : " + kInstanceBaseSemantic + ",";
            std::string rest = skinnedSource.substr(weightsAt + weightsInput.size());

            const std::string rowPrefix = "uint osGpuSkinRow = osGpuSkinIndices.";
            size_t rewrites = 0;
            for (size_t at = rest.find(rowPrefix); at != std::string::npos; at = rest.find(rowPrefix, at + 1))
            {
                const size_t laneAt = at + rowPrefix.size();
                const std::string tail = " * 3;";
                if (laneAt >= rest.size() || rest.compare(laneAt + 1, tail.size(), tail) != 0)
                {
                    result.error = "unexpected palette row expression";
                    return result;
                }
                const std::string replacement = std::string("uint osGpuSkinRow = (osGpuSkinIndices.") +
                    rest[laneAt] + " + (uint)" + kInstanceBaseInput + ") * 3;";
                rest.replace(at, laneAt + 1 + tail.size() - at, replacement);
                at += replacement.size() - 1;
                ++rewrites;
            }
            if (rewrites == 0)
            {
                result.error = "no palette row to offset";
                return result;
            }
            out += rest;
            result.source = std::move(out);
            result.ok = true;
            return result;
        }
    }
}
