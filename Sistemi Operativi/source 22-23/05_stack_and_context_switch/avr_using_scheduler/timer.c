#include "timer.h"

// main scheduler function
extern void schedule(void);

/**
 * \b avrInitSystemTickTimer
 *
 * Initialise the system tick timer. Uses the AVR's timer1 facility.
 *
 * @return None
 */
void timerStart ( void )
{
    /* Set timer 1 compare match value for configured system tick,
     * with a prescaler of 256. We will get a compare match 1A
     * interrupt on every system tick, in which we must call the
     * OS's system tick handler. */
    OCR5A = (AVR_CPU_HZ / 256 / SYSTEM_TICKS_PER_SEC);

    /* Enable compare match 1A interrupt */
#ifdef TIMSK
    TIMSK = _BV(OCIE5A);
#else
    TIMSK5 = _BV(OCIE5A);
#endif

    /* Set prescaler 256 */
    TCCR5B = _BV(CS52) | _BV(WGM52);
}


// timer interrupt
ISR (TIMER5_COMPA_vect)
{
    schedule();
}
