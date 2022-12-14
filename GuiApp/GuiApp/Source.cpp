// MFC Stuff
#define _AFXDLL
#include <afxwin.h>

#include <string>
#include <wil/result.h>
#include <wil/cppwinrt.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.Windows.System.h>
#include <stdlib.h>
#include <time.h>
//
//std::wstring evNameAndValue{  };
//winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring> evs;

//void Cls_OnPaint(HWND hWnd)
//{
//        PAINTSTRUCT ps;
//        HDC hdc;
//        hdc = BeginPaint(hWnd, &ps);
//        THROW_LAST_ERROR_IF(!TextOut(hdc, 5, 5, evNameAndValue.c_str(), evNameAndValue.size()));
//        // End application specific layout section.
//        EndPaint(hWnd, &ps);
//
//        evNameAndValue.clear();
//}
//
//void Cls_OnDestroy(HWND hwnd)
//{
//    PostQuitMessage(0);
//}
//
//void Cls_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
//{
//    winrt::hstring messageToPrint{};
//    int indexToBreakAt = rand() % evs.Size();
//    int currentIndex{};
//
//    // Very bad way of picking an EV at random.  But IMapViews don't have index selecting.
//    for (auto&& ev : evs)
//    {
//        if (currentIndex == indexToBreakAt)
//        {
//            messageToPrint = messageToPrint + ev.Key();
//            messageToPrint = messageToPrint + winrt::to_hstring(": ");
//            messageToPrint = messageToPrint + ev.Value();
//            break;
//        }
//        currentIndex++;
//    }
//
//    evNameAndValue = std::wstring(messageToPrint);
//
//    // Tell windows what part of the window to redraw be invalidating it.
//    RECT region{0, 0, 500, 30};
//    InvalidateRect(hWnd, &region, TRUE);
//}

LRESULT CALLBACK WindowsProc(
    _In_ HWND   hWnd,
    _In_ UINT   message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    //switch (message)
    //{
    //    HANDLE_MSG(hWnd, WM_PAINT, Cls_OnPaint);
    //    HANDLE_MSG(hWnd, WM_DESTROY, Cls_OnDestroy);
    //    HANDLE_MSG(hWnd, WM_COMMAND, Cls_OnCommand);
    //default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    //}
}

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    //auto forProcess{ winrt::Microsoft::Windows::System::EnvironmentManager::GetForProcess() };
    //evs = { forProcess.GetEnvironmentVariables() };
    //srand(time(NULL));


    //std::wstring windowsClassName{ L"MyWindowsClass" };
    //WNDCLASSEXW mainWindowClass;
    //mainWindowClass.cbSize = sizeof(WNDCLASSEX);
    //mainWindowClass.style = CS_HREDRAW | CS_VREDRAW;
    //mainWindowClass.lpfnWndProc = WindowsProc;
    //mainWindowClass.cbClsExtra = 0;
    //mainWindowClass.cbWndExtra = 0;
    //mainWindowClass.hInstance = hInstance;
    //mainWindowClass.hIcon = LoadIcon(mainWindowClass.hInstance, IDI_APPLICATION);
    //mainWindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    //mainWindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    //mainWindowClass.lpszMenuName = nullptr;
    //mainWindowClass.lpszClassName = windowsClassName.c_str();
    //mainWindowClass.hIconSm = LoadIcon(mainWindowClass.hInstance, IDI_APPLICATION);

    //ATOM mainWindowsAtom{ RegisterClassExW(&mainWindowClass) };
    //if (!mainWindowsAtom)
    //{
    //    THROW_LAST_ERROR_MSG("Stuff broke");
    //}

    auto className{ AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW) };

    CWnd mainWindow{};
    DWORD exStyle{};
    DWORD style{};
    RECT myRectangle{50, 50, 500, 500};
    THROW_LAST_ERROR_IF(mainWindow.CreateEx(WS_EX_OVERLAPPEDWINDOW, className, L"Title", CS_HREDRAW | CS_VREDRAW, myRectangle, NULL, NULL));

    //std::wstring titleName{ L"TitleName" };
    //HWND windowsHandle{ CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, windowsClassName.c_str(), titleName.c_str(), WS_OVERLAPPEDWINDOW, 800, 500, 800, 500, nullptr, nullptr, hInstance, nullptr) };
    //THROW_LAST_ERROR_IF_NULL(windowsHandle);


    //HWND hwndButton = CreateWindowEx(
    //    WS_EX_OVERLAPPEDWINDOW,
    //    L"BUTTON",  // Predefined class; Unicode assumed 
    //    L"Find me a random EV",      // Button text 
    //    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    //    50,         // x position 
    //    150,         // y position 
    //    500,        // Button width
    //    100,        // Button height
    //    windowsHandle,     // Parent window
    //    NULL,       // No menu.
    //    (HINSTANCE)GetWindowLongPtr(windowsHandle, GWLP_HINSTANCE),
    //    NULL);      // Pointer not needed.

    //THROW_LAST_ERROR_IF_NULL(hwndButton);
    //ShowWindow(windowsHandle, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}