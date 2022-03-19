// SGS Calibration by linear interpolation for Strain 1 and Strain 2
// Apply two known loads to the Strain Gauge sensor and record the values obtained below
// You can use Strain 1 or Strain 2 or the two Strains at the same time.
#include <LiquidCrystal_I2C.h> //Include LCD module

LiquidCrystal_I2C lcd(0x27,16,2); //Initialize LCD
//I2Cアドレス0x27、16桁、2行のLCDを初期化

//Cariburation parameter
//重さ既知のおもりAとBを用いて線形の校正をおこなう。
float ReadingA_Strain1 = 8;
float LoadA_Strain1 = 1.162; // (Kg)
float ReadingB_Strain1 = 13;
float LoadB_Strain1 = 1.976; // (Kg)
int time_step = 2500 ; // reading every 2.5s
long time = 0;

void setup() {
    Serial.begin(9600); // setup serial baudrate

    lcd.init(); // initialize the lcd 
    lcd.backlight(); //turn on backlight of LCD
}

void loop() {
    
    float newReading_Strain1 = analogRead(1); // analog in 1 for Strain 1

    // Calculate load by interpolation
    float load_Strain1 = ((LoadB_Strain1 - LoadA_Strain1)/(ReadingB_Strain1 - ReadingA_Strain1)) *
    (newReading_Strain1 - ReadingA_Strain1) + LoadA_Strain1;

    // millis returns the number of milliseconds since the board started the current program
    if(millis() > time_step+time) {

        //output Serial monitor
        Serial.print("Reading_Strain1 : ");
        Serial.print(newReading_Strain1); // display strain 1 reading
        Serial.print(" Load_Strain1 : ");
        Serial.println(load_Strain1); // display strain 1 load
        Serial.println('\n');

        //output LCD
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("RAW: ");
        lcd.print(String(int(newReading_Strain1)));
        lcd.setCursor(0,1);
        lcd.print("LOAD: "+String(load_Strain1)+" kg");

        time = millis();
    }
}
