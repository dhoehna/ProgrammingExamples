#include <Windows.h>
#include <string>
#include <wil/result.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.Windows.System.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <codecvt>
#include <locale>
#include <memory>

std::wstring evName{ L"Hello, Windows desktop!" };
winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring> evs;
LRESULT CALLBACK WindowsProc(
    _In_ HWND   hWnd,
    _In_ UINT   message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    PAINTSTRUCT ps;
    HDC hdc;
    std::stringstream evMessage{};
    std::string myMessageAsString{ evMessage.str() };
    auto indexToBreakAt = rand() % evs.Size();
    int currentIndex{};
    std::unique_ptr<wchar_t> buffer;
    int requiredCharacters{};
    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, Windows desktop!"
        // in the top left corner.
        TextOut(hdc,
            5, 5,
            evName.c_str(), evName.size());
        // End application specific layout section.

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        for (auto&& ev : evs)
        {
            if (currentIndex == indexToBreakAt)
            {
                evMessage << winrt::to_string(ev.Key());
                evMessage << " ";
                evMessage << winrt::to_string(ev.Value());
                break;
            }
            currentIndex++;
        }

        requiredCharacters = MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, myMessageAsString.c_str(), -1, nullptr, 0);
        buffer.reset(new wchar_t[requiredCharacters + 1]);
        requiredCharacters = MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, myMessageAsString.c_str(), -1, buffer.get(), 0);

        evName = buffer.release();

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}


int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    auto forProcess{winrt::Microsoft::Windows::System::EnvironmentManager::GetForProcess()};
    evs = { forProcess.GetEnvironmentVariables() };
    srand(time(NULL));


    std::wstring windowsClassName{L"MyWindowsClass"};
    WNDCLASSEXW mainWindow;
    mainWindow.cbSize = sizeof(WNDCLASSEX);
    mainWindow.style = CS_HREDRAW | CS_VREDRAW;
    mainWindow.lpfnWndProc = WindowsProc;
    mainWindow.cbClsExtra = 0;
    mainWindow.cbWndExtra = 0;
    mainWindow.hInstance = hInstance;
    mainWindow.hIcon = LoadIcon(mainWindow.hInstance, IDI_APPLICATION);
    mainWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);
    mainWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    mainWindow.lpszMenuName = nullptr;
    mainWindow.lpszClassName = windowsClassName.c_str();
    mainWindow.hIconSm = LoadIcon(mainWindow.hInstance, IDI_APPLICATION);

    ATOM mainWindowsAtom{ RegisterClassExW(&mainWindow) };
    if (!mainWindowsAtom)
    {
        THROW_LAST_ERROR_MSG("Stuff broke");
    }

    std::wstring titleName{ L"TitleName" };
    HWND windowsHandle{ CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, windowsClassName.c_str(), titleName.c_str(), WS_OVERLAPPEDWINDOW, 800, 500, 500, 500, nullptr, nullptr, hInstance, nullptr) };
    THROW_LAST_ERROR_IF_NULL(windowsHandle);


    HWND hwndButton = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"Find me a random EV",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        150,         // x position 
        150,         // y position 
        100,        // Button width
        100,        // Button height
        windowsHandle,     // Parent window
        NULL,       // No menu.
        (HINSTANCE)GetWindowLongPtr(windowsHandle, GWLP_HINSTANCE),
        NULL);      // Pointer not needed.

    THROW_LAST_ERROR_IF_NULL(hwndButton);
    ShowWindow(windowsHandle, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}