#pragma once
#include <string>

namespace CpuDetect {

    inline bool supports(const char* feature)
    {
        int cpuInfo[4];
        __cpuid(cpuInfo, 1);

        if (strcmp(feature, "SSE") == 0)
            return (cpuInfo[3] & (1 << 25));

        if (strcmp(feature, "SSE2") == 0)
            return (cpuInfo[3] & (1 << 26));

        if (strcmp(feature, "SSE4") == 0)
            return (cpuInfo[2] & (1 << 19));

        if (strcmp(feature, "AVX") == 0)
            return (cpuInfo[2] & (1 << 28));

        // AVX2 requires leaf 7
        __cpuidex(cpuInfo, 7, 0);
        if (strcmp(feature, "AVX2") == 0)
            return (cpuInfo[1] & (1 << 5));

        return false;
    }

    inline std::string best_simd()
    {
        if (supports("AVX2")) return "avx";
        if (supports("AVX"))  return "avx";
        if (supports("SSE4")) return "sse";
        if (supports("SSE2")) return "sse";
        return "x86";
    }

}
