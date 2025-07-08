#include "logger.h"

#ifdef _WIN32
#include <windows.h>

void mini_putc(char c) {
    DWORD written;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsoleA(h, &c, 1, &written, NULL);
}

#elif defined(__unix__) || defined(__APPLE__)
#ifdef __cplusplus
extern "C" {
#endif
    
#include <unistd.h>
    
    void mini_putc(char c) {
        // Use syscall-level write to stdout (fd = 1)
        write(1, &c, 1);
    }
    
#ifdef __cplusplus
}
#endif

#else
#error "Platform not supported for mini_putc"
#endif

static void mini_puts(const char *s) {
    while (*s) {
        mini_putc(*s++);
    }
}
static void mini_itoa(int value, char *buf, int base) {
    char tmp[32];
    int i = 0, neg = 0;
    
    if (value == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    
    if (value < 0 && base == 10) {
        neg = 1;
        value = -value;
    }
    
    while (value != 0 && i < (int)(sizeof(tmp) - 1)) {
        int rem = value % base;
        tmp[i++] = (rem > 9) ? (rem - 10 + 'a') : (rem + '0');
        value /= base;
    }
    
    if (neg) {
        tmp[i++] = '-';
    }
    
    int j = 0;
    while (i--) {
        buf[j++] = tmp[i];
    }
    buf[j] = '\0';
}
void mini_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    char buf[32];
    
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's': {
                    const char *s = va_arg(args, const char *);
                    mini_puts(s);
                    break;
                }
                case 'd': {
                    int d = va_arg(args, int);
                    mini_itoa(d, buf, 10);
                    mini_puts(buf);
                    break;
                }
                case 'x': {
                    int x = va_arg(args, int);
                    mini_itoa(x, buf, 16);
                    mini_puts(buf);
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    mini_putc(c);
                    break;
                }
                case '%': {
                    mini_putc('%');
                    break;
                }
                default:
                mini_putc('?');
                break;
            }
        } else {
            mini_putc(*fmt);
        }
        fmt++;
    }
    
    va_end(args);
}
#ifdef _WIN32
#include <windows.h>

void set_console_color(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void reset_console_color() {
    set_console_color(7);
}
#else
void set_console_color(int color) {}
void reset_console_color() {}
#endif

int log(const char* message, LogTypes logType){
    const char* type;
    
#ifdef _WIN32
    WORD color;
#else
    const char* color;
#endif
    
    switch(logType){
        case LOG_TYPE_INFO:
        type = "INFO";
#ifdef _WIN32
        color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
#else
        color = ANSI_COLOR_GREEN;
#endif
        break;
        case LOG_TYPE_WARNING:
        type = "WARNING";
#ifdef _WIN32
        color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
#else
        color = ANSI_COLOR_YELLOW;
#endif
        break;
        case LOG_TYPE_ERROR:
        type = "ERROR";
#ifdef _WIN32
        color = FOREGROUND_RED | FOREGROUND_INTENSITY;
#else
        color = ANSI_COLOR_RED;
#endif
        break;
        default:
        type = "INFO";
#ifdef _WIN32
        color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
#else
        color = ANSI_COLOR_GREEN;
#endif
        break;
    }
    
#ifdef _WIN32
    set_console_color(color);
    mini_printf("[%s]: %s\n", type, message);
    reset_console_color();
#else
    mini_printf("%s[%s]: %s%s\n", color, type, message, ANSI_COLOR_RESET);
#endif
    
    return 0;
}
