#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <locale.h>

void signal_handler(int sig) {
    switch (sig) {
        case SIGABRT:
            printf("Вызван сигнал (1) - SIGABRT\n");
            break;
        case SIGFPE:
            printf("Вызван сигнал (2) - SIGFPE\n");
            break;
        case SIGILL:
            printf("Вызван сигнал (3) - SIGILL\n");
            break;
        case SIGINT:
            printf("Вызван сигнал (4) - SIGINT\n");
            break;
        case SIGSEGV:
            printf("Вызван сигнал (5) - SIGSEGV\n");
            break;
        case SIGTERM:
            printf("Вызван сигнал (6) - SIGTERM\n");
            break;
        default:
            printf("ERROR\n");
            break;
    }
}

int main() {
    setlocale(LC_ALL, "");
    signal(SIGABRT, signal_handler);
    signal(SIGFPE, signal_handler);
    signal(SIGILL, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGTERM, signal_handler);
    
    int n;
    while (1) {
        printf("choose signal: (1) - SIGABRT (2) - SIGFPE (3) - SIGILL (4) - SIGINT (5) - SIGSEGV (6) - SIGTERM\n");
        scanf("%d", &n);
        switch (n) {
            case 1:
            	raise(SIGABRT);
//                abort();
                break;
            case 2:
                {
                int a = 23526, b = 0;
                int c = a / b;
                }
                break;
            case 3:
                raise(SIGILL);
                break;
            case 4:
                raise(SIGINT);
                break;
            case 5:
            	raise(SIGSEGV);
//                {
//                int *ptr = NULL;
//                *ptr = 42;
//                }
                break;
            case 6:
                raise(SIGTERM);
                break;
            default:
                printf("ERROR\n");
                break;
        }
    }
    return 0;
}

//Сигналы в C — это механизм, используемый операционной системой для уведомления программы о каких-либо событиях (например, ошибках или внешних прерываниях). 
//Каждый сигнал имеет уникальный номер и имя. В вашем задании указаны следующие сигналы: 
//SIGABRT: Сигнал, вызываемый при аварийном завершении программы (например, при вызове функции abort()). 
//SIGFPE: Сигнал, связанный с ошибками арифметики (например, деление на ноль). 
//SIGILL: Сигнал, вызываемый при попытке выполнить недопустимую инструкцию процессора. 
//SIGINT: Сигнал прерывания, обычно отправляемый при нажатии Ctrl+C в терминале. 
//SIGSEGV: Сигнал, возникающий при попытке доступа к недопустимой области памяти (сегментация). 
//SIGTERM: Сигнал, используемый для "мягкого" запроса завершения программы.
