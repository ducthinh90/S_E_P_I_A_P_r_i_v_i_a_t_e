/****************************************************************/
// Author: E.Pataky
// Date: 8/20/13
// Desc: stopwatch
/****************************************************************/
#include "alldefs.h" // all defines
#include "stopWatch.h" // all defines




uint32_t m_nStart;               //DEBUG Stopwatch start cycle counter value
uint32_t m_nStop;                //DEBUG Stopwatch stop cycle counter value

#define DEMCR_TRCENA    0x01000000

/* Core Debug registers */
#define DEMCR           (*((volatile uint32_t *)0xE000EDFC))
#define DWT_CTRL        (*(volatile uint32_t *)0xe0001000)
#define CYCCNTENA       (1<<0)
#define DWT_CYCCNT      ((volatile uint32_t *)0xE0001004)
#define CPU_CYCLES      *DWT_CYCCNT

#define STOPWATCH_START { m_nStart = *((volatile unsigned int *)0xE0001004);}//DWT_CYCCNT;}
#define STOPWATCH_STOP  { m_nStop = *((volatile unsigned int *)0xE0001004);}


static inline void stopwatch_reset(void)
{
    /* Enable DWT */
    DEMCR |= DEMCR_TRCENA;
    *DWT_CYCCNT = 0;
    /* Enable CPU cycle counter */
    DWT_CTRL |= CYCCNTENA;
}

static inline uint32_t stopwatch_getticks()
{
    return CPU_CYCLES;
}

void stopwatch_delay(uint32_t ticks)
{
    STOPWATCH_START;
    stopwatch_reset();
    while(1)
    {
        if (stopwatch_getticks() >= ticks)
            break;
    }
    STOPWATCH_STOP;
}
