#include <ArduinoJson.h>


void CommMain(){
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      flipLed();
      Serial.println(".");
      String request = client.readStringUntil('\n');    // receives the message from the client
      Serial.print("Request from client: "); Serial.println(request);
      client.flush();
      //client.println("Hi client! No, I am listening.\r"); // sends the answer to the client

      DynamicJsonDocument doc(100);
      doc["node"] = "homelivingroom";
      doc["runtime"] = runtimeMinutes;
      doc["temp"] = String(temp, 2);
      doc["humidity"] = String(humidity, 2);
      ssDoorBack = !ssDoorBack;
      doc["ssDoorBack"] = ssDoorBack;
      doc["ssDoorBackOpenMin"] = minutesDoorBackOpened++;
    
      char jsonHomeMain[100];
      serializeJson(doc, jsonHomeMain);
      client.println(String(jsonHomeMain) + "\n");
      Serial.println("Reply from server: " + String(jsonHomeMain));

      flipLed();
    }
    client.stop();                // tarminates the connection with the client
  }

}
