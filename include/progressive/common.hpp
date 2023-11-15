#pragma once

#if defined(_WIN32)
#	define PROG_WINDOWS // Windows
#	define PROG_OS_NAME "windows"
#elif defined(_WIN64)
#	define PROG_WINDOWS // Windows
#	define PROG_OS_NAME "windows"
#elif defined(__linux__)
#	define PROG_LINUX // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#	define PROG_UNIX
#	define PROG_OS_NAME "linux"
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
#	include <sys/param.h>
#	if defined(BSD)
#		define PROG_BSD // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
#		define PROG_UNIX
#		define PROG_OS_NAME "bsd"
#	endif
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
#	define PROG_APPLE
#	define PROG_UNIX
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR == 1
#		define PROG_IOS	 // Apple iOS
#		define PROG_OS_NAME "ios"
#	elif TARGET_OS_IPHONE == 1
#		define PROG_IOS	 // Apple iOS
#		define PROG_OS_NAME "ios"
#	elif TARGET_OS_MAC == 1
#		define PROG_OSX	 // Apple OSX
#		define PROG_OS_NAME "osx"
#	endif
#endif

#if defined(PROG_OSX)
#	include <unistd.h>
#	include <sys/ioctl.h>
#elif defined(PROG_LINUX)
#	include <unistd.h>
#	include <sys/ioctl.h>
#elif defined(PROG_WINDOWS)
#	include <windows.h>
#endif

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/color.h>
