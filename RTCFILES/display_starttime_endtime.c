
/*******************************************************************************
 * File Name     : display_starttime_endtime.c
 * Description   : Displays the configured streetlight starting and ending
 *                 time boundaries on a 16x2 LCD.
 *
 * Target        : LPC21xx
 * Toolchain     : Keil MDK-ARM
 ******************************************************************************/

#include "lpc21xx.h"

#include "lcd.h"
#include "lcd_defines.h"
#include "time_edit.h"
#include "RTC_edit.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "types.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "delay.h"
#include "automatic_street_light_project.h"
#include "display_starttime_endtime.h"

/*******************************************************************************
 * Function Name : display_starttime_endtime
 * Description   : Displays the configured streetlight operating time
 *                 boundaries in HH:MM:SS format.
 *
 *                 First LCD line  : Starting time (S_t)
 *                 Second LCD line : Ending time (E_t)
 *
 * Parameters    : None.
 * Return        : None.
 *
 * Dependencies  : LCD driver, delay driver and streetlight time configuration
 *                 variables.
 ******************************************************************************/
void display_starttime_endtime(void)
{
    /* Initialize the LCD peripheral. */
    InitLCD();

    /***************************************************************************
     * Display Streetlight Starting Time - First LCD Line
     **************************************************************************/

    /* Position the LCD cursor at the beginning of the first line. */
    CmdLCD(GOTO_LINE1_POS0);

    /* Display the starting-time label. */
    StrLCD("S_t:");

    /* Display starting hour in two-digit format. */
    CharLCD((LED_START_HOUR / 10) + '0');
    CharLCD((LED_START_HOUR % 10) + '0');

    /* Display the time separator. */
    CharLCD(':');

    /* Display starting minutes in two-digit format. */
    CharLCD((LED_START_MIN / 10) + '0');
    CharLCD((LED_START_MIN % 10) + '0');

    /* Display the time separator. */
    CharLCD(':');

    /* Display starting seconds in two-digit format. */
    CharLCD((LED_START_SEC / 10) + '0');
    CharLCD((LED_START_SEC % 10) + '0');

    /***************************************************************************
     * Display Streetlight Ending Time - Second LCD Line
     **************************************************************************/

    /* Position the LCD cursor at the beginning of the second line. */
    CmdLCD(GOTO_LINE2_POS0);

    /* Display the ending-time label. */
    StrLCD("E_t:");

    /* Display ending hour in two-digit format. */
    CharLCD((LED_END_HOUR / 10) + '0');
    CharLCD((LED_END_HOUR % 10) + '0');

    /* Display the time separator. */
    CharLCD(':');

    /* Display ending minutes in two-digit format. */
    CharLCD((LED_END_MIN / 10) + '0');
    CharLCD((LED_END_MIN % 10) + '0');

    /* Display the time separator. */
    CharLCD(':');

    /* Display ending seconds in two-digit format. */
    CharLCD((LED_END_SEC / 10) + '0');
    CharLCD((LED_END_SEC % 10) + '0');

    /***************************************************************************
     * LCD Display Cleanup
     **************************************************************************/

    /* Keep the configured time boundaries visible for one second. */
    delay_s(1);

    /* Clear the LCD display before returning to the calling function. */
    CmdLCD(CLEAR_LCD);
}
