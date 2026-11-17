
/*******************************************************************************
 * File Name : lcd.c
 * Description : LCD Driver Implementation for LPC21xx.
 *               Provides low-level LCD interfacing functions for
 *               command transmission, character transmission, string
 *               display, numeric display and custom character generation.
 *
 * Hardware    : 16x2 Character LCD.
 * Interface   : 8-bit parallel interface.
 ******************************************************************************/

#include <LPC21xx.h>

#include "lcd_defines.h"
#include "defines.h"
#include "types.h"
#include "delay.h"

/*******************************************************************************
 * Function Name : WriteLCD
 * Description   : Sends an 8-bit command or data byte to the LCD through
 *                 the parallel data interface.
 *
 *                 Performs the following operations:
 *                 1. Selects the LCD write operation.
 *                 2. Places the 8-bit data on the LCD data bus.
 *                 3. Generates the Enable pulse to latch the data.
 *                 4. Provides the required LCD execution delay.
 *
 * Parameters    : byte - 8-bit command or data value to be transmitted.
 * Return        : void.
 * Dependencies  : GPIO registers and delay driver.
 ******************************************************************************/
void WriteLCD(u8 byte)
{
    // Select the LCD write operation by driving RW LOW.
    IOCLR0 = 1 << LCD_RW;

    // Place the 8-bit command or data value on LCD data pins D0-D7.
    WRITEBYTE(IOPIN0, LCD_DATA, byte);

    // Generate the LCD Enable pulse to latch the transmitted byte.
    IOSET0 = 1 << LCD_EN;

    // Maintain the Enable signal HIGH for the required pulse width.
    delay_us(1);

    // Drive the Enable signal LOW to complete the write operation.
    IOCLR0 = 1 << LCD_EN;

    // Provide the LCD instruction execution delay.
    delay_ms(2);
}

/*******************************************************************************
 * Function Name : CmdLCD
 * Description   : Sends an instruction or command byte to the LCD.
 *
 *                 Selects the LCD instruction register by driving RS LOW
 *                 and transmits the command through the WriteLCD() routine.
 *
 * Parameters    : cmd - LCD instruction or command byte.
 * Return        : void.
 * Dependencies  : WriteLCD().
 ******************************************************************************/
void CmdLCD(u8 cmd)
{
    // Select the LCD instruction register by driving RS LOW.
    IOCLR0 = 1 << LCD_RS;

    // Transmit the command byte to the LCD.
    WriteLCD(cmd);
}

/*******************************************************************************
 * Function Name : InitLCD
 * Description   : Initializes the 16x2 character LCD in 8-bit interface mode.
 *
 *                 Configures the LCD interface GPIO pins as outputs and
 *                 executes the LCD initialization sequence.
 *
 *                 Initialization Sequence:
 *                 1. Configure LCD data and control pins as GPIO outputs.
 *                 2. Wait for LCD power stabilization.
 *                 3. Execute the LCD initialization sequence.
 *                 4. Configure 8-bit interface and two-line display mode.
 *                 5. Enable display and disable cursor.
 *                 6. Clear the LCD display.
 *                 7. Configure cursor movement direction.
 *
 * Parameters    : None.
 * Return        : void.
 * Dependencies  : LCD command definitions and delay driver.
 ******************************************************************************/
void InitLCD(void)
{
    // Configure LCD data bus D0-D7 and control pins RS, RW and EN
    // as GPIO output pins.
    // WRITEBYTE(IODIR0, LCD_DATA, 0xFF);
    // SETBIT(IODIR0, LCD_RS);
    // SETBIT(IODIR0, LCD_RW);
    // SETBIT(IODIR0, LCD_EN);

    IODIR0 |= (0xFF << LCD_DATA) | (1 << LCD_RS) |
              (1 << LCD_RW) | (1 << LCD_EN);

    // Wait for the LCD power supply to stabilize after initialization.
    delay_ms(15);

    // Execute the first initialization command.
    CmdLCD(0x30);

    // Provide the required initialization delay.
    delay_ms(4);
    delay_us(100);

    // Execute the second initialization command.
    CmdLCD(0x30);

    // Provide the required initialization delay.
    delay_us(100);

    // Execute the third initialization command.
    CmdLCD(0x30);

    // Configure the LCD for 8-bit interface and two-line display mode.
    CmdLCD(MODE_8BIT_2LINE);

    // Enable the LCD display and disable the cursor.
    CmdLCD(DSP_ON_CUR_OFF);

    // Clear all characters from the LCD display.
    CmdLCD(CLEAR_LCD);

    // Configure the cursor to move towards the right after data entry.
    CmdLCD(SHIFT_CUR_RIGHT);
}

/*******************************************************************************
 * Function Name : CharLCD
 * Description   : Displays a single ASCII character on the LCD.
 *
 *                 Selects the LCD data register by driving RS HIGH
 *                 and transmits the character using WriteLCD().
 *
 * Parameters    : asciiVal - ASCII character to be displayed.
 * Return        : void.
 * Dependencies  : WriteLCD().
 ******************************************************************************/
void CharLCD(u8 asciiVal)
{
    // Select the LCD data register by driving RS HIGH.
    IOSET0 = 1 << LCD_RS;

    // Transmit the ASCII character to the LCD.
    WriteLCD(asciiVal);
}

/*******************************************************************************
 * Function Name : StrLCD
 * Description   : Displays a null-terminated character string on the LCD.
 *
 *                 Transmits each character sequentially until the
 *                 null terminator is encountered.
 *
 * Parameters    : s - Pointer to the null-terminated string.
 * Return        : void.
 * Dependencies  : CharLCD().
 ******************************************************************************/
void StrLCD(s8 *s)
{
    // Transmit characters sequentially until the null terminator is reached.
    while(*s)
        CharLCD(*s++);
}

/*******************************************************************************
 * Function Name : U32LCD
 * Description   : Converts an unsigned 32-bit integer into ASCII decimal
 *                 characters and displays the resulting number on the LCD.
 *
 *                 Extracts individual decimal digits and stores them
 *                 in reverse order before transmitting them in the
 *                 correct display order.
 *
 * Parameters    : n - Unsigned integer value to be displayed.
 * Return        : void.
 * Dependencies  : CharLCD().
 ******************************************************************************/
void U32LCD(u32 n)
{
    s32 i = 0;
    u8 a[10];

    // Handle zero as a special case.
    if(n == 0)
    {
        // Display ASCII character '0'.
        CharLCD('0');
    }
    else
    {
        // Extract individual decimal digits in reverse order.
        while(n > 0)
        {
            // Convert the extracted digit into its corresponding ASCII value.
            a[i++] = (n % 10) + 48;

            // Remove the least significant decimal digit.
            n /= 10;
        }

        // Display the extracted digits in the correct order.
        for(--i; i >= 0; i--)
        {
            CharLCD(a[i]);
        }
    }
}

/*******************************************************************************
 * Function Name : S32LCD
 * Description   : Displays a signed 32-bit integer on the LCD.
 *
 *                 Checks the sign of the input value, displays a negative
 *                 sign when required and transmits the magnitude using
 *                 the unsigned integer display routine.
 *
 * Parameters    : n - Signed integer value to be displayed.
 * Return        : void.
 * Dependencies  : CharLCD(), U32LCD().
 ******************************************************************************/
void S32LCD(s32 n)
{
    // Check whether the input value is negative.
    if(n < 0)
    {
        // Display the negative sign.
        CharLCD('-');

        // Convert the negative value into its positive equivalent.
        n = -n;
    }

    // Display the magnitude of the signed integer.
    U32LCD(n);
}

/*******************************************************************************
 * Function Name : F32LCD
 * Description   : Displays a floating-point value on the LCD with
 *                 the specified number of decimal places.
 *
 *                 Separates the integer and fractional portions
 *                 and converts each fractional digit into ASCII
 *                 before displaying it.
 *
 * Parameters    : fn  - Floating-point value to be displayed.
 *                 nDP - Number of decimal places to be displayed.
 * Return        : void.
 * Dependencies  : CharLCD(), U32LCD().
 ******************************************************************************/
void F32LCD(f32 fn, u8 nDP)
{
    u32 n, i;

    // Check whether the floating-point value is negative.
    if(fn < 0.0)
    {
        // Display the negative sign.
        CharLCD('-');

        // Convert the value into its positive equivalent.
        fn = -fn;
    }

    // Extract and display the integer portion of the floating-point value.
    n = fn;
    U32LCD(n);

    // Display the decimal point.
    CharLCD('.');

    // Extract and display the required number of fractional digits.
    for(i = 0; i < nDP; i++)
    {
        // Shift the fractional portion one decimal position to the left.
        fn = (fn - n) * 10;

        // Extract the next fractional digit.
        n = fn;

        // Convert the numeric digit into its corresponding ASCII character.
        CharLCD(n + 48);
    }
}

/*******************************************************************************
 * Function Name : BuildCGRAM
 * Description   : Creates a custom character pattern in the LCD
 *                 Character Generator RAM (CGRAM).
 *
 *                 Configures the LCD CGRAM address based on the selected
 *                 custom character location and writes the specified
 *                 character bitmap data into CGRAM.
 *
 * Parameters    : p        - Pointer to the custom character bitmap array.
 *                 nBytes   - Number of bitmap bytes to be written.
 *                 location - Custom character location in CGRAM.
 * Return        : void.
 * Dependencies  : CmdLCD(), WriteLCD().
 ******************************************************************************/
void BuildCGRAM(u8 *p, u8 nBytes, u8 location)
{
    u32 i;

    // Set the LCD CGRAM address for the selected custom character location.
    // Each 5x8 custom character requires 8 CGRAM bytes.
    // CmdLCD(GOTO_CGRAM_START);
    CmdLCD(GOTO_CGRAM_START + (location * 8));

    // Select the LCD write operation.
    IOCLR0 = 1 << LCD_RW;

    // Select the LCD data register for writing CGRAM bitmap data.
    IOSET0 = 1 << LCD_RS;

    // Write the custom character bitmap data into CGRAM.
    for(i = 0; i < nBytes; i++)
    {
        // Transmit the current bitmap row through the LCD data register.
        WriteLCD(p[i]);
    }

    // Return the LCD cursor address to the beginning of DDRAM line 1.
    CmdLCD(GOTO_LINE1_POS0);
}
