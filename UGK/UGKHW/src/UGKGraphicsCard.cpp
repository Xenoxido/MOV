/** 
 *	Header with definitions needed for the management of any generic graphics card
 *
 *	Prefix: UGKCGC_	for class graphic card
 *
 *	@author Ramón Mollá
 *	@author Sergio Laguna
 *	@version 2015-11
 */
#include <UGKGraphicsCard.h>
#ifdef UGKOS_OPENGL
#include <glew.h>

void CDeskTop::SystemMetrics()
{
	hDeskTop	= GetDesktopWindow();
	hDeskTopDC	= GetDC(hDeskTop);

	Width		= GetDeviceCaps(hDeskTopDC, PLANES) * GetDeviceCaps(hDeskTopDC, HORZRES); 
	Height		= GetDeviceCaps(hDeskTopDC, PLANES) * GetDeviceCaps(hDeskTopDC, VERTRES);
	BitsPerPixel = GetDeviceCaps(hDeskTopDC, PLANES) * GetDeviceCaps(hDeskTopDC, BITSPIXEL);
	ReleaseDC(hDeskTop, hDeskTopDC);
}

CGraphicCard::CGraphicCard()
{
	HWAccelerated	= false;

	TypeHW			= CHW_GRAPHIC;
	bitsPerPixel	= UGKCGC_DEFAULT_DEPTH;

	PIXELFORMATDESCRIPTOR pfd =					// pfd Tells Windows How We Want Things To Be
	{	
		sizeof(PIXELFORMATDESCRIPTOR),			// Size Of This Pixel Format Descriptor
			1,									// Version Number
			PFD_DRAW_TO_WINDOW |				// Format Must Support Window
			PFD_SUPPORT_OPENGL |				// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,					// Must Support Double Buffering
			PFD_TYPE_RGBA,						// Request An RGBA Format
			bitsPerPixel,						// Select Our Color Depth
			0, 0, 0, 0, 0, 0,					// Color Bits Ignored
			0,									// No Alpha Buffer
			0,									// Shift Bit Ignored
			0,									// No Accumulation Buffer
			0, 0, 0, 0,							// Accumulation Bits Ignored
			UGKCGC_DEFAULT_DEPTH,				// 24Bit Z-Buffer (Depth Buffer)  
			0,									// No Stencil Buffer
			0,									// No Auxiliary Buffer
			PFD_MAIN_PLANE,						// Main Drawing Layer
			0,									// Reserved
			0, 0, 0								// Layer Masks Ignored
	};

	PFD		= pfd;
	Status	= CHW_HW_ACTIVE;
}

/**
*	\fn void CGraphicCard::DetectHWAcceleration()

*	Detects if the graphics card is accelerated
*/
void CGraphicCard::DetectHWAcceleration()
{

	HWAccelerated = false;

#ifdef UGKOS_WINDOWS
  
   // Very important to set this variable.. Windows seems
   // not to be able to do this itself;)
   PFD.nSize = sizeof(PIXELFORMATDESCRIPTOR);
   
   // Device Context of the Window you want to draw in
   // must be the same as the one you use to draw GL
   // HDC hDC = GetDC(Window.hWnd);
   UGKCGC_DEVICE_CONTEXT_HANDLE hDC = GetDC(HWND_DESKTOP);
 
   // Number of available pixel formats
   int nFormatCount = DescribePixelFormat(hDC, 1, 0, NULL);
 
   // Go through all available pixel formats and check..
   for(int i = 1; i <= nFormatCount; i++)
   {
      // Get description of pixel format
      DescribePixelFormat(hDC, i, PFD.nSize, &PFD);
 
      // Not generic?
      if (!(PFD.dwFlags & PFD_GENERIC_FORMAT))
      {
         // It's HW accelerated!
         HWAccelerated = true;
         // We can stop here, as there is at least one acc. pixel format
         return;
      }
   }
#elif	defined(UGKOS_LINUX)
#elif	defined(UGKOS_OSX)
#elif	defined(UGKOS_ANDROID)
#endif
}

/**
*	\fn bool CGraphicCard::ChangeScreenResolution(int Width, int Height, int bitsPerPixel)

*	Changes the screen resolution
*	\param[in] Width		New screen horizontal width
*	\param[in] Height		New screen vertical height
*	\param[in] bitsPerPixel New pixel depth. Amount of bits assigned per pixel
*/
bool CGraphicCard::ChangeScreenResolution(int Width, int Height, int bitsPerPixel)
{
#ifdef UGKOS_WINDOWS

	DEVMODE dmScreenSettings;										// Device Mode
	ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));					// Make Sure Memory Is Cleared

	dmScreenSettings.dmSize			= sizeof(DEVMODE);				// Size Of The Devmode Structure
	dmScreenSettings.dmPelsWidth	= Width;						// Select Screen Width
	dmScreenSettings.dmPelsHeight	= Height;						// Select Screen Height
	dmScreenSettings.dmBitsPerPel	= bitsPerPixel;					// Select Bits Per Pixel
	dmScreenSettings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		return FALSE;												// Display Change Failed, Return False

#elif	defined UGKOS_LINUX
#elif	defined UGKOS_OSX
#elif	defined UGKOS_ANDROID
#endif
	return TRUE;													// Display Change Was Successful, Return True
}

UGKS_String CGraphicCard::GetOpenGLVendor()
{
	UGKS_String vendor = (char*)glGetString(GL_VENDOR);
	return vendor;
}

UGKS_String CGraphicCard::GetOpenGLRenderer()
{
	UGKS_String renderer = (char*)glGetString(GL_RENDERER);
	return renderer;
}

UGKS_String CGraphicCard::GetOpenGLVersion()
{
	UGKS_String version = (char*)glGetString(GL_VERSION);
	return version;
}

UGKS_String CGraphicCard::GetOpenGLExtensions()
{
	UGKS_String exts = (char*)glGetString(GL_EXTENSIONS);
	return exts;
}

#elif defined UGKOS_DIRECTX
#endif

#ifdef UGKOS_WINDOWS
void CGraphicCard::GetScreenResolution(int &width, int &height)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	width = desktop.right;
	height = desktop.bottom;
}
#elif defined UGKOS_OSX
#elif defined UGKOS_LINUX
#elif defined UGKOS_ANDROID
#endif