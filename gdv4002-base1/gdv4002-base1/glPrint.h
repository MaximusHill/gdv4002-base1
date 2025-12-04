#pragma once

#include <Windows.h>

bool glBuildFont(int pointsize);
bool glBuildFontFromFile(const wchar_t* filePath, const wchar_t* faceName, int pointSize = 12);
void glDeleteFont();
void glPrint(const char *fmt, ...);


