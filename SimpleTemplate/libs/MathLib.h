#pragma once

// 判断平台
#if defined(_WIN32) || defined(_WIN64)
#ifdef MATHLIB_EXPORTS
#define MATHLIB_API __declspec(dllexport)
#else
#define MATHLIB_API __declspec(dllimport)
#endif
#else
// 非 Windows 平台（Android / Linux / Mac）直接为空
#define MATHLIB_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

MATHLIB_API int addaddadd(int a, int b);

#ifdef __cplusplus
}
#endif
