
#include "lpc21xx.h"
#include "RTC_edit.h"
#include "time_edit.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm.h"
#include "kpm_defines.h"
#include "types.h"
#include "rtc.h"
#include "rtc_defines.h"
#include "delay.h"
#include "automatic_street_light_project.h"


/*******************************************************************************
 * Global Variable Declarations
 ******************************************************************************/

/*
 * Variable Name : RTC_HOUR
 * Description   : Temporarily stores the user-entered RTC hour value
 *                 before validating and updating the RTC HOUR register.
 */
unsigned int RTC_HOUR;

/*
 * Variable Name : RTC_MIN
 * Description   : Temporarily stores the user-entered RTC minute value
 *                 before validating and updating the RTC MIN register.
 */
unsigned int RTC_MIN;

/*
 * Variable Name : RTC_SEC
 * Description   : Temporarily stores the user-entered RTC second value
 *                 before validating and updating the RTC SEC register.
 */
unsigned int RTC_SEC;

/*
 * Variable Name : RTC_DATE
 * Description   : Temporarily stores the user-entered date value
 *                 before validating and updating the RTC DOM register.
 */
unsigned int RTC_DATE;

/*
 * Variable Name : RTC_DAY
 * Description   : Temporarily stores the user-entered day-of-week value
 *                 before validating and updating the RTC DOW register.
 */
unsigned int RTC_DAY;

/*
 * Variable Name : RTC_MONTH
 * Description   : Temporarily stores the user-entered month value
 *                 before validating and updating the RTC MONTH register.
 */
unsigned int RTC_MONTH;

/*
 * Variable Name : RTC_YEAR
 * Description   : Temporarily stores the user-entered year value
 *                 before validating and updating the RTC YEAR register.
 */
unsigned int RTC_YEAR;

/*
 * Variable Name : key_pressed_value
 * Description   : Stores the keypad key value selected by the user
 *                 to identify the RTC configuration operation.
 * Initial Value : 0.
 */
u32 key_pressed_value = 0;

/*
 * Variable Name : lastKey
 * Description   : Stores the last keypad key detected during numeric
 *                 data entry through the ReadNum2() routine.
 */
u8 lastKey;

/*******************************************************************************
 * Function Name : rtc_edit
 * Description   : Provides a keypad-based interface to configure RTC
 *                 time and calendar parameters.
 *
 *                 Displays an RTC configuration menu on the LCD and
 *                 allows the user to modify the following parameters:
 *
 *                 1. Hour
 *                 2. Minute
 *                 3. Second
 *                 4. Day of the week
 *                 5. Date
 *                 6. Month
 *                 7. Year
 *                 8. Exit
 *
 *                 Each entered value is validated against its
 *                 corresponding permissible range before updating
 *                 the RTC register.
 *
 * Parameters    : None.
 * Return        : None.
 * Dependencies  : RTC, LCD, Keypad and Delay driver modules.
 ******************************************************************************/
void rtc_edit()
{
    // Initialize the LCD peripheral for displaying RTC configuration options.
    InitLCD();

    // Initialize the RTC peripheral.
    rtc_init();

    // Initialize the keypad interface for user input.
    InitKPM();

    /***************************************************************************
     * RTC Configuration Menu
     **************************************************************************/

    // Display the RTC configuration menu.
    ex:
    CmdLCD(CLEAR_LCD);

    // Position the cursor at the beginning of the first LCD row.
    CmdLCD(GOTO_LINE1_POS0);

    // Display the first four RTC configuration options.
    StrLCD("1.H 2.M 3.S 4.D");

    // Position the cursor at the beginning of the second LCD row.
    CmdLCD(GOTO_LINE2_POS0);

    // Display the remaining configuration options.
    StrLCD("5.d 6.M 7.Y 8.E");

    // Reset the previous keypad selection.
    key_pressed_value = 0;

    // Wait until all keypad column inputs are released.
    while(ColScan() != 0);

    // Read the key pressed by the user.
    key_pressed_value = KeyScan();

    // Introduce a short delay after keypad scanning.
    delay_ms(100);

    // Select the RTC configuration operation based on the pressed key.
    switch(key_pressed_value)
    {
        /***********************************************************************
         * Case 1: RTC Hour Configuration
         **********************************************************************/

        case '1':

            // Clear the LCD and display the hour entry prompt.
            CmdLCD(CLEAR_LCD);
            StrLCD("hour value enter");

            // Position the cursor at the beginning of the second LCD row.
            CmdLCD(GOTO_LINE2_POS0);

            // Initialize the temporary hour variable.
            RTC_HOUR = 0;

            // Read the two-digit hour value entered through the keypad.
            ReadNum2(&RTC_HOUR, &lastKey);

            // Validate the entered hour against the 24-hour clock range.
            if(RTC_HOUR <= 23)
            {
                // Update the RTC hour register with the validated value.
                HOUR = RTC_HOUR;

                // Display the successful hour update message.
                CmdLCD(CLEAR_LCD);
                StrLCD("Hours updated");
            }
            else
            {
                // Display an error message for an invalid hour value.
                CmdLCD(CLEAR_LCD);
                StrLCD("out of range");
            }

            // Reset the temporary hour variable.
            RTC_HOUR = 0;

            // Return to the RTC configuration menu.
            goto ex;

        /***********************************************************************
         * Case 2: RTC Minute Configuration
         **********************************************************************/

        case '2':

            // Clear the LCD and display the minute entry prompt.
            CmdLCD(CLEAR_LCD);
            StrLCD("minutes enter");

            // Position the cursor at the beginning of the second LCD row.
            CmdLCD(GOTO_LINE2_POS0);

            // Initialize the temporary minute variable.
            RTC_MIN = 0;

            // Read the two-digit minute value entered through the keypad.
            ReadNum2(&RTC_MIN, &lastKey);

            // Validate the entered minute against the permissible range.
            if(RTC_MIN <= 59)
            {
                // Update the RTC minute register with the validated value.
                MIN = RTC_MIN;

                // Display the successful minute update message.
                CmdLCD(CLEAR_LCD);
                StrLCD("mins updated");
            }
            else
            {
                // Display an error message for an invalid minute value.
                CmdLCD(CLEAR_LCD);
                StrLCD("out of range");
            }

            // Reset the temporary minute variable.
            RTC_MIN = 0;

            // Return to the RTC configuration menu.
            goto ex;

        /***********************************************************************
         * Case 3: RTC Second Configuration
         **********************************************************************/

        case '3':

            // Clear the LCD and display the second entry prompt.
            CmdLCD(CLEAR_LCD);
            StrLCD("seconds enter");

            // Position the cursor at the beginning of the second LCD row.
            CmdLCD(GOTO_LINE2_POS0);

            // Initialize the temporary second variable.
            RTC_SEC = 0;

            // Read the two-digit second value entered through the keypad.
            ReadNum2(&RTC_SEC, &lastKey);

            // Validate the entered second against the permissible range.
            if(RTC_SEC <= 59)
            {
                // Update the RTC second register with the validated value.
                SEC = RTC_SEC;

                // Display the successful second update message.
                CmdLCD(CLEAR_LCD);
                StrLCD("secs updated");
            }
            else
            {
                // Display an error message for an invalid second value.
                CmdLCD(CLEAR_LCD);
                StrLCD("out of range");
            }

            // Reset the temporary second variable.
            RTC_SEC = 0;

            // Return to the RTC configuration menu.
            goto ex;

        /***********************************************************************
         * Case 4: RTC Day-of-Week Configuration
         **********************************************************************/

        case '4':

            // Clear the LCD and display the day entry prompt.
            CmdLCD(CLEAR_LCD);
            StrLCD("Day enter 0.SUN");

            // Position the cursor at the beginning of the second LCD row.
            CmdLCD(GOTO_LINE2_POS0);

            // Initialize the temporary day variable.
            RTC_DAY = 0;

            // Read the day-of-week value entered through the keypad.
            ReadNum2(&RTC_DAY, &lastKey);

            // Validate the day value against the range 0 to 6.
            if(RTC_DAY <= 6)
            {
                // Update the RTC day-of-week register.
                DOW = RTC_DAY;

                // Display the successful day update message.
                CmdLCD(CLEAR_LCD);
                StrLCD("Day updated");
            }
            else
            {
                // Display an error message for an invalid day value.
                CmdLCD(CLEAR_LCD);
                StrLCD("out of range");
            }

            // Reset the temporary day variable.
            RTC_DAY = 0;

            // Return to the RTC configuration menu.
            goto ex;

        /***********************************************************************
         * Case 5: RTC Date Configuration
         **********************************************************************/

        case '5':

            // Clear the LCD and display the date entry prompt.
            CmdLCD(CLEAR_LCD);
            StrLCD("Date enter");

            // Position the cursor at the beginning of the second LCD row.
            CmdLCD(GOTO_LINE2_POS0);

            // Initialize the temporary date variable.
            RTC_DATE = 0;

            // Read the date value entered through the keypad.
            ReadNum2(&RTC_DATE, &lastKey);

            // Check whether the current month is February.
            if(MONTH == 2)
            {
                // Determine whether the current year is a leap year.
                if((YEAR % 400 == 0) ||
                   ((YEAR % 4 == 0) && (YEAR % 100 != 0)))
                {
                    // Validate the date for February in a leap year.
                    if((RTC_DATE >= 1) && (RTC_DATE <= 29))
                    {
                        // Update the RTC date register.
                        DOM = RTC_DATE;

                        // Display the successful date update message.
                        CmdLCD(CLEAR_LCD);
                        StrLCD("Date updated");
                    }
                    else
                    {
                        // Display an error message for an invalid date.
                        CmdLCD(CLEAR_LCD);
                        StrLCD("out of range");
                    }
                }
                else
                {
                    // Validate the date for February in a non-leap year.
                    if((RTC_DATE >= 1) && (RTC_DATE <= 28))
                    {
                        // Update the RTC date register.
                        DOM = RTC_DATE;

                        // Display the successful date update message.
                        CmdLCD(CLEAR_LCD);
                        StrLCD("Date updated");
                    }
                    else
                    {
                        // Display an error message for an invalid date.
                        CmdLCD(CLEAR_LCD);
                        StrLCD("out of range");
                    }
                }
            }

            // Check months containing 31 days.
            else if(MONTH == 1 || MONTH == 3 || MONTH == 5 ||
                    MONTH == 7 || MONTH == 8 || MONTH == 10 ||
                    MONTH == 12)
            {
                // Validate the date against the 31-day month range.
                if((RTC_DATE >= 1) && (RTC_DATE <= 31))
                {
                    // Update the RTC date register.
                    DOM = RTC_DATE;

                    // Display the successful date update message.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Date updated");
                }
                else
                {
                    // Display an error message for an invalid date.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("out of range");
                }
            }
            else
            {
                // Validate the date against the 30-day month range.
                if(RTC_DATE <= 30)
                {
                    // Update the RTC date register.
                    DOM = RTC_DATE;

                    // Display the successful date update message.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("Date updated");
                }
                else
                {
                    // Display an error message for an invalid date.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("out of range");
                }
            }

            // Reset the temporary date variable.
            RTC_DATE = 0;

            // Return to the RTC configuration menu.
            goto ex;

        /***********************************************************************
         * Case 6: RTC Month Configuration
         **********************************************************************/

        case '6':

            // Clear the LCD and display the month entry prompt.
            CmdLCD(CLEAR_LCD);
            StrLCD("month enter");

            // Position the cursor at the beginning of the second LCD row.
            CmdLCD(GOTO_LINE2_POS0);

            // Initialize the temporary month variable.
            RTC_MONTH = 0;

            // Read the month value entered through the keypad.
            ReadNum2(&RTC_MONTH, &lastKey);

            // Validate months from 1 to 12, excluding February.
            if((RTC_MONTH >= 1) && (RTC_MONTH <= 12) &&
               (RTC_MONTH != 2))
            {
                // Update the RTC month register.
                MONTH = RTC_MONTH;

                // Display the successful month update message.
                CmdLCD(CLEAR_LCD);
                StrLCD("mon updated");
            }

            // Handle February as a special case.
            else if((RTC_MONTH >= 1) && (RTC_MONTH <= 12))
            {
                // Verify that the existing date is valid for February.
                if(DOM <= 29)
                {
                    // Update the RTC month register.
                    MONTH = RTC_MONTH;

                    // Display the successful month update message.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("mon updated");
                }
                else
                {
                    // Display an error message for an invalid date/month combination.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("out of range");
                }
            }
            else
            {
                // Display an error message for an invalid month value.
                CmdLCD(CLEAR_LCD);
                StrLCD("out of range");
            }

            // Reset the temporary month variable.
            RTC_MONTH = 0;

            // Return to the RTC configuration menu.
            goto ex;

        /***********************************************************************
         * Case 7: RTC Year Configuration
         **********************************************************************/

        case '7':

            // Clear the LCD and display the year entry prompt.
            CmdLCD(CLEAR_LCD);
            StrLCD("YEAR");

            // Position the cursor at the beginning of the second LCD row.
            CmdLCD(GOTO_LINE2_POS0);

            // Initialize the temporary year variable.
            RTC_YEAR = 0;

            // Read the year value entered through the keypad.
            ReadNum2(&RTC_YEAR, &lastKey);

            // Validate the year against the supported RTC range.
            if((RTC_YEAR >= 1) && (RTC_YEAR <= 4095))
            {
                // Update the RTC year register.
                YEAR = RTC_YEAR;

                // Display the successful year update message.
                CmdLCD(CLEAR_LCD);
                StrLCD("year updated");
            }
            else
            {
                // Display an error message for an invalid year value.
                CmdLCD(CLEAR_LCD);
                StrLCD("out of range");
            }

            // Reset the temporary year variable.
            RTC_YEAR = 0;

            // Return to the RTC configuration menu.
            goto ex;

        /***********************************************************************
         * Case 8: Exit RTC Configuration
         **********************************************************************/

        case '8':

            // Exit the RTC configuration menu.
            goto exi;
    }

    /***************************************************************************
     * RTC Configuration Exit
     **************************************************************************/

    // Clear the LCD display before returning to the calling function.
    exi:
    CmdLCD(CLEAR_LCD);

    // Return control to the calling application.
    return;
}
