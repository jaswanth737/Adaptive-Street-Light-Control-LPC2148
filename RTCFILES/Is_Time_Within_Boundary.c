
/*******************************************************************************
 * File Name     : Is_Time_Within_Boundary.c
 * Description   : Checks whether the current RTC time falls within the
 *                 configured streetlight operating time boundaries.
 *
 * Target        : LPC21xx
 * Toolchain     : Keil MDK-ARM
 ******************************************************************************/

#include <LPC21xx.H>

#include "types.h"
#include "Is_Time_Within_Boundary.h"
#include "automatic_street_light_project.h"
#include "rtc.h"
#include "rtc_defines.h"

/*******************************************************************************
 * Function Name : Is_Time_Within_Boundary
 * Description   : Compares the current RTC time with the configured starting
 *                 and ending time boundaries.
 *
 *                 All time values are converted into seconds to simplify
 *                 time comparison.
 *
 *                 Supports both:
 *                 1. Normal time intervals (e.g., 08:00:00 to 18:00:00).
 *                 2. Overnight intervals (e.g., 20:00:00 to 06:00:00).
 *
 * Parameters    : None.
 * Return        : 1 - Current time is within the configured boundaries.
 *                 0 - Current time is outside the configured boundaries.
 *
 * Dependencies  : RTC peripheral and streetlight time configuration variables.
 ******************************************************************************/
u32 Is_Time_Within_Boundary(void)
{
    /* Variables to store current, starting and ending times in seconds. */
    unsigned long CURRENT_TIME;
    unsigned long START_TIME;
    unsigned long END_TIME;

    /***************************************************************************
     * Convert RTC Time into Seconds
     **************************************************************************/

    /* Calculate the current RTC time in seconds from midnight. */
    CURRENT_TIME = (HOUR * 3600UL) +
                   (MIN * 60UL) +
                   SEC;

    /***************************************************************************
     * Convert Configured Starting Time into Seconds
     **************************************************************************/

    /* Calculate the streetlight starting time in seconds from midnight. */
    START_TIME = (LED_START_HOUR * 3600UL) +
                 (LED_START_MIN * 60UL) +
                 LED_START_SEC;

    /***************************************************************************
     * Convert Configured Ending Time into Seconds
     **************************************************************************/

    /* Calculate the streetlight ending time in seconds from midnight. */
    END_TIME = (LED_END_HOUR * 3600UL) +
               (LED_END_MIN * 60UL) +
               LED_END_SEC;

    /***************************************************************************
     * Check the Configured Operating Time Interval
     **************************************************************************/

    /* Check whether the operating interval crosses midnight. */
    if(START_TIME >= END_TIME)
    {
        /*
         * Overnight interval:
         * The current time must be greater than or equal to the start time
         * OR less than or equal to the end time.
         */
        if((CURRENT_TIME >= START_TIME) ||
           (CURRENT_TIME <= END_TIME))
        {
            return 1U;
        }
        else
        {
            return 0U;
        }
    }
    else
    {
        /*
         * Normal interval:
         * The current time must be between the start and end times,
         * including both boundary values.
         */
        if((CURRENT_TIME >= START_TIME) &&
           (CURRENT_TIME <= END_TIME))
        {
            return 1U;
        }
        else
        {
            return 0U;
        }
    }
}
