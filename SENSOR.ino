

/* Comment this out to disable prints and save space */
//#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define FLAME 12
 int f;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = " 795c33746e204fb28a4241bc079193a6";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Irfan";
char pass[] = "asim1234";

#define DHTPIN 2          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void Flamesensor()
{
 
  int fire = digitalRead(FLAME);// read FLAME sensor
  if ( fire == HIGH)
  { f = 1;
     } else {
    f = 0;
     }
}
double Light (int RawADC0)
{
  double Vout = RawADC0 * 0.0048828125;
  int lux = 500 / (10 * ((5 - Vout) / Vout)); //use this equation if the LDR is in the upper part of the divider
  //int lux=(2500/Vout-500)/10;
  return lux;
}
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
   float hic = dht.computeHeatIndex(t, h, false);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Flamesensor();
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V4, hic);
  Blynk.virtualWrite(V2, int(Light(analogRead(0))));
   Blynk.virtualWrite(V3, f);
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
pinMode(FLAME, INPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(600000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
