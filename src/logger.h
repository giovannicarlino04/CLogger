/* date = July 8th 2025 6:51 pm */

#ifndef LOGGER_H
#define LOGGER_H


typedef enum{
    LOG_TYPE_INFO = 0,
    LOG_TYPE_WARNING,
    LOG_TYPE_ERROR
} LogTypes;

void mini_putc(char c); 
static void mini_puts(const char *s);
static void mini_itoa(int value, char *buf, int base);
void mini_printf(const char *fmt, ...);
int log(const char* message, LogTypes logType);



#endif // LOGGER_H
