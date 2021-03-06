// OGLWin32.cpp : Defines the entry point for the application.
//

#include "OGLWin32.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

#include <Windows.h>
#include <CommCtrl.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <tchar.h>
#include "OGLApplication.h"

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")
#pragma comment( lib, "comctl32.lib" )

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                       _In_opt_ HINSTANCE hPrevInstance,
                       _In_ LPTSTR    lpCmdLine,
                       _In_ int       nCmdShow)
{
    int exitcode = 0;
    //Allocate a console window
    //so that messages can be redirected to stdout
    AllocConsole();
    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE *hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;
    INITCOMMONCONTROLSEX icex;
    // Ensure that the common control DLL is loaded.
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC  = ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES;
    ::InitCommonControlsEx(&icex);
    //Create the application instance
    OGLApplication *myapp = OGLApplication::CreateApplication(hInstance);
    exitcode = myapp->Run();
    myapp->DestroyApplication();
    //Free the console window
    FreeConsole();
    ExitProcess(0);
    return exitcode;
}
