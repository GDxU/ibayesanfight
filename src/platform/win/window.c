#include <stdio.h>
#include <windows.h>

const char g_szClassName[] = "BayeWindowClass";

LRESULT CALLBACK BayeWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(hwnd, &ps);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void RegisterMainWindow(HINSTANCE hInstance)
{
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = BayeWindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "窗口注册失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
        exit(0);
    }
}

HWND CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
    HWND hwnd;
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "iBaye",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 100, 100,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, "窗口创建失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
        exit(0);
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return hwnd;
}

void bayeStart();

int main(int argc, char *argv[])
{
    MSG msg;
    HINSTANCE hInstance;

    hInstance = GetModuleHandle(0);
    RegisterMainWindow(hInstance);
    CreateMainWindow(hInstance, SW_SHOW);

    bayeStart();

    while (1)
    {
        GetMessage(&msg, NULL, 0, 0);
        DispatchMessage(&msg);
    }
    return 0;
}
