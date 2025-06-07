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

double getCommandInput();

extern "C" ;
void main2() {
  calcInit();
  fillScreen(color(31,64,31));
  LCD_Refresh();
  Debug_SetCursorPosition(264,160);
	Debug_PrintString("Physium Formulae",0);
	Debug_SetCursorPosition(263, 160);
	Debug_PrintString("ClΔssPΔd",0);
	LCD_Refresh();
	while(true){
    	uint32_t key1, key2;    // First create variables
    	getKey(&key1, &key2);    // then read the keys
    	if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
    	    goto Main_Menu;
    	}else if(testKey(key1,key2, KEY_CLEAR )){
			goto End_Main;
		};
	}
	Main_Menu:
	fillScreen(color(31,64,31));
	LCD_Refresh();
	Debug_SetCursorPosition(0,160);
  	Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
	Debug_SetCursorPosition(6,1);
	Debug_PrintString("[1] Solver",0);
	Debug_SetCursorPosition(6,1);
	Debug_PrintString("[2] Formulas",0);
	Debug_SetCursorPosition(6,2);
	Debug_PrintString("[3] Exit",0);
	LCD_Refresh();
	uint32_t Menukey, MenKey;
	getKey(&Menukey, &MenKey);
	if(Menukey == KEY_1){
		fillScreen(color(31,63,31));
		LCD_Refresh();
		Debug_SetCursorPosition(6,0);
      	Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
		Debug_SetCursorPosition(6,2);
		Debug_PrintString("Main Solver Menu",0);
		Debug_SetCursorPosition(6,1);
		Debug_PrintString("[1] GPE  GPE = m*g*h",0);
		Debug_SetCursorPosition(6,2);
		Debug_PrintString("[2] Force m*a, m*g",0);
		Debug_SetCursorPosition(6,3);
		Debug_PrintString("[3] Acceleration ΔV / Δt, a = F/m",0);
		Debug_SetCursorPosition(6,4);
		Debug_PrintString("[4] Velocity (d/t) & direction",0);
		LCD_Refresh();
		uint32_t SMenukey;
		uint32_t Skey;
		getKey(&SMenukey, &Skey);
		LCD_Refresh();
		if(SMenukey == KEY_1){
      		Debug_SetCursorPosition(0,160);
      		Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
			Debug_SetCursorPosition(6,0);
			Debug_PrintString("GPE Solver Submenu",0);
			Debug_SetCursorPosition(6,1);
			Debug_PrintString("[1] GPE",0);
			Debug_SetCursorPosition(6,2);
			Debug_PrintString("[2] Mass",0);
			Debug_SetCursorPosition(6,3);
			Debug_PrintString("[3] Acceleration to Gravity",0);
			Debug_SetCursorPosition(6,4);
			Debug_PrintString("[4] Height",0);
			LCD_Refresh();
			uint32_t GPEKey;
			uint32_t ConfGPE;
			getKey(&GPEKey, &ConfGPE);
			LCD_Refresh();
			if(GPEKey == KEY_1){
				Debug_SetCursorPosition(264,160);
				Debug_PrintString("Mass?",0);
				double m = getCommandInput();
				LCD_ClearScreen();
				Debug_PrintString("Acceleration to Gravity, g on earth is ~9.8 m/s^2 & is exactly 9.80665 m/s^2",0);
				double g = getCommandInput();
				LCD_ClearScreen();
				Debug_PrintString("Height?",1);
				double h = getCommandInput();
				double GPE;
				GPE = g*m*h;
				LCD_ClearScreen();
				Debug_PrintString("Press any key to exit answer",0);
				Debug_SetCursorPosition(264, 159);
				Debug_PrintString("%d",0);
				while(true){
    				uint32_t key1, key2;    // First create variables
      				getKey(&key1, &key2);    // then read the keys
      				if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
      				    goto Main_Menu;
        			}
	      		}
			}else if(GPEKey == KEY_2){
        		Debug_SetCursorPosition(528,160);
        		Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
				Debug_SetCursorPosition(264,160);
				Debug_PrintString("GPE=?",0);
				LCD_Refresh();
				double GPE = getCommandInput();
        		LCD_ClearScreen();
	        	Debug_SetCursorPosition(528,160);
    	    	Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
	        	Debug_PrintString("Acceleration to Gravity, g on earth is ~9.8 m/s^2 & is exactly 9.80665 m/s^2",0);
    	    	LCD_Refresh();
        		double g = getCommandInput();
        		LCD_ClearScreen();
        		Debug_SetCursorPosition(528,160);
        		Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
        		Debug_PrintString("Height=?",0);
        		LCD_Refresh();
        		double h = getCommandInput();
        		LCD_ClearScreen();
        		double m = (GPE /(g*h));
        		Debug_SetCursorPosition(528,160);
        		Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
        		Debug_PrintString("Mass =",0);
        		Debug_PrintString("%d", 0);
        		LCD_Refresh();
        		Debug_WaitKey();
			}else if(GPEKey == KEY_3){
        		Debug_SetCursorPosition(528,160);
        		Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
        		Debug_SetCursorPosition(264, 160);
				Debug_PrintString("PLACEHOLDER", 0);
				while(true){
    	  			uint32_t key1, key2;    // First create variables
      				getKey(&key1, &key2);    // then read the keys
      				if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
      	    		goto Main_Menu;
        		};
	    		  };
			}
		
		}
					
	}else if (Menukey == KEY_2){
	    Debug_SetCursorPosition(528,160);
    	Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
    	Debug_SetCursorPosition(264,0);
		Debug_PrintString("Formulas",0);
	}else if (Menukey == KEY_3){
    	Debug_SetCursorPosition(528,160);
    	Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
    	Debug_SetCursorPosition(264,160);
    	Debug_PrintString("Program Terminating...",0);
    	LCD_Refresh();
		goto End_Main;
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

		
	End_Main:
	calcEnd();
}