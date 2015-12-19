#include <ESP8266WiFi.h>
#include <Bounce2.h>

const char BUTTON_PIN = 0;
#define SSID "Your Wi-Fi Router SSID"
#define PASSWORD "YOUR_WIFI_PASSWORD"
#define HOST "hooks.slack.com"
#define URL "/services/AAAAAA/BBBBBB/CCCCCCCCCC"
String MESSAGE = "Someone pushed the big red button.";

Bounce button = Bounce();

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to wifi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(250);
  }

  Serial.println();
  Serial.println(WiFi.localIP());

  button.attach(BUTTON_PIN);
  button.interval(5);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  if (button.update()) { 
    if (button.fell()) {
      post();
    }
  }
}

void post() {
  Serial.println("Connecting to host...");
  WiFiClientSecure client;
  if (!client.connect(HOST, 443)) {
    Serial.println("Connection failed");
    client.stop();
    return;
  }
  Serial.println("Connected to host");

  // Send a POST request to your Slack webhook:
  // {"text": "Someone pushed the big red button."}

  String request = "";
  request += "POST ";
  request += URL;
  request += " HTTP/1.1\r\n";

  request += "Host: ";
  request += HOST;
  request += "\r\n";

  int len = MESSAGE.length() + 12;  // JSON wrapper length
  request += "Content-Length: ";
  request += len;
  request += "\r\n";

  request += "Accept: application/json\r\n";
  request += "Connection: close\r\n";
  request += "Content-Type: application/json\r\n";

  request += "\r\n";
  
  request += "{\"text\": \"";
  request += MESSAGE;
  request += "\"}";

  Serial.print(request);
  Serial.println();
  client.print(request);

  long timeout = millis() + 5000;
  while (!client.available()) {
    if (millis() > timeout) {
      Serial.println("Request timed out");
      client.stop();
      return;
    }
  }
  Serial.println("Response:");
  while (client.available()) {
    Serial.write(client.read());
  }
  Serial.println();
  Serial.println("Request complete");
}
