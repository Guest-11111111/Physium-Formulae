
#include <appdef.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <sdk/os/lcd.hpp>
#include <sdk/os/debug.hpp>
#include <sdk/os/input.hpp>
#include <sdk/calc/calc.hpp>
#include <sdk/os/string.hpp>
#include <string.h>



/*
 * Fill this section in with some information about your app.
 * All fields are optional - so if you don't need one, take it out.
 */
APP_NAME("Physium Formulae: Physics solver")
APP_DESCRIPTION("Bare physics solver. Will be updated. Press [EXE] for unpause. Use the action Bar Exit for ending the app.")
APP_AUTHOR("Guest-11111111")
APP_VERSION("1.0.0")



double getCommandInput(){
	char num[13]; //the command line
	int pos = 1; //the position of the cursor in num
	String_Strcpy(num,">_          ");

	struct InputEvent event;
	while (true){
		Debug_Printf(0,43,false,0,"%s",num); LCD_Refresh();
		GetInput(&event,0xFFFFFFFF,0x10);
		if(event.type==EVENT_KEY){
			if(event.data.key.direction==KEY_PRESSED){
				if(pos<=10){//If we have have less than 11 chars ('>' + 10 digits)
					switch (event.data.key.keyCode){
						case KEYCODE_0: num[pos++]='0';num[pos]='_';break;
						case KEYCODE_1: num[pos++]='1';num[pos]='_';break;
						case KEYCODE_2: num[pos++]='2';num[pos]='_';break;
						case KEYCODE_3: num[pos++]='3';num[pos]='_';break;
						case KEYCODE_4: num[pos++]='4';num[pos]='_';break;
						case KEYCODE_5: num[pos++]='5';num[pos]='_';break;
						case KEYCODE_6: num[pos++]='6';num[pos]='_';break;
						case KEYCODE_7: num[pos++]='7';num[pos]='_';break;
						case KEYCODE_8: num[pos++]='8';num[pos]='_';break;
						case KEYCODE_9: num[pos++]='9';num[pos]='_';break;
						case KEYCODE_DOT: 
							if (pos==1){
								if(num[1]=='.'){
									Debug_PrintString("ERROR! RESTART!", 0);
								}else{
									num[1]='.';
								}
							}break;
						case KEYCODE_KEYBOARD: Debug_PrintString("ERROR! ", 0);
						case KEYCODE_SHIFT: Debug_PrintString("ERROR", 1);
					}
				}//pos!<=8
				if (pos>1){ //If there are chars you can delete one.
					if(event.data.key.keyCode==KEYCODE_BACKSPACE){
						num[pos--]=' ';num[pos]='_';
					}//keycode!=Backspace
				}//pos!>1
				if(event.data.key.keyCode==KEYCODE_POWER_CLEAR){
					calcEnd();
				}//!Clear
				if(event.data.key.keyCode==KEYCODE_EXE){
					while(num[1]!='_'&&num[1]!='.'){
						int ret = num[1]-'0';
						int i=2;
						while(num[i]!='_'){
							ret = (ret*10) + (num[i]-'0');
							i++;
						}//num[i]!='_'
						return ret;
					}//num[1]!='_'
				}//!EXE
			}//direction!Pressed
		}else if(event.type==EVENT_TOUCH){
			if(event.data.touch_single.direction==TOUCH_UP){
				long y = event.data.touch_single.p1_y;
				y = y*341 >>12; //multiply by 341 and divide by 4096 to divide by 12
				if (y==1) return 99;
				else return (y-2);

			}//OUCH_UP
		}//EVENT_TOUCH
	}//while (true)
}

extern "C" ;
void main2() {
	while (true) {
	
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
					char buf[32];
					snprintf(buf, sizeof(buf), "GPE = %.20f", GPE);
					Debug_PrintString(buf, 0);
					Debug_PrintString("Press any key to exit answer",1);
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
        			Debug_SetCursorPosition(528,160);
	        		Debug_PrintString("Physium Formulae-ClΔssPΔd", 0);
    	    		Debug_PrintString("Mass =",0);
					double m = (GPE /(g*h));
					char buf[32];
					snprintf(buf, sizeof(buf), "Mass = %.20f", m);
					Debug_PrintString(buf, 0);
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
  	
}