#include <iostream>
#include <windows.h>
#include <conio.h>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    HANDLE hPipe;
    char buffer;
    DWORD dwWritten;

    hPipe = CreateFile(TEXT("\\\\.\\pipe\\EchoNamedPipe"),
                       GENERIC_READ | GENERIC_WRITE,
                       0, NULL,
                       OPEN_EXISTING,
                       0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        cerr << "Не удалось создать именованный канал. Код ошибки: " << GetLastError() << endl;
        return 1;
    }

    cout << "Сервер подключен! Введите данные..." << endl;

    while (true) {
        
        wchar_t c = _getwch();
        if (c == L'\r') cout << '\n';
        else if (c == L'\b') cout << "\b \b";
        else wcout << c;

        WriteFile(hPipe, &c, sizeof(c), &dwWritten, NULL);
    }

    CloseHandle(hPipe);
    return 0;
}