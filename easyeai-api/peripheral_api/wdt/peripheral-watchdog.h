#ifndef WDT_H
#define WDT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern int32_t wdt_open(int32_t s);
extern int32_t wdt_feeddog();
extern int32_t wdt_close();




#if defined(__cplusplus)
}
#endif
#endif // WDT_H