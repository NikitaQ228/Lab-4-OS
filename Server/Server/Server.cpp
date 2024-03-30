#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    HANDLE hPipe;
    wchar_t buffer;
    DWORD dwRead;

    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\EchoNamedPipe"), PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1, 1, 1, NMPWAIT_USE_DEFAULT_WAIT, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        cerr << "Не удалось создать именованный канал. Код ошибки: " << GetLastError() << endl;
        return 1;
    }

    cout << "Ожидание соединения с клиентом..." << endl;

    ConnectNamedPipe(hPipe, NULL);

    cout << "Клиент подключен! Ожидание данных..." << endl;

    while (true) {
        if (!ReadFile(hPipe, &buffer, sizeof(buffer), &dwRead, NULL) || dwRead == 0) {
            cerr << "Потеря связи" << endl;
            break;
        }

        if (buffer == L'\b') cout << "\b \b"; 
        else if (buffer == '\r') cout << endl;
        else wcout << buffer;

        cout.flush();
    }

    CloseHandle(hPipe);

    return 0;
}