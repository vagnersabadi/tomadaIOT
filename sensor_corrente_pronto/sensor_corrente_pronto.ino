//foi tirado de http://labdegaragem.com/forum/topics/ajuda-com-o-codigo-do-sensor-acs-712-30?commentId=6223006%3AComment%3A446072

int VQ;
int ACSPin = A0;

void setup() {
Serial.begin(9600);
VQ = determineVQ(ACSPin); //Quiscent output voltage - the average voltage ACS712 shows with no load (0 A)
delay(1000);
}

void loop() {
Serial.print("ACS712@A2:");
Serial.print(readCurrent(ACSPin),3);
Serial.println(" mA");
delay(150);
}

int determineVQ(int PIN) {
long VQ = 0;
//read 5000 samples to stabilise value
for (int i=0; i<1000; i++) {
VQ += abs(analogRead(PIN));
delay(1);//depends on sampling (on filter capacitor), can be 1/80000 (80kHz) max.
}
VQ /= 1000;
Serial.print(map(VQ, 0, 1023, 0, 5000));
Serial.println(" mV");
return int(VQ);
}

float readCurrent(int PIN) {
int current = 0;
int sensitivity = 52;//change this to 100 for ACS712-20A or to 66 for ACS712-30A
//read 5 samples to stabilise value
for (int i=0; i<200; i++) {
current += abs(analogRead(PIN) - VQ);
delay(1);
}
current = map(current/200, 0, 1023, 0, 5000);
return float(current)/sensitivity;
}
