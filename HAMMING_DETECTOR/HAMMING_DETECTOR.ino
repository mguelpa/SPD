#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key = 0;
int adc_key_in = 0;

//--------------------------------------------------------------------------------------------------------------
// "display.cpp"
//--------------------------------------------------------------------------------------------------------------
#define FALSE 0
#define TRUE 1

#define DISPLAY_STATE_RESET 0
#define DISPLAY_STATE_SETTED 1

#define DISPLAY_STATE_SHOW 1
#define DISPLAY_STATE_SETUP 2

#define DISPLAY_STATE_SETUP_SEG 0
#define DISPLAY_STATE_SETUP_MIN 1

#define INTERVAL_MESSAGE1 5000

#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

static int state_display = DISPLAY_STATE_RESET;
static int row, col, counter;
static unsigned long time_now = 0;
static char screen[16] = {"set value: ****"};

static int i = 0;



void setup()
{
    pinMode(A5, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(2, OUTPUT);
    

    Serial.begin(9600);
    lcd.begin(16, 2);
    row = 0;
    col = 11;
    counter = 0;

}

void loop()
{
    lcd_key = read_LCD_buttons();
    if((state_display == DISPLAY_STATE_RESET && lcd_key == btnNONE) || (state_display == DISPLAY_STATE_SETTED))
    {            
        lcd.setCursor(0, 0);
        lcd.print("press select to ");
        lcd.setCursor(0, 1);
        lcd.print("start");
    }
    else if(state_display == DISPLAY_STATE_RESET && lcd_key != btnNONE)
    {
        state_display = DISPLAY_STATE_SETUP;
        lcd.clear();

    }


    if(state_display == DISPLAY_STATE_SETUP)
    {
        display_setup_loop();
//        digitalWrite(A5, HIGH);
//        delay(150);
//        digitalWrite(A1, LOW);
//        delay(150);
//        digitalWrite(A4, HIGH);
//        delay(150);
//        digitalWrite(A1, LOW);
//        delay(150);
//        digitalWrite(A3, HIGH);
//        delay(150);
//        digitalWrite(A1, LOW);
//        delay(150);
//        digitalWrite(A2, HIGH);
//        delay(150);
//        digitalWrite(A1, LOW);
//        delay(150);
//        digitalWrite(A1, HIGH);
//        delay(150);
//        digitalWrite(A1, LOW);
//        delay(150);
//        digitalWrite(2, HIGH);
//        delay(150);
//        digitalWrite(A1, LOW);
//        delay(150);
//        digitalWrite(3, HIGH);
//        delay(150);
//        digitalWrite(A1, LOW);
//        delay(150);
    }
    
}

void display_setup_loop()
{
  
    char values[3] = {'*', '0', '1'};
    lcd_key = read_LCD_buttons();

    

  
    switch (lcd_key)
    {        
        case btnRIGHT:  
            if(millis() > time_now + 500)
            {
              if(col < 14)
                col++; 
              i=0;   
              time_now = millis();
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("set value: ****");
              lcd.setCursor(col, 1);
              lcd.print("^");
            }
            break;

        case btnLEFT:
            if(millis() > time_now + 500)
            {
              time_now = millis();
              if(col > 11)
                col--;
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("set value: ****");
              lcd.setCursor(0, 1);
              lcd.setCursor(col, 1);
              lcd.print("^");

            }
            break;

        case btnUP:
            if(millis() > time_now + 500)
            {
              if(i<2)
                i++;
              time_now = millis(); 
              lcd.setCursor(col, 0);
              lcd.print(values[i]);
              screen[col] = values[i];
            }            
            break;

        case btnDOWN:
            if(millis() > time_now + 500)
            {
              if(i>1)
                i--;
              time_now = millis(); 
              lcd.setCursor(col, 0);
              lcd.print(values[i]);
              screen[col] = values[i];
            }            
            break;

        case btnNONE:
            lcd.setCursor(0, 0);
            lcd.print(screen);
            lcd.setCursor(col, 1);
            lcd.print("^");
            break;
        
        case btnSELECT:
        if(millis() > time_now + 500)
        {
            time_now = millis();
            if(screen[11] != '*' && screen[12] != '*' && screen[13] != '*' && screen[14] != '*')
            {
                state_display = DISPLAY_STATE_SETTED;
                lcd.clear();
            }
        }
        break;
    }
}

int read_LCD_buttons()
{
    adc_key_in = analogRead(0);
     
    if (adc_key_in > 1000)
        return btnNONE;
        
    if (adc_key_in < 50)
        return btnRIGHT;
        
    if (adc_key_in < 195)
        return btnUP;
        
    if (adc_key_in < 380)
        return btnDOWN;
        
    if (adc_key_in < 555)
        return btnLEFT;
        
    if (adc_key_in < 790)
        return btnSELECT;
        
    return btnNONE;
}
