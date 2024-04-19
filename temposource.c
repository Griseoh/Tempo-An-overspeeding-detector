#include <ESP8266WiFi.h>                 
#include <FirebaseArduino.h>      

 
#define FIREBASE_HOST "******.firebaseio.com"      
#define FIREBASE_AUTH "*************"            
#define WIFI_SSID "*****"                                  
#define WIFI_PASSWORD "******"  

int sen1=A0;
int sen2=A3;
int ledPin=9;
unsigned   long t1=0;
unsigned long t2=0; 
float velocity;
float velocity_real;
float   timeFirst;
float timeScnd;
float diff;
float speedConst=7.5;  //in cm.
          
                                                    
 
void   setup()
{
  Serial.begin(115200);
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase
 
  pinMode(sen1,INPUT);
  pinMode(sen2,INPUT);
   analogWrite(11,LOW);
  analogWrite(10,HIGH);
}
  void loop()
  {
     if (analogRead(sen1)<500 && analogRead(sen2)>500)
    {
      timeFirst   = millis();
      digitalWrite(ledPin, LOW);
      delay(30);
    }
   
  if (analogRead(sen2)>500 && analogRead(sen1)<500)
  {
    timeScnd =   millis();
    diff = timeScnd - timeFirst; 
    velocity = speedConst / diff;
     velocity_real = (velocity*360)/100;     //milliseconds to hours and centimetres to kilometeres.
    delay(30);
    digitalWrite(ledPin, HIGH);
  Serial.print("\
   the velocity is : ");
  Serial.println(velocity_real);
  Serial.print("   km/hr. ");
  delay(500);
  digitalWrite(ledPin,LOW);
  delay(500);
  Firebase.pushString("velocity", velocity_real);            //setup path to send Humidity readings
          //setup path to send Temperature readings
    if (Firebase.failed()) 
    {
 
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
  }
   }
 
  }
