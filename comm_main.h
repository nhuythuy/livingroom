#include <ArduinoJson.h>


void CommMain(){
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      digitalWrite(PIN_LED, LOW);  // to show the communication only (inverted logic)
      Serial.println(".");
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("Request from client: "); Serial.println(request);
      client.flush();
      //client.println("Hi client! No, I am listening.\r"); // sends the answer to the client

      DynamicJsonDocument doc(100);
      doc["node"] = "homelivingroom";
      doc["heartbeat"] = heartbeat++;
      doc["runtime"] = runtimeMinutes;
      doc["temp"] = String(temp, 2);
      doc["humidity"] = String(humidity, 2);
      ssDoorBack = !ssDoorBack;
      doc["ssDoorBack"] = ssDoorBack;
      doc["ssDoorBackOpenMin"] = minutesDoorBackOpened++;
    
      char jsonHomeMain[100];
      serializeJson(doc, jsonHomeMain);
      client.println(String(jsonHomeMain) + "\r");
      Serial.println("Reply from server: " + String(jsonHomeMain));

      digitalWrite(PIN_LED, HIGH);
    }
    client.stop();                // tarminates the connection with the client
  }

}
