/* -*- mode: c; indent-width: 4; -*- */
/*
 * libshim -- application shim
 *
 * Copyright (c) 2024 - 2025, Adam Young.
 *
 * https://github.com/adamyg/busybox-w32-shim
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * ==end==
 */

#if defined(_WIN32_WINNT) && (_WIN32_WINNT < 0x0601)
#undef  _WIN32_WINNT                            // ASSOCSTR's
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif
#if defined(__WATCOMC__)
#define _WIN32_IE 0x0800                        // ASSOCSTR's
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

#include <stdlib.h>                             // EXIT_FAILURE
#include <wchar.h>                              // wchar_t

#ifdef __cplusplus
extern "C" {
#endif

void ApplicationShim(const wchar_t *name, const wchar_t *alias);
void ApplicationShimCmd(const wchar_t *name, const wchar_t *alias, const wchar_t *cmdline);

int  ShimCreateChild(PROCESS_INFORMATION *ppi, const wchar_t *name, const wchar_t *path, const wchar_t *cmdline);
void ShimErrorMessage(const wchar_t *name, DWORD wrc);

#ifdef __cplusplus
}
#endif

//end

