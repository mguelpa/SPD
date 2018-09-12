#include <LiquidCrystal.h>

// Defines del estado del sistema
#define IDLE 0x00
#define TEMPSETTING 0x01

// Defines de la última tecla presionada
#define NOKEY 0x00
#define SELECT 0x01
#define LEFT 0x02
#define DOWN 0x03
#define UP 0x04
#define RIGHT 0x05

 
// Variables
int tempOut, programTemp;

//char stateMachine, key;
typedef struct s_status{
    char machineState;
    char lastKeyPressed;
    char fanCondition;
};
s_status status;

// funciones
void lcdManager(int currentTemp, int programmedTemp);
char kbdManager();

// objetos
LiquidCrystal myLcd(8,9,4,5,6,7);


void setup()
{
  myLcd.begin(16,2);
  Serial.begin(9600);
  programTemp = 0; // en el inicio no tiene 
                   // temperatura programada
                   
  status.machineState = IDLE; // la máquina arranca 
                              // en estado cero.
                              
  tempOut = map(analogRead(A1),20,358,-40,125); // leo la temperatura del sensor 
                                                // y la mapeo como entero
  lcdManager(tempOut,programTemp);
}

void loop()
{
    tempOut = map(analogRead(A1),20,358,-40,125);
    status.lastKeyPressed = kbdManager();
    lcdManager(tempOut,programTemp);
    
    switch (status.machineState)
    {  
      case IDLE:
      {      
        if(status.lastKeyPressed == SELECT)
            status.machineState = TEMPSETTING;
          break;
      }
      
      case TEMPSETTING:
      {
        if(status.lastKeyPressed == UP && programTemp < 120)
            programTemp++;
        if(status.lastKeyPressed == DOWN && programTemp > -40)
            programTemp--;
        if(status.lastKeyPressed == SELECT)
            status.machineState = IDLE;
        break;
      }
      
      default:
      {
        break;
      }
  }
}

void lcdManager(int currentTemp, int programmedTemp)
{
  myLcd.setCursor(0,0);
  myLcd.print("Temp.Actual: ");
  myLcd.print(currentTemp);
  myLcd.print("    ");
  myLcd.setCursor(0,1);
  myLcd.print ("Temp Obj:    ");
  myLcd.print(programmedTemp);
  myLcd.print("    ");
}

char kbdManager(){

  int kbdPressed = analogRead(A0);
    if(kbdPressed > 900)
      return NOKEY; 
    
    if(kbdPressed > 620)
        return SELECT; 
    
    if(kbdPressed > 400)
        return LEFT; 
    
    if(kbdPressed > 250)
        return DOWN; 
    
    if(kbdPressed > 70)
        return UP; 
    
    return RIGHT;     
}
