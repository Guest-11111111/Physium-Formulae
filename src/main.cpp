#include "sys/_intsup.h"
#include <appdef.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <sdk/os/lcd.hpp>
#include <sdk/os/debug.hpp>
#include <sdk/os/input.hpp>
#include <sdk/calc/calc.hpp>

/*
 * Fill this section in with some information about your app.
 * All fields are optional - so if you don't need one, take it out.
 */
APP_NAME("Physium Formulae: Physics solver")
APP_DESCRIPTION("Bare physics solver. Will be updated. Press [EXE] for unpause.")
APP_AUTHOR("Help_Programming")
APP_VERSION("1.0.2")

int getCommandInput();

extern "C" ;
void main2() {
  calcInit();
  fillScreen(color(31,64,31));
  LCD_Refresh();
  Debug_SetCursorPosition(264,160);
	Debug_PrintString("Physium Solver",1);
	Debug_SetCursorPosition(275, 160);
	Debug_PrintString("ClΔssPΔd",1);
	LCD_Refresh();
	while(true){
    	uint32_t key1, key2;    // First create variables
    	getKey(&key1, &key2);    // then read the keys
    	if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
    	    break;
    }
	}
	Main_Menu:
	fillScreen(color(31,64,31));
	LCD_Refresh();
	fillScreen(color(31,64,31));
	LCD_Refresh();
	Debug_SetCursorPosition(6,1);
	Debug_PrintString("[1] Solver",1);
	Debug_SetCursorPosition(6,1);
	Debug_PrintString("[2] Formulas",1);
	Debug_SetCursorPosition(6,2);
	Debug_PrintString("[3] Exit",1);
	LCD_Refresh();
	uint32_t Menukey;
	uint32_t MenKey;
	getKey(&Menukey, &MenKey);
	if(Menukey == KEY_1){
		fillScreen(color(31,63,31));
		LCD_Refresh();
		Debug_SetCursorPosition(6,0);
		Debug_PrintString("Main Solver Menu",1);
		Debug_SetCursorPosition(6,1);
		Debug_PrintString("[1] GPE  GPE = m*g*h",1);
		Debug_SetCursorPosition(6,2);
		Debug_PrintString("[2] Force m*a, m*g",1);
		Debug_SetCursorPosition(6,3);
		Debug_PrintString("[3] Acceleration ΔV / Δt, a = F/m",1);
		Debug_SetCursorPosition(6,4);
		Debug_PrintString("[4] Velocity (d/t) & direction",1);
		LCD_Refresh();
		uint32_t SMenukey;
		uint32_t Skey;
		getKey(&SMenukey, &Skey);
		LCD_Refresh();
		if(SMenukey == KEY_1){
			Debug_SetCursorPosition(6,0);
			Debug_PrintString("GPE Solver Submenu",1);
			Debug_SetCursorPosition(6,1);
			Debug_PrintString("[1] GPE",1);
			Debug_SetCursorPosition(6,2);
			Debug_PrintString("[2] Mass",1);
			Debug_SetCursorPosition(6,3);
			Debug_PrintString("[3] Acceleration to Gravity",1);
			Debug_SetCursorPosition(6,4);
			Debug_PrintString("[4] Height",1);
			LCD_Refresh();
			uint32_t GPEKey;
			uint32_t ConfGPE;
			getKey(&GPEKey, &ConfGPE);
			LCD_Refresh();
			if(GPEKey == KEY_1){
				Debug_SetCursorPosition(264,160);
				Debug_PrintString("Mass?",1);
				int m = getCommandInput();
				LCD_ClearScreen();
				Debug_PrintString("Acceleration to Gravity, g on earth is ~9.8 m/s^2 & is exactly 9.80665 m/s^2",1);
				int g = getCommandInput();
				LCD_ClearScreen();
				Debug_PrintString("Height?",1);
				int h = getCommandInput();
				int GPE;
				GPE = g*m*h;
				LCD_ClearScreen();
				Debug_PrintString("Press any key to exit answer",1);
				int d = GPE;
				Debug_SetCursorPosition(264, 150);
				Debug_PrintString("%d",1);
				if(Input_IsAnyKeyDown() == true){
					goto Main_Menu;
				}
			}else if(GPEKey == KEY_2){
				Debug_SetCursorPosition(264,160);
				Debug_PrintString("GPE=?",1);
				LCD_Refresh();
				int GPE = getCommandInput();

			}else if(GPEKey == KEY_3){
				Debug_PrintString("PLACEHOLDER", 1);
				Debug_WaitKey();
				goto Main_Menu;
			}
		
		}
					
	}else if (Menukey == KEY_2){
    Debug_SetCursorPosition(264,0);
		Debug_PrintString("Formulas",1);
	}else if (Menukey == KEY_3){
		
	}
						
			//if(testkey(SMenukey, KEY_1)){
			//	Debug_PrintString("GPE Solver Submenu");
			//	Debug_PrintString("[1] GPE");const char *string
			//	Debug_PrintString("[2] Mass");
			//	Debug_PrintString("[3] Acceleration to Gravity");
			//	Debug_PrintString("[4] Height");
			//	uint32_t GPEKey;
			//	getkey(&GPEKey);
			//	if(testkey())
			//	}
		//case KEY_2:
		//	Debug_PrintString(" Not Complete!",1);
		//	return 0;
		//case KEY_3:
		//	return 0;

		
	
	calcEnd();
}
