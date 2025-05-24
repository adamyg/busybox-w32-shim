/*
 * libshim -- application shim
 *
 * Copyright (c) 2024 - 2025, Adam Young    .
 *
 * https://github.com/adamyg/busybox-w32-shims
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

#include "shim.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef _countof
#define _countof(__type) (sizeof(__type)/sizeof(__type[0]))
#endif

BOOL WINAPI CtrlHandler(DWORD ctrlType);

BOOL WINAPI
CtrlHandler(DWORD ctrlType)
{
    switch (ctrlType) {
    case CTRL_C_EVENT:
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        // forward to child
        return TRUE;
    default:
        return FALSE;
    }
}


static BOOL
Diagnostics(void)
{
    const char *mcshim_diagositics = getenv("MCSHIM_DIAGNOSTICS"); // optional runtime diagnostics
    return (mcshim_diagositics && mcshim_diagositics[0] && mcshim_diagositics[0] != '0'); // non-zero
}


static wchar_t *
Basename(wchar_t *path)
{
    wchar_t *base = path;

    for (;*path; ++path) {
        if (*path == '\\' || *path == '/') { // path delimiter
            base = path + 1; // next element
        }
    }
    return base;
}


int
ShimCreateChild(PROCESS_INFORMATION *ppi, const wchar_t *name, const wchar_t *path, const wchar_t *cmdline)
{
    wchar_t *t_cmdline = _wcsdup(cmdline); // command line, cloned.
    STARTUPINFOW si = {0};

    GetStartupInfoW(&si); // process information

    if (NULL == t_cmdline ||
            ! CreateProcessW(path, t_cmdline, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &si, ppi)) {

        ShimErrorMessage(name, GetLastError());
        return FALSE;
    }
    return TRUE;
}


void
ShimErrorMessage(const wchar_t *name, DWORD wrc)
{
    wchar_t *message = NULL;

    if (FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, wrc, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR) &message, 0, NULL) && message) {

        wchar_t *nl, *rt; // trailing newline/return

        nl = wcsrchr(message, '\n'); // trim
        rt = wcsrchr(message, '\r'); // trim

        if (nl) *nl = 0;
        if (rt) *rt = 0;

        wprintf(L"%ls: unable to execute child : %ls (0x%08lx)\n", name, message, wrc);

    } else {
        wprintf(L"%ls: unable to execute child : 0x%08lx.\n", name, wrc);
    }

    LocalFree(message);
}

static wchar_t orgpath[1024] = {0};
static wchar_t newpath[1024] = {0};

/*
 *  ApplicationShim - application execution redirect shim.
 *
 *  Parameters:
 *      name - Application name.
 *      alias - Replacement application name, same path assumed.
 *
 *  Returns:
 *      On success no-return, otherwise returns on error.
 */
void
ApplicationShim(const wchar_t *name, const wchar_t *alias)
{
    ApplicationShimCmd(name, alias, GetCommandLineW());
}


void
ApplicationShimCmd(const wchar_t *name, const wchar_t *alias, const wchar_t *cmdline)
{
    const BOOL diagositics = Diagnostics(); // optional runtime diagnostics
    const unsigned aliassz = wcslen(alias), // alias length, in characters.
        pathsz = GetModuleFileNameW(NULL, orgpath, _countof(orgpath)); // fully qualified path.
    wchar_t *base;

    HANDLE job = INVALID_HANDLE_VALUE;
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION joli = {0};
    PROCESS_INFORMATION pi = {0};
    DWORD excode = 0;

    setvbuf(stdout, NULL, _IONBF, 0); // disable buffering

    // build path
    if (pathsz >= _countof(orgpath)) {
        wprintf(L"%ls: command line too long.\n", name);
        return;
    }

    if (diagositics) {
        wprintf(L"ORG: %ls\n", orgpath);
        wprintf(L"CMD: %ls\n", cmdline);
    }

    wmemcpy(newpath, orgpath, pathsz);
    if (NULL == (base = Basename(newpath)) || !*base) {
        wprintf(L"%ls: command line invalid.\n", name);
        return;

    } else if ((base + aliassz) >= (newpath + _countof(newpath))) {
        wprintf(L"%ls: command line too long.\n", name);
        return;
    }
    wmemcpy(base, alias, aliassz + 1 /*NUL*/);

        //wmemcpy(newpath, L".\\testapp.exe", 13 + 1);
    if (diagositics) {
        wprintf(L"NEW: %ls\n", newpath);
    }

    // execute child
    job = CreateJobObject(NULL, NULL);
    joli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE | JOB_OBJECT_LIMIT_SILENT_BREAKAWAY_OK;
    SetInformationJobObject(job, JobObjectExtendedLimitInformation, &joli, sizeof(joli));

    if (! ShimCreateChild(&pi, name, newpath, cmdline)) {
        return;
    }

    // redirect signals and monitor termination
#if defined(_MSC_VER)
#pragma warning(disable:6387) // handle maybe 0
#endif
    SetConsoleCtrlHandler(CtrlHandler, TRUE);
    AssignProcessToJobObject(job, pi.hProcess);
    ResumeThread(pi.hThread);
    CloseHandle(pi.hThread);

    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &excode);
    CloseHandle(pi.hProcess);
    CloseHandle(job);

    ExitProcess(excode);
    //no-return
}

//end
