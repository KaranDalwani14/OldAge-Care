
#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#define FIREBASE_HOST "dukh2-49941-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "jlgmWCQ0AYga3Dh3k9M0rVg5b1mPpNBzNigfJgoc"

 
  #define Relay1 12
  int val1;
  #define Relay2 02
  int val2;
  #define Relay3 13
  int val3;
  #define Relay4 15
  int val4;
  FirebaseData fbdo;
  FirebaseData kbdo;
  FirebaseData nbdo;


  String WIFI_SSID = "Note 5";
  String WIFI_PASSWORD = "KARAN123";

    void setup()
      {
          Serial.begin(115200);
          pinMode(Relay1, OUTPUT);
          pinMode(Relay2, OUTPUT);
          pinMode(Relay3, OUTPUT);
          pinMode(Relay4, OUTPUT);
  
          digitalWrite(Relay1, LOW);
          digitalWrite(Relay2, LOW);
          digitalWrite(Relay3, LOW);
          digitalWrite(Relay4, LOW);

          WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
          Serial.print("connecting");
          delay(10000);
          while (WiFi.status() != WL_CONNECTED) 
            {
                Serial.print(".");
                delay(500);
             }
           Serial.println();
           Serial.print("connected:");
           Serial.println(WiFi.localIP());
   
               Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
               Firebase.setString(fbdo,"S1", "0");                   
               Firebase.setString(fbdo,"S2", "0");
               Firebase.setString(fbdo,"S3", "0");                   
               Firebase.setString(fbdo,"S4", "0");

             
                Firebase.setStreamCallback(fbdo, streamCallback);
                      Firebase.beginStream(fbdo, "S1");
                       Firebase.setStreamCallback(kbdo, streamCallback1);
                     Firebase.beginStream(kbdo, "S2");
                      Firebase.setStreamCallback(nbdo, streamCallback2);
                      Firebase.beginStream(nbdo, "S3");
        }

      void streamCallback(StreamData data)
      {
             val1 = data.stringData().toInt();
             Serial.println(val1);
             if (val1 == 1)
           {
               digitalWrite(Relay1, HIGH);
               Serial.println("light ON \n");
           }
          else if (val1 == 0)
           {
              digitalWrite(Relay1, LOW);
              Serial.printf("light OFF \n");
           }
        
      }
      void streamCallback1(StreamData data1)
      {
             val2 = data1.stringData().toInt();
             Serial.println(val2);
             if (val2 == 1)
            {
              digitalWrite(Relay2, HIGH);
              Serial.printf("Fan ON \n");
            }
          else if (val2 == 0)
            {
              digitalWrite(Relay2, LOW);
              Serial.printf("Fan OFF \n");
            }
        
      }
         void streamCallback2(StreamData data2)
      {
             val3 = data2.stringData().toInt();
             Serial.println(val3);
              if (val3 == 1)
            {
              digitalWrite(Relay3, HIGH);
              Serial.printf("TV ON \n");
            }
          else if (val3 == 0)
            {
              digitalWrite(Relay3, LOW);
              Serial.printf("TV OFF \n");
            }
        
      }        
    void firebasereconnect()
      {
         Serial.println("Trying to reconnect");
         Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
      }
    void loop()
      {
      }
