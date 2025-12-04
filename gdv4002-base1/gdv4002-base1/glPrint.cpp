#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdio.h>
#include <string>
#include "glPrint.h"
#include "GraphicsCore.h"


// Reference to OpenGL display list which stores font information
static GLuint		fnt_base = 0;
// Track whether we registered a private font file so we can remove it later
static bool g_fontAdded = false;
static std::wstring g_loadedFontPath;


bool glBuildFont(int pointSize, int width)
{
	HFONT		font = NULL;
	HDC			 hDC = NULL;

	// Get device context
	hDC = GetDC(NULL);
	if (!hDC)
		return false;

	// Generate and validate display list
	fnt_base = glGenLists(256);
	if (!fnt_base) {
		ReleaseDC(NULL, hDC);
		return false;
	}
	int dpi = GetDeviceCaps(hDC, LOGPIXELSY);
	int height = -MulDiv(pointSize > 0 ? pointSize : 12, dpi, 72);
	
	// Create font
	if (!(font = CreateFont(-height,                        // Height Of Font
		width,                            // Width Of Font
		0,                            // Angle Of Escapement
		0,                            // Orientation Angle
		FW_BOLD,                    // Font Weight
		FALSE,                        // Italic
		FALSE,                        // Underline
		FALSE,                        // Strikeout
		ANSI_CHARSET,                // Character Set Identifier
		OUT_TT_PRECIS,                // Output Precision
		CLIP_DEFAULT_PRECIS,        // Clipping Precision
		ANTIALIASED_QUALITY,        // Output Quality
		FF_DONTCARE | DEFAULT_PITCH,    // Family And Pitch
		L"Courier New"))) {            // Font Name
		glDeleteFont();
		ReleaseDC(NULL, hDC);
		return false;
	}
	

	SelectObject(hDC, font); // Select current font
	wglUseFontBitmapsA(hDC, 0, 256, fnt_base); // Builds characters

	// Release device context and dispose local resources
	ReleaseDC(NULL, hDC);
	DeleteObject(font);

	return true;
}

// Load a .ttf or .otf font file (filePath) for this process and build font display lists
bool glBuildFontFromFile(const wchar_t* filePath, const wchar_t* faceName, int pointSize)
{
	if (!filePath || !faceName)
		return false;

	HFONT font = NULL;
	HDC hDC = GetDC(NULL);
	if (!hDC)
		return false;

	// Register the font file privately for this process
	int added = AddFontResourceExW(filePath, FR_PRIVATE, nullptr);
	if (added == 0) {
		ReleaseDC(NULL, hDC);
		return false;
	}

	// Generate display lists
	fnt_base = glGenLists(256);
	if (!fnt_base) {
		RemoveFontResourceExW(filePath, FR_PRIVATE, nullptr);
		ReleaseDC(NULL, hDC);
		return false;
	}

	// Compute height in logical units from point size
	int dpi = GetDeviceCaps(hDC, LOGPIXELSY);
	int height = -MulDiv(pointSize > 0 ? pointSize : 12, dpi, 72);

	// Create the HFONT using the provided face name
	font = CreateFontW(height, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH, faceName);

	if (!font) {
		glDeleteLists(fnt_base, 256);
		fnt_base = 0;
		RemoveFontResourceExW(filePath, FR_PRIVATE, nullptr);
		ReleaseDC(NULL, hDC);
		return false;
	}

	SelectObject(hDC, font);
	wglUseFontBitmapsA(hDC, 0, 256, fnt_base);

	ReleaseDC(NULL, hDC);
	DeleteObject(font);

	// Remember we added this font so glDeleteFont can remove it later
	g_fontAdded = true;
	g_loadedFontPath = filePath;

	return true;
}


void glDeleteFont()
{
	if (fnt_base)
		glDeleteLists(fnt_base, 256);
	fnt_base = 0;

	if (g_fontAdded && !g_loadedFontPath.empty()) {
		RemoveFontResourceExW(g_loadedFontPath.c_str(), FR_PRIVATE, nullptr);
		g_fontAdded = false;
		g_loadedFontPath.clear();
	}
}


// glPrint acts in a similar way to printf
void glPrint(const char *fmt, ...)
{
	char	text[256];
	va_list	ap;

	if (fmt == NULL)
		return;

	// Parse the string for variables
	va_start(ap, fmt);
	vsprintf_s(text, 256, fmt, ap);
	va_end(ap);

	// Render text
	glPushAttrib(GL_LIST_BIT);
	glListBase(fnt_base);
	glCallLists((GLsizei)strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

