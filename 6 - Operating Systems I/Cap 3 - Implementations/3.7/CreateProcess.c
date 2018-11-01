#include <windows.h>

int main()
{
     STARTUPINFO sj;
     PROCESS_INFORMATION pj;
     
     ZeroMemory(&sj, sizeof(sj));
     sj.cb = sizeof(sj);
     ZeroMemory(&pj, sizeof(pj));

     if(!CreateProcess(".\\fibonacciw.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &sj, &pj))
     {
         printf("Falha ao criar o processo (%d)\n", GetLastError());
         getch();
         exit(0);
     }
     // Espera ate que o processo filho termine
     WaitForSingleObject(pj.hProcess, INFINITE);
     printf("\n\nProcesso filho finalizado!");
     // Fecha o processo e as Threads
     CloseHandle(pj.hProcess);
     CloseHandle(pj.hThread);
     getch();
}
