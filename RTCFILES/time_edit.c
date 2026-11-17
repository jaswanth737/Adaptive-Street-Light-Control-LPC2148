
#include <lpc21xx.h>

#include "time_edit.h"
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
#include "types.h"
#include "automatic_street_light_project.h"
/*******************************************************************************
 * Global Variable Declarations
 ******************************************************************************/

/*
 * Variable Name : LED_START_HOUR
 * Description   : Stores the user-configured starting hour for automatic
 *                 street light operation.
 */
unsigned int LED_START_HOUR=18;

/*
 * Variable Name : LED_START_MIN
 * Description   : Stores the user-configured starting minute for automatic
 *                 street light operation.
 */
unsigned int LED_START_MIN=00;

/*
 * Variable Name : LED_START_SEC
 * Description   : Stores the user-configured starting second for automatic
 *                 street light operation.
 */
unsigned int LED_START_SEC=00;

/*
 * Variable Name : LED_END_HOUR
 * Description   : Stores the user-configured ending hour for automatic
 *                 street light operation.
 */
unsigned int LED_END_HOUR=5;

/*
 * Variable Name : LED_END_MIN
 * Description   : Stores the user-configured ending minute for automatic
 *                 street light operation.
 */
unsigned int LED_END_MIN=59;

/*
 * Variable Name : LED_END_SEC
 * Description   : Stores the user-configured ending second for automatic
 *                 street light operation.
 */
unsigned int LED_END_SEC=59;

/*
 * Variable Name : key_pressed_value1
 * Description   : Stores the keypad selection used to navigate between
 *                 starting-time and ending-time configuration menus.
 * Initial Value : 0.
 */
u32 key_pressed_value1 = 0;

/*
 * Variable Name : s_h, s_m, s_s
 * Description   : Temporary variables used to capture the starting
 *                 hour, minute and second values entered through
 *                 the keypad before validation.
 */
u32 s_h, s_m, s_s;

/*
 * Variable Name : e_h, e_m, e_s
 * Description   : Temporary variables used to capture the ending
 *                 hour, minute and second values entered through
 *                 the keypad before validation.
 */
u32 e_h, e_m, e_s;

/*
 * Variable Name : lastKey1
 * Description   : Stores the last keypad key detected during numeric
 *                 input operations.
 */
u8 lastKey1;

/*******************************************************************************
 * Function Name : time_edit
 * Description   : Provides a keypad-based configuration interface for
 *                 setting the automatic street light ON and OFF timings.
 *
 *                 The user can configure:
 *
 *                 Starting Time:
 *                   1. Starting Hour
 *                   2. Starting Minute
 *                   3. Starting Second
 *                   4. Exit
 *
 *                 Ending Time:
 *                   1. Ending Hour
 *                   2. Ending Minute
 *                   3. Ending Second
 *                   4. Exit
 *
 *                 Each entered time parameter is validated before
 *                 updating the corresponding application variable.
 *
 * Parameters    : None.
 * Return        : None.
 * Dependencies  : LCD, Keypad and Delay driver modules.
 ******************************************************************************/
void time_edit()
{
    // Initialize the LCD peripheral for displaying time configuration menus.
    InitLCD();

    // Initialize the keypad interface for user input.
    InitKPM();

    /***************************************************************************
     * Main Time Configuration Menu
     **************************************************************************/

    // Display the starting-time and ending-time selection menu.
    ex1:
    CmdLCD(CLEAR_LCD);

    // Position the LCD cursor at the beginning of the first row.
    CmdLCD(GOTO_LINE1_POS0);

    // Display the starting-time configuration option.
    StrLCD("1.starting time");

    // Position the LCD cursor at the beginning of the second row.
    CmdLCD(GOTO_LINE2_POS0);

    // Display the ending-time configuration and exit options.
    StrLCD("2.End time  3.Ex");

    // Reset the previous keypad selection.
    key_pressed_value1 = 0;

    // Wait until all keypad column inputs are released.
    while(ColScan() != 0);

    // Read the key pressed by the user.
    key_pressed_value1 = KeyScan();

    /***************************************************************************
     * Starting-Time Configuration
     **************************************************************************/

    // Enter the starting-time configuration menu when key '1' is selected.
    while(key_pressed_value1 == '1')
    {
        // Display the starting-time parameter selection menu.
        ex2:
        CmdLCD(CLEAR_LCD);

        // Position the LCD cursor at the beginning of the first row.
        CmdLCD(GOTO_LINE1_POS0);

        // Display the starting hour and minute options.
        StrLCD("1.S_h 2.S_m");

        // Position the LCD cursor at the beginning of the second row.
        CmdLCD(GOTO_LINE2_POS0);

        // Display the starting second and exit options.
        StrLCD("3.S_s 4.Exit");

        // Reset the previous keypad selection.
        key_pressed_value1 = 0;

        // Wait until all keypad column inputs are released.
        while(ColScan() != 0);

        // Read the selected keypad key.
        key_pressed_value1 = KeyScan();

        // Introduce a short delay after keypad scanning.
        delay_ms(50);

        // Select the starting-time parameter to be configured.
        switch(key_pressed_value1)
        {
            /*******************************************************************
             * Case 1: Starting Hour Configuration
             ******************************************************************/

            case '1':

                // Clear the LCD and display the starting-hour entry prompt.
                CmdLCD(CLEAR_LCD);
                StrLCD("hour value enter");

                // Position the cursor at the beginning of the second LCD row.
                CmdLCD(GOTO_LINE2_POS0);

                // Initialize the temporary starting-hour variable.
                s_h = 0;

                // Read the two-digit starting-hour value through the keypad.
                ReadNum2(&s_h, &lastKey1);

                // Validate the entered hour against the 24-hour clock range.
                if(s_h <= 23)
                {
                    // Store the validated value in the starting-hour variable.
                    LED_START_HOUR = s_h;

                    // Display the successful starting-hour update message.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("s_Hours updated");

                    // Allow the user to observe the confirmation message.
                    delay_ms(200);

                    // Clear the LCD before returning to the configuration menu.
                    CmdLCD(CLEAR_LCD);
                    CmdLCD(GOTO_LINE1_POS0);
                }
                else
                {
                    // Display an error message for an invalid hour value.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("out of range");
                }

                // Reset the temporary starting-hour variable.
                s_h = 0;

                // Return to the starting-time parameter selection menu.
                goto ex2;

            /*******************************************************************
             * Case 2: Starting Minute Configuration
             ******************************************************************/

            case '2':

                // Clear the LCD and display the starting-minute entry prompt.
                CmdLCD(CLEAR_LCD);
                StrLCD("min value enter");

                // Position the cursor at the beginning of the second LCD row.
                CmdLCD(GOTO_LINE2_POS0);

                // Initialize the temporary starting-minute variable.
                s_m = 0;

                // Read the two-digit starting-minute value through the keypad.
                ReadNum2(&s_m, &lastKey1);

                // Validate the entered minute against the permissible range.
                if(s_m <= 59)
                {
                    // Store the validated value in the starting-minute variable.
                    LED_START_MIN = s_m;

                    // Display the successful starting-minute update message.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("s_mins updated");

                    // Allow the user to observe the confirmation message.
                    delay_ms(200);
                }
                else
                {
                    // Display an error message for an invalid minute value.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("out of range");
                }

                // Reset the temporary starting-minute variable.
                s_m = 0;

                // Return to the starting-time parameter selection menu.
                goto ex2;

            /*******************************************************************
             * Case 3: Starting Second Configuration
             ******************************************************************/

            case '3':

                // Clear the LCD and display the starting-second entry prompt.
                CmdLCD(CLEAR_LCD);
                StrLCD("sec value enter");

                // Position the cursor at the beginning of the second LCD row.
                CmdLCD(GOTO_LINE2_POS0);

                // Initialize the temporary starting-second variable.
                s_s = 0;

                // Read the two-digit starting-second value through the keypad.
                ReadNum2(&s_s, &lastKey1);

                // Validate the entered second against the permissible range.
                if(s_s <= 59)
                {
                    // Store the validated value in the starting-second variable.
                    LED_START_SEC = s_s;

                    // Display the successful starting-second update message.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("s_seconds updated");

                    // Allow the user to observe the confirmation message.
                    delay_ms(200);
                }
                else
                {
                    // Display an error message for an invalid second value.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("out of range");
                }

                // Reset the temporary starting-second variable.
                s_s = 0;

                // Return to the starting-time parameter selection menu.
                goto ex2;

            /*******************************************************************
             * Case 4: Exit Starting-Time Configuration
             ******************************************************************/

            case 4:

                // Return to the main time configuration menu.
                goto ex1;
        }
    }

    /***************************************************************************
     * Ending-Time Configuration
     **************************************************************************/

    // Enter the ending-time configuration menu when key '2' is selected.
    while(key_pressed_value1 == '2')
    {
        // Display the ending-time parameter selection menu.
        ex3:
        CmdLCD(CLEAR_LCD);

        // Position the LCD cursor at the beginning of the first row.
        CmdLCD(GOTO_LINE1_POS0);

        // Display the ending-hour and ending-minute options.
        StrLCD("1.E_h 2.E_m");

        // Position the LCD cursor at the beginning of the second row.
        CmdLCD(GOTO_LINE2_POS0);

        // Display the ending-second and exit options.
        StrLCD("3.E_s 4.Exit");

        // Reset the previous keypad selection.
        key_pressed_value1 = 0;

        // Wait until all keypad column inputs are released.
        while(ColScan() != 0);

        // Read the selected keypad key.
        key_pressed_value1 = KeyScan();

        // Introduce a short delay after keypad scanning.
        delay_ms(50);

        // Select the ending-time parameter to be configured.
        switch(key_pressed_value1)
        {
            /*******************************************************************
             * Case 1: Ending Hour Configuration
             ******************************************************************/

            case '1':

                // Clear the LCD and display the ending-hour entry prompt.
                CmdLCD(CLEAR_LCD);
                StrLCD("e_hour value enter");

                // Position the cursor at the beginning of the second LCD row.
                CmdLCD(GOTO_LINE2_POS0);

                // Initialize the temporary ending-hour variable.
                e_h = 0;

                // Read the two-digit ending-hour value through the keypad.
                ReadNum2(&e_h, &lastKey1);

                // Validate the entered hour against the 24-hour clock range.
                if(e_h <= 23)
                {
                    // Store the validated value in the ending-hour variable.
                    LED_END_HOUR = e_h;

                    // Display the successful ending-hour update message.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("e_Hours updated");

                    // Allow the user to observe the confirmation message.
                    delay_ms(200);
                }
                else
                {
                    // Display an error message for an invalid hour value.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("out of range");
                }

                // Reset the temporary ending-hour variable.
                e_h = 0;

                // Return to the ending-time parameter selection menu.
                goto ex3;

            /*******************************************************************
             * Case 2: Ending Minute Configuration
             ******************************************************************/

            case '2':

                // Clear the LCD and display the ending-minute entry prompt.
                CmdLCD(CLEAR_LCD);
                StrLCD("e_min value enter");

                // Position the cursor at the beginning of the second LCD row.
                CmdLCD(GOTO_LINE2_POS0);

                // Initialize the temporary ending-minute variable.
                e_m = 0;

                // Read the two-digit ending-minute value through the keypad.
                ReadNum2(&e_m, &lastKey1);

                // Validate the entered minute against the permissible range.
                if(e_m <= 59)
                {
                    // Store the validated value in the ending-minute variable.
                    LED_END_MIN = e_m;

                    // Display the successful ending-minute update message.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("e_mins updated");

                    // Allow the user to observe the confirmation message.
                    delay_ms(200);
                }
                else
                {
                    // Display an error message for an invalid minute value.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("out of range");
                }

                // Reset the temporary ending-minute variable.
                e_m = 0;

                // Return to the ending-time parameter selection menu.
                goto ex3;

            /*******************************************************************
             * Case 3: Ending Second Configuration
             ******************************************************************/

            case '3':

                // Clear the LCD and display the ending-second entry prompt.
                CmdLCD(CLEAR_LCD);
                StrLCD("sec value enter");

                // Position the cursor at the beginning of the second LCD row.
                CmdLCD(GOTO_LINE2_POS0);

                // Initialize the temporary ending-second variable.
                e_s = 0;

                // Read the two-digit ending-second value through the keypad.
                ReadNum2(&e_s, &lastKey1);

                // Validate the entered second against the permissible range.
                if(e_s <= 59)
                {
                    // Store the validated value in the ending-second variable.
                    LED_END_SEC = e_s;

                    // Display the successful ending-second update message.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("e_seconds updated");

                    // Allow the user to observe the confirmation message.
                    delay_ms(200);
                }
                else
                {
                    // Display an error message for an invalid second value.
                    CmdLCD(CLEAR_LCD);
                    StrLCD("out of range");
                }

                // Reset the temporary ending-second variable.
                e_s = 0;

                // Return to the ending-time parameter selection menu.
                goto ex3;

            /*******************************************************************
             * Case 4: Exit Ending-Time Configuration
             ******************************************************************/

            case 4:

                // Return to the main time configuration menu.
                goto ex1;
        }
    }

    /***************************************************************************
     * Main Menu Exit Handling
     **************************************************************************/

    // Exit the time configuration interface when key '3' is selected.
    while(key_pressed_value1 == '3')
    {
        // Transfer control to the exit section.
        goto ex4;
    }

    // Clear the LCD display before returning to the calling application.
    ex4:
    CmdLCD(CLEAR_LCD);
}
