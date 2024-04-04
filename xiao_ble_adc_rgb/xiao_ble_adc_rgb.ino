#include <Adafruit_TinyUSB.h> // for Serial
#include <Servo.h>

#define SERV_PORT 1


#define REF_VLT 3.3
#define REF_BIT 10

#if REF_BIT == 8
#define REF_RNG 256
#elif REF_BIT == 10
#define REF_RNG 1024
#elif REF_BIT == 12
#define REF_RNG 4096
#elif REF_BIT == 14
#define REF_RNG 16384
#endif

#define REF_KEF REF_VLT/(float)REF_RNG

int i = 0;
int ii = 0;
Servo pntr;

void setup() {
  pntr.attach(SERV_PORT);
  // Set the resolution to 12-bit (0..4095)
  Serial.begin(115200);
  Serial.println("===========");
  Serial.println(REF_BIT);
  Serial.println(REF_BIT);
  Serial.println(REF_VLT);
  Serial.println(REF_RNG);
  Serial.println(REF_KEF);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  analogReadResolution(REF_BIT); // Can be 8, 10, 12 or 14

  pinMode(1, OUTPUT);

  //  while(1){
  //  Serial.println("===========");
  //  Serial.println(REF_BIT);
  //  Serial.println(REF_VLT);
  //  Serial.println(REF_RNG);
  //  Serial.println(REF_KEF);
  //  delay(1000);
  //  }
}

uint64_t tm1 = 9;
int an = 0;
char out[64];
int pwm = 0;
int ang = 0;
void loop() {
  if (millis() - tm1 > 1000) {
    i++;
    tm1 = millis();
  }
  ii = i % 3;
//  int pwm = (i % 25) * 10;
  an = analogRead(A0);
  ang = ((float)an / (float)REF_RNG) * 180;
  pwm = ((float)an / (float)REF_RNG) * 255;

  sprintf(out, "I:%d\tA0:%d\tV:%f\tPWM:%d\tSERV:%d", i, an, an * (float)REF_KEF, pwm, ang);
  //  sprintf(out, " V:%f", (float)an / (float)REF_KEF);
  //Serial.print(i);
  Serial.println(out);
  //  delay(1000);                       // wait for a second
  pntr.write(ang);
  analogWrite(2, pwm);

  digitalWrite(LED_RED, (ii == 0) ? 0 : 1);
  digitalWrite(LED_GREEN, (ii == 1) ? 0 : 1);
  digitalWrite(LED_BLUE, (ii == 2) ? 0 : 1);
  delay(15);
}
