#ifndef APP_DEBUG_H
#define APP_DEBUG_H

#include "display.h"

#ifndef DEBUG_LEVEL
//#define DEBUG_LEVEL (0x01|DEBUG_LEVEL_DISPLAY)
#endif

#define DEBUG_LEVEL_MASK       0x00FF
#define DEBUG_LEVEL_SEGERR     0x0100   /*�δ������λ*/
#define DEBUG_LEVEL_DISPLAY    0x0200   /*������ʾ����λ*/
#define DEBUG_LEVEL_MEMWCH     0x0400   /*memwatchʹ��λ*/


#if	((DEBUG_LEVEL & DEBUG_LEVEL_MEMWCH) == DEBUG_LEVEL_MEMWCH)
    #ifndef MEMWATCH
    #define MEMWATCH
    #endif

    #ifndef MW_STDIO
    #define MW_STDIO
    #endif    
    #include "memwatch.h"
#endif

#endif // APP_DEBUG_H
