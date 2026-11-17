
#include "automatic_street_light_project_defines.h"
#include "LCD.h"
#include "LCD_defines.h"
#include "delay.h"

/*******************************************************************************
 * Function Name : rtc_time_edit_init
 * Description   : Initializes and displays the RTC and automatic street
 *                 light timing configuration menu on the LCD.
 *
 *                 Displays an editing mode notification followed by
 *                 the available configuration options:
 *
 *                 1. RTC EDIT  - Configure RTC date and time parameters.
 *                 2. TIME EDIT - Configure street light starting and
 *                                ending time parameters.
 *
 * Parameters    : None.
 * Return        : void.
 * Dependencies  : LCD driver and Delay driver modules.
 ******************************************************************************/
void rtc_time_edit_init(void)
{
    // Clear the LCD display before showing the editing mode notification.
    CmdLCD(CLEAR_LCD);

    // Position the LCD cursor at the beginning of the first row.
    CmdLCD(GOTO_LINE1_POS0);

    // Display the editing mode activation message.
    StrLCD("EDITING MODE ON");

    // Introduce a short delay to allow the user to view the notification.
    delay_ms(100);

    // Clear the LCD before displaying the configuration menu.
    CmdLCD(CLEAR_LCD);

    // Position the LCD cursor at the beginning of the first row.
    CmdLCD(GOTO_LINE1_POS0);

    // Display the RTC configuration menu option.
    StrLCD("1.RTC EDIT 3.D");

    // Position the LCD cursor at the beginning of the second row.
    CmdLCD(GOTO_LINE2_POS0);

    // Display the street light timing configuration menu option.
    StrLCD("2.Time EDIT 4.E");

    // Return control to the calling application.
    return;
}
