
#include <appdef.hpp>
#include <sdk/os/lcd.hpp>
#include <sdk/os/debug.hpp>
#include <sdk/os/input.hpp>
#include <sdk/calc/calc.hpp>
#include <sdk/os/string.hpp>

extern "C" {
	#include "ugui_config.h"
  	#include "ugui (1).h"
};

/*
 * Fill this section in with some information about your app.
 * All fields are optional - so if you don't need one, take it out.
 */
APP_NAME("Physium Formulae: Physics solver")
APP_DESCRIPTION("Bare physics solver. Will be updated. Press [EXE] for unpause.")
APP_AUTHOR("Guest-11111111")
APP_VERSION("1.0.0")

void UPD(){
	UG_Update();
	LCD_Refresh();
}

double getCommandInput(){
	char num[13]; //the command line
	int pos = 1; //the position of the cursor in num
	String_Strcpy(num,">_          ");

	struct InputEvent event;
	while (true){
		Debug_Printf(0,43,false,0,"%s",num); UPD();
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
									Debug_SetCursorPosition(0, 0);
									Debug_PrintString("ERROR! RESTART!", 0);
									UPD();
									return 0;
								}else{ 
									break;
									num[1]='.';
									return 0.0; //Return 0.0 if the user inputs a dot at the start.
								}
							}break;
						case KEYCODE_KEYBOARD: 
							UPD();
							Debug_PrintString("ERROR! ", 0);
							return 0;
						case KEYCODE_SHIFT: 
							return 0;
					}
				}//pos!<=8
				if (pos>1){ //If there are chars you can delete one.
					if(event.data.key.keyCode==KEYCODE_BACKSPACE){
						num[pos--]=' ';num[pos]='_';
					}//keycode!=Backspace
				}//pos!>1
				if(event.data.key.keyCode==KEYCODE_POWER_CLEAR){
					return 0;
				}//!Clear
				if(event.data.key.keyCode==KEYCODE_EXE){
					while(num[1]!='_'&&num[1]!='.'){
						double ret = num[1]-'0';
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
			return 0;
		}//EVENT_TOUCH
	}//while (true)
}

void cls(){
	LCD_ClearScreen();
}

char* doubleToString(double value, char* buffer, int precision = 1000000000) {
    // Basic implementation for positive numbers and limited precision
    long long intPart = static_cast<long long>(value);
    double fracPart = value - intPart;

    int i = 0;
    // Convert integer part
    if (intPart == 0) {
        buffer[i++] = '0';
    } else {
        // Reverse digits
        char temp[20]; // Temporary buffer for digits
        int k = 0;
        while (intPart > 0) {
            temp[k++] = (intPart % 10) + '0';
            intPart /= 10;
        }
        while (k > 0) {
            buffer[i++] = temp[--k];
        }
    }

    // Add decimal point and fractional part (simplified)
    if (precision > 0) {
        buffer[i++] = '.';
        for (int p = 0; p < precision; ++p) {
            fracPart *= 10;
            int digit = static_cast<int>(fracPart);
            buffer[i++] = digit + '0';
            fracPart -= digit;
        }
    }
    buffer[i] = '\0'; // Null-terminate the string
    return buffer;
}

void UGWrapper(UG_S16 x, UG_S16 y, UG_COLOR color) {
	setPixel(x, y, color);
}
void guiInit(UG_GUI* gui,UG_S16 width, UG_S16 height) {
	UG_Init(gui, nullptr, width, height);
}



#define MAX_OBJECTS 10

UG_GUI gui;
UG_S16 x = 320; // Width of the screen
UG_S16 y = 520; // Height of the screen

void ProgInit(){
	guiInit(&gui, x,y);
	calcInit();
}

int main() {		
		ProgInit();
  		fillScreen(color(31,64,31));
  		UPD();
  		Debug_SetCursorPosition(264,160);
		Debug_PrintString("Physium Formulae",0);
		Debug_SetCursorPosition(263, 160);
		Debug_PrintString("ClassPad",0);
		UPD();
		while(true){
    		uint32_t key1, key2;    // First create variables
    		getKey(&key1, &key2);    // then read the keys
    		if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
    		    break;
    		}else if(testKey(key1,key2, KEY_CLEAR)){
				break;
			};
		}
		fillScreen(color(31,64,31));
		UPD();
		Debug_SetCursorPosition(0,160);
  		Debug_PrintString("Physium Formulae-ClassPad", 0);
		Debug_SetCursorPosition(6,1);
		Debug_PrintString("[1] Solver",0);
		Debug_SetCursorPosition(6,1);
		Debug_PrintString("[2] Formulas",0);
		Debug_SetCursorPosition(6,2);
		Debug_PrintString("[3] Exit",0);
		UPD();
		uint32_t Menukey, MenKey;
		getKey(&Menukey, &MenKey);
		if(Menukey == KEY_1){
			fillScreen(color(31,63,31));
			UPD();
			Debug_SetCursorPosition(1,0);
      		Debug_PrintString("Physium Formulae-ClassPad", 0);
			uint32_t k1, k2;
			getKey(&k1, &k2);
			UG_PutString(1,30,"Main Solver Menu");
			UG_PutString(1,47,"[1] GPE  GPE = m*g*h");
			UG_PutString(1,64,"[2] Force F = m*a ");
			UG_PutString(1,81,"[3] Fg = m*g");
			UG_PutString(1,98,"[4] WIP-Acceleration a = F/m");
			Debug_SetCursorPosition(6,4);
			Debug_PrintString("[5] WIP-DO NOT USE",0);
			UPD();
			uint32_t SMenukey;
			uint32_t Skey;
			getKey(&SMenukey, &Skey);
			UPD();
			if(SMenukey == KEY_1){
      			Debug_SetCursorPosition(0,160);
      			Debug_PrintString("Physium Formulae-ClassPad", 0);
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
				UPD();
				uint32_t GPEKey;
				uint32_t ConfGPE;
				getKey(&GPEKey, &ConfGPE);
				UPD();
				if(GPEKey == KEY_1){
					UG_PutString(160,264,"Mass?");
					UPD();
					double m = getCommandInput();
					cls();
					UG_PutString(0,264,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
					UPD();
					double g = getCommandInput();
					cls();
					UG_PutString(160,264,"Height?");
					UPD();
					double h = getCommandInput();
					double GPE = g*m*h;
					cls();
					char* GPEAns = nullptr;
					UG_PutString(160,150, "GPE = ");
					UG_PutString(160, 264, doubleToString(GPE,GPEAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
							break;
						}
					}
				}else if(GPEKey == KEY_2){
        			Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"GPE=?");
					UPD();
					double GPE = getCommandInput();
        			cls();
	        		Debug_SetCursorPosition(0,160);
    	    		Debug_PrintString("Physium Formulae-ClassPad", 0);
	        		UG_PutString(160,264,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
    	    		UPD();
        			double g = getCommandInput();
        			cls();
        			Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae-ClassPad", 0);
        			UG_PutString(160,264,"Height=?");
        			UPD();
        			double h = getCommandInput();
        			cls();
        			Debug_SetCursorPosition(0,160);
	        		Debug_PrintString("Physium Formulae-ClassPad", 0);
    	    		UG_PutString(160,264,"Mass =");
					double m = (GPE /(g*h));
					char* Mass = nullptr;
					UG_PutString(160,264,doubleToString(m,Mass));
					UPD();
					while(true){
    	  				uint32_t key1, key2;    // First create variables
      					getKey(&key1, &key2);    // then read the keys
      					break;
	    			};
				}else if(GPEKey == KEY_3){
        			Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae-ClassPad", 0);
        			UG_PutString(160,264,"GPE = ?");
					UPD();
					double GPE = getCommandInput();
					cls();
					Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae-ClassPad", 0);
        			UG_PutString(160,264,"Mass = ?");
					UPD();
					double Mass = getCommandInput();
					cls();
					Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae-ClassPad", 0);
        			UG_PutString(160,264,"Height = ?");
					UPD();
					double Height = getCommandInput();
					cls();
					double g = GPE / (Mass * Height);
					char* gAns = nullptr;
					UG_PutString(160,264,"Acceleration to Gravity =");
					UG_PutString(160,298,doubleToString(g,gAns));
					UPD();
					while(true){
    	  				uint32_t key1, key2;    // First create variables
      					getKey(&key1, &key2);    // then read the keys
						break;
	    			};
				}else if(GPEKey == KEY_4){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"GPE = ?");
					UPD();
					double GPE = getCommandInput();
					cls();
					UG_PutString(160,264,"Mass = ?");
					UPD();
					double Mass = getCommandInput();
					cls();
					UG_PutString(160,264,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
					UPD();
					double g = getCommandInput();
					cls();
					double Height = GPE / (Mass * g);
					char* HeightAns = nullptr;
					UG_PutString(160,264,"Height =");
					UG_PutString(160,298,doubleToString(Height,HeightAns));
					UPD();
					while(true){
		  				uint32_t key1, key2;    // First create variables
	  					getKey(&key1, &key2);
						break; // Break the loop to exit the program
	    			};
				}
		
			} else if(SMenukey == KEY_2){
				Debug_SetCursorPosition(0,160);
				Debug_PrintString("Physium Formulae-ClassPad", 0);
				Debug_SetCursorPosition(6,0);
				Debug_PrintString("Force Solver Submenu",0);
				Debug_SetCursorPosition(6,1);
				Debug_PrintString("[1] Force",0);
				Debug_SetCursorPosition(6,2);
				Debug_PrintString("[2] Mass",0);
				Debug_SetCursorPosition(6,3);
				Debug_PrintString("[3] Acceleration",0);
				UPD();
				uint32_t ForceKey;
				uint32_t ConfForce;
				getKey(&ForceKey, &ConfForce);
				UPD();
				if(ForceKey == KEY_1){
					UG_PutString(160,264,"Mass?");
					UPD();
					double m = getCommandInput();
					cls();
					UG_PutString(160,264,"Acceleration?");
					UPD();
					double a = getCommandInput();
					double F = m * a;
					cls();
					char* ForceAns = nullptr;
					UG_PutString(160,150,"Force = ");
					UG_PutString(160,264,doubleToString(F,ForceAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
							break;
						}
					}
				}else if(ForceKey == KEY_2){

					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Force=?");
					UPD();
					double F = getCommandInput();
					cls();
	        		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae-ClassPad", 0);
	        		UG_PutString(160,264,"Acceleration?");
		    		UPD();
					double a = getCommandInput();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Mass =");
					double m = F / a;
					char* MassAns = nullptr;
					UG_PutString(160,264,doubleToString(m,MassAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					};
				} else if(ForceKey == KEY_3){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Force = ?");
					UPD();
					double F = getCommandInput();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Mass = ?");
					UPD();
					double m = getCommandInput();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Acceleration =");
					double a = F / m;
					char* AccelAns = nullptr;
					UG_PutString(160,264,doubleToString(a,AccelAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					};
				}
			} else if(SMenukey == KEY_3){
				Debug_SetCursorPosition(0,0);
				Debug_PrintString("Physium Formulae-ClassPad", 0);
				UG_PutString(2,264,"Force of Gravity Solver Submenu");
				UG_PutString(2,281,"[1] Force of Gravity Fg");
				UG_PutString(2,298,"[2] Mass");
				UG_PutString(2,315,"[3] Acceleration to Gravity");
				UPD();
				uint32_t FgKey;
				uint32_t ConfFg;
				getKey(&FgKey, &ConfFg);
				if(FgKey == KEY_1){
					cls();
					UG_PutString(160,264,"Mass?");
					UPD();
					double m = getCommandInput();
					cls();
					UG_PutString(160,264,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
					UPD();
					double g = getCommandInput();
					double Fg = m * g;
					cls();
					char* FgAns = nullptr;
					UG_PutString(160,150,"Force of Gravity = ");
					UG_PutString(160,264,doubleToString(Fg,FgAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
							break;
						}
					}
				} else if(FgKey == KEY_2){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Force of Gravity=?");
					UPD();
					double Fg = getCommandInput();
					cls();
	        		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae-ClassPad", 0);
	        		UG_PutString(160,264,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
		    		UPD();
					double g = getCommandInput();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Mass =");
					double m = Fg / g;
					char* MassFgAns = nullptr;
					UG_PutString(160,264,doubleToString(m,MassFgAns));
					UPD();
					while(true){
		  				uint32_t key1, key2;    // First create variables
	  					getKey(&key1, &key2);    // then read the
					}
				} else if(FgKey == KEY_3){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Force of Gravity = ?");
					UPD();
					double Fg = getCommandInput();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Mass = ?");
					UPD();
					double m = getCommandInput();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae-ClassPad", 0);
					UG_PutString(160,264,"Acceleration to Gravity =");
					double g = Fg / m;
					char* AccelFgAns = nullptr;
					UG_PutString(160,264,doubleToString(g,AccelFgAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}
			}
		} else if (Menukey == KEY_2){
			cls();
	    	Debug_SetCursorPosition(0,160);
    		Debug_PrintString("Physium Formulae-ClassPad", 0);
    		Debug_SetCursorPosition(160,0);
			Debug_PrintString("Formulas",0);
			UG_PutString(0,264,"WIP");
			UG_PutString(160,40,"GPE = mass * accel. to grav. * height");
			UG_PutString(160,80,"F = Mass * Acceleration");
			UPD();
			while(true){
				uint32_t key1, key2;    // First create variables
	  			getKey(&key1, &key2);
				break;
			};
		}else if (Menukey == KEY_3){
    		Debug_SetCursorPosition(0,160);
    		Debug_PrintString("Physium Formulae-ClassPad", 0);
    		Debug_SetCursorPosition(264,160);
    		Debug_PrintString("Program Terminating...",0);
    		UPD();
			while(true){
				break;
			}
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

		UPD();
		cls();
		return 0;
		calcEnd();
}