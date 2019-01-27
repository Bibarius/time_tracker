#define _WIN32_WINNT 0x0600 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <Psapi.h>
#include <string.h>
#include "request.c"

HWND ForeGroundWindow;      //  HANDLE  окна, на котором в данный момент фокус
DWORD ProcessId;            //  id процесса, которому принадлежит данное окно
HANDLE hOpenProcess;        //  HANDLE этого процесса

DWORD size = MAX_PATH;
DWORD Error;  
LPTSTR path;   
    

//для времени
FILETIME CreationTime;
FILETIME ExitTime;
FILETIME KernelTime;
FILETIME UserTime;

SYSTEMTIME ProcessTime;
SYSTEMTIME CurrentTime;

//для строк
char *Slash;
const char *Path;

Element *array;


int main(int argc, LPTSTR argv[])
{
    array = init_array(5);

    while(TRUE)
    {
        path = malloc(sizeof(WCHAR[MAX_PATH]));      //  выделяем память для строки с названием программы
        DWORD charsCarried = MAX_PATH;               //  переменная, содержащая количество символов в строке с названием

        ForeGroundWindow = GetForegroundWindow();
        if(!(GetWindowThreadProcessId(ForeGroundWindow, &ProcessId)))       //получаем процесс, который запустил окно, на котором сейчас фокус
        {
            printf("error getting the process-ownre of the window\n");
            free(path);
            Sleep(5000);
            continue;
        }        
        if(!(hOpenProcess = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_QUERY_INFORMATION, FALSE, ProcessId)))     //получаем HANDLE этого процесса
        {
            printf("error oppening the process-owner\n");
            free(path);
            Sleep(5000);
            continue;
        } 
        if(!(QueryFullProcessImageNameA(hOpenProcess, 0, path, &charsCarried)))
        {
            printf("error querying process-owner name\n");
            free(path);
            Sleep(5000);
            continue;
        }
        else
        {
            Path = path;
            Slash = strrchr(Path, 92); Slash++;            
            printf("\n\nCurrent working program is: %s\n", Slash);

            request(Slash, array);

            /////сбор данных о времени работы процесса
            // GetProcessTimes(hOpenProcess, &CreationTime, &ExitTime, &KernelTime, &UserTime);
            // FileTimeToSystemTime(&KernelTime, &ProcessTime);


            free(path);
            Sleep(5000);
        }        
    }

    system("PAUSE");
    return 0;
}
