/*
NoCrash - QMM Plugin to fix q3msgboom
Copyright 2026
https://github.com/thecybermind/nocrash_qmm/
3-clause BSD license: https://opensource.org/license/bsd-3-clause

Created By:
    Kevin Masterson < k.m.masterson@gmail.com >

*/

#ifndef NOCRASH_QMM_VERSION_H
#define NOCRASH_QMM_VERSION_H

#define STRINGIFY(x) STRINGIFY2(x)
#define STRINGIFY2(x) #x

#define NOCRASH_QMM_VERSION_MAJOR    2
#define NOCRASH_QMM_VERSION_MINOR    7
#define NOCRASH_QMM_VERSION_REV      0

#define NOCRASH_QMM_VERSION          STRINGIFY(NOCRASH_QMM_VERSION_MAJOR) "." STRINGIFY(NOCRASH_QMM_VERSION_MINOR) "." STRINGIFY(NOCRASH_QMM_VERSION_REV)

#if defined(_WIN32)
#define NOCRASH_QMM_OS               "Windows"
#ifdef _WIN64
#define NOCRASH_QMM_ARCH             "x86_64"
#else
#define NOCRASH_QMM_ARCH             "x86"
#endif
#elif defined(__linux__)
#define NOCRASH_QMM_OS               "Linux"
#ifdef __LP64__
#define NOCRASH_QMM_ARCH             "x86_64"
#else
#define NOCRASH_QMM_ARCH             "x86"
#endif
#endif

#define NOCRASH_QMM_VERSION_DWORD    NOCRASH_QMM_VERSION_MAJOR , NOCRASH_QMM_VERSION_MINOR , NOCRASH_QMM_VERSION_REV , 0
#define NOCRASH_QMM_COMPILE          __TIME__ " " __DATE__
#define NOCRASH_QMM_BUILDER          "Kevin Masterson"

#endif // NOCRASH_QMM_VERSION_H
