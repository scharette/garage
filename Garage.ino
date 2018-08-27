#include <Keypad.h>


#define BUZZER_PIN D8 

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//liste des codes possibles
char *ListeCodes[] = {"12345","9876","5558D","5555ABA", "BCA123"};
char Pincode[8];




byte rowPins[ROWS] = {D7, D6, D5,D4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {D3, D2,D1 ,D0 }; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(115200);
   pinMode(BUZZER_PIN, OUTPUT);
}
void pulseBuzzer() {
  // pulse the buzzer on for a short time
 
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  
}



int countCharacter (char *ArrayToCount)
{
  int i;
  int charcount = 0;
  for (i = 0; ArrayToCount[i]; i++)
  {
    charcount++;

  }
  return(charcount);
}


boolean IsCodeOK(char *PinCodeAvalider)
{
  //validation du code
  int x;
  byte len = (sizeof(ListeCodes) / sizeof(ListeCodes[0]) );

  for (x = 0; x <len; x++)
  {
    if (strcmp(PinCodeAvalider, ListeCodes[x]) == 0 )
    {
      // Le code est valide
      return true;
    }   
  }
      return false;
}

void loop(){
  
  char key = {keypad.getKey()};
  
if (key != NO_KEY){
  if ((key != '#') && (key != '*'))  
  {   
    char keytmp[] = {key};
    pulseBuzzer();
    if ((countCharacter(Pincode) < 8))
    {
      strcat(Pincode,keytmp);
    }
    else  
    {
      pulseBuzzer();
      pulseBuzzer();
      pulseBuzzer();
      memset(Pincode,'\0', 8);
    }
     
  }
    // Si le boutton # ou * est detecte, on envoie le code pour validation et on ouvre la porte
    else if ((key == '#') || (key == '*'))
  {
    
    if (IsCodeOK(Pincode))
    {
      // BON CODE 
      Serial.println(Pincode);
      pulseBuzzer();
      pulseBuzzer();
      pulseBuzzer();
      // log le code
      memset(Pincode,'\0', 8);

    }
    else
    {
      // Mauvais code
      pulseBuzzer();
      pulseBuzzer();      
      Serial.println("Mauvais Code");
      Serial.println(Pincode);
      memset(Pincode,'\0', 8);
    }     
  }
}
 }
  


