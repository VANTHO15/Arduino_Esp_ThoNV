
#include <FirebaseArduino.h>



void setup() 
{
 WiFi.disconnect();
 WiFi.begin("Vantho15","12345678");
 while(WiFi.waitForConnectResult()!=WL_CONNECTED)
 {
  delay(200);
 }
Firebase.begin("esp8266-36c06.firebaseio.com");
}

void loop()
{
   Firebase.setFloat("number", 42.0);

}
