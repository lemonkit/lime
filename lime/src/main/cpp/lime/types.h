/**
 *
 * @file     types
 * @brief    Copyright (C) 2016  yayanyang All Rights Reserved
 * @author   yayanyang
 * @date     2016/04/05
 */
#ifndef LIME_TYPES_H
#define LIME_TYPES_H

#include <lemon/config.h>

#if defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */

typedef HDC     LimeNativeDisplayType;
typedef HBITMAP LimeNativePixmapType;
typedef HWND    LimeNativeWindowType;

#elif defined(SUPPORT_X11)

 /* X11 (tentative)  */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef Display *LimeNativeDisplayType;
typedef Pixmap   LimeNativePixmapType;
typedef Window   LimeNativeWindowType;


#elif defined(__ANDROID__) || defined(ANDROID)

#include <android/native_window.h>

struct Lime_native_pixmap_t;

typedef struct ANativeWindow*           LimeNativeWindowType;
typedef struct Lime_native_pixmap_t*     LimeNativePixmapType;
typedef void*                           LimeNativeDisplayType;

#else

#if defined(_WIN64) ||  __WORDSIZE == 64
typedef khronos_int64_t LimeNativeDisplayType;
#else
typedef int LimeNativeDisplayType;
#endif

typedef void *LimeNativeWindowType;
typedef void *LimeNativePixmapType;

#endif

#endif  //LIME_TYPES_H