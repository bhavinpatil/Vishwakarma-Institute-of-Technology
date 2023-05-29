#define BLYNK_TEMPLATE_ID "TMPLIrKxbfuo"
#define BLYNK_DEVICE_NAME "IOTPetFeeder"
#define BLYNK_AUTH_TOKEN "uvD6FNRnjdpJli8RtK68BxkVfDvt1Jbt"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define FEEDER_PIN 5

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "A9";
char pass[] = "HarshiA9";

Servo servo;

int should_feed = 0;

void setup()
{
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);  //PING blynk-cloud.com
    servo.attach(2); // D4
    servo.write(0);
    delay(2000);
}

void loop()
{
    Blynk.run();
    should_feed = digitalRead(FEEDER_PIN);
    if(should_feed == 1){
        servo.write(180);
    } else {
        servo.write(0);
    }
}
