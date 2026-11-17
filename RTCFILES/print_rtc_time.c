
/*******************************************************************************
 * File Name     : print_rtc_time.c
 * Description   : Reads the current date and time from the LPC21xx RTC
 *                 peripheral and displays the information on a 16x2 LCD.
 *
 * Target        : LPC21xx
 * Toolchain     : Keil MDK-ARM
 ******************************************************************************/

#include <LPC21XX.h>

#include "lcd.h"
#include "lcd_defines.h"
#include "print_rtc_time.h"
#include "rtc.h"
#include "rtc_defines.h"

/*******************************************************************************
 * Day-of-Week Lookup Table
 *
 * Description : Stores three-character abbreviations for the days of the week.
 * Index       : 0 - Sunday, 1 - Monday, 2 - Tuesday, 3 - Wednesday,
 *               4 - Thursday, 5 - Friday, 6 - Saturday.
 ******************************************************************************/
u8 day[][4] =
{
    "SUN",
    "MON",
    "TUE",
    "WED",
    "THU",
    "FRI",
    "SAT"
};

/*******************************************************************************
 * Function Name : print_rtc_time
 * Description   : Reads the current RTC time and date using the consolidated
 *                 time and date registers (CTIME0 and CTIME1), extracts the
 *                 individual fields, and displays them on the LCD.
 *
 * Parameters    : None.
 * Return        : None.
 *
 * Dependencies  : LPC21xx RTC registers, LCD driver and LCD display functions.
 ******************************************************************************/
void print_rtc_time(void)
{
    /* Local variables for storing consolidated RTC register values. */
    unsigned int time_snapshot;
    unsigned int date_snapshot;

    /* Variables for individual RTC time and date fields. */
    unsigned int sec, min, hour, dow;
    unsigned int date, month, year;

    /***************************************************************************
     * Read and Extract RTC Time
     **************************************************************************/

    /* Read the consolidated RTC time register. */
    time_snapshot = CTIME0;
	DOW=1;

    /* Extract seconds, minutes, hours and day-of-week fields. */
    sec  =  time_snapshot        & 0x3F;
    min  = (time_snapshot >> 8)  & 0x3F;
    hour = (time_snapshot >> 16) & 0x1F;
    dow  = (time_snapshot >> 24) & 0x07;

    /***************************************************************************
     * Read and Extract RTC Date
     **************************************************************************/

    /* Read the consolidated RTC date register. */
    date_snapshot = CTIME1;

    /* Extract date, month and year fields. */
    date  =  date_snapshot        & 0x3F;
    month = (date_snapshot >> 8)  & 0x0F;
    year  = (date_snapshot >> 16) & 0x0FFF;

    /***************************************************************************
     * Display RTC Time on LCD - First Line
     **************************************************************************/

    /* Position the LCD cursor at the beginning of the first line. */
    CmdLCD(GOTO_LINE1_POS0);

    /* Display time in HH:MM:SS format. */
    CharLCD((hour / 10) + '0');
    CharLCD((hour % 10) + '0');
    CharLCD(':');

    CharLCD((min / 10) + '0');
    CharLCD((min % 10) + '0');
    CharLCD(':');

    CharLCD((sec / 10) + '0');
    CharLCD((sec % 10) + '0');

    /* Display the day-of-week abbreviation at LCD column 10. */
    CmdLCD(GOTO_LINE1_POS0 + 10);
    StrLCD((char *)day[dow]);

    /***************************************************************************
     * Display RTC Date on LCD - Second Line
     **************************************************************************/

    /* Position the LCD cursor at the beginning of the second line. */
    CmdLCD(GOTO_LINE2_POS0);

    /* Display date in DD/MM/YYYY format. */
    CharLCD((date / 10) + '0');
    CharLCD((date % 10) + '0');
    CharLCD('/');

    CharLCD((month / 10) + '0');
    CharLCD((month % 10) + '0');
    CharLCD('/');

    /* Display the four-digit year. */
    U32LCD(year);
}
