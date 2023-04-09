#include <winsock2.h>
#include <windows.h>
#include <psapi.h>
#include <shlwapi.h>
#include <stdio.h>
#include <stdlib.h>

#include "windivert.h"

#define INET6_ADDRSTRLEN    45

int main()
{
    HANDLE handle, process;
    INT16 priority = 1121;          // Arbitrary.
    const char* filter = "processId == 13680", * err_str;
    char path[MAX_PATH + 1];
    char local_str[INET6_ADDRSTRLEN + 1], remote_str[INET6_ADDRSTRLEN + 1];
    char* filename;
    DWORD path_len;
    WINDIVERT_ADDRESS addr;

    handle = WinDivertOpen(filter, WINDIVERT_LAYER_SOCKET, priority, 0 | WINDIVERT_FLAG_RECV_ONLY);
    if (handle == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_INVALID_PARAMETER &&
            !WinDivertHelperCompileFilter(filter, WINDIVERT_LAYER_SOCKET,
                NULL, 0, &err_str, NULL))
        {
            fprintf(stderr, "error: invalid filter \"%s\"\n", err_str);
            exit(EXIT_FAILURE);
        }
        fprintf(stderr, "error: failed to open the WinDivert device (%d)\n",
            GetLastError());
        return EXIT_FAILURE;
    }

    while (TRUE) {
        if (!WinDivertRecv(handle, NULL, 0, NULL, &addr))
        {
            fprintf(stderr, "failed to read packet (%d)\n", GetLastError());
            continue;
        }


        WinDivertSend(handle, nullptr, 0, NULL, &addr)
    }

    return 0;
}