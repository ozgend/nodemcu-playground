#include <ESP8266WiFi.h>

const char* ssid = "SSID";
const char* password = "PASSWORD"
 
int relayPin = 13;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
 
  // init wifi 
  Serial.print("--wifi-connecting--");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("--wifi-connected--");
 
  // http server start
  server.begin();
  Serial.println("--server-start--");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  
  // check if available client connection 
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // await data from client
  Serial.println("--begin-client--");
  while(!client.available()){
    delay(1);
  }
 
  // read client request path
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // process paths for relay switch
  int value = LOW;
  if (request.indexOf("/SWITCH=ON") != -1)  {
    digitalWrite(relayPin, LOW);
    value = LOW;
  }
  if (request.indexOf("/SWITCH=OFF") != -1)  {
    digitalWrite(relayPin, HIGH);
    value = HIGH;
  }
 
  // send html content
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><style>* { font-size:150%; color: #c1c1c1; background:#000000; font-family: sans-serif; } .btn { width:100%; line-height: 2; } .btn-on { background-color: #d4f7da; color: #4ea74e; } .btn-off { background-color: #ffd2d2; color: #a74e4e; } </style></head>");

  client.print("relayPin:"); 
  if(value == HIGH) {
    client.print("<b>ON</b>");
  } else {
    client.print("<b>OFF</b>");
  }
  client.println("<br><br>");
  client.println("<a href='/SWITCH=ON'><button class='btn btn-on'> ON </button></a>");
  client.println("<br><br>");
  client.println("<a href='/SWITCH=OFF'><button class='btn btn-off'> OFF </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("--end-client--");
 
}
