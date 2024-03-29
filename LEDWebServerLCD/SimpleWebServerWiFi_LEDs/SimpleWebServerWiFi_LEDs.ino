#include <SPI.h>
#include <WiFiNINA.h>
#include <Wire.h>



#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

const int yellowLED = 2;
const int blueLED = 3;
const int whiteLED = 4;
const int redLED = 5;
const int greenLED = 6;

char signal;

void setup() {
  Serial.begin(9600);      // initialize serial communication
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event  
pinMode(redLED, OUTPUT);
pinMode(yellowLED, OUTPUT);
pinMode(greenLED, OUTPUT);
pinMode(blueLED, OUTPUT);// set the LED pin mode
pinMode(whiteLED, OUTPUT);
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            showWebPage(client);
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        performRequest(currentLine);
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void showWebPage(WiFiClient client) {
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();

  // the content of the HTTP response follows the header:
  client.println("<h1><center>Arduino Remote Control</center></h1>");

  client.print("<Center>");
  client.println("<table border=1 style='text-align:center'>");
  // Yellow LED
  client.print("<tr><td>Yellow LED</td><td>");
  if (digitalRead(yellowLED)) {
    client.print("<font style='color:green;'>ON</font>");
  } else {
    client.print("<font style='color:red;'>OFF</font>");
  }
  client.println("</td><td><a href='/yellowLED/on'>ON</a> / <a href='/yellowLED/off'>OFF</a></td></tr>");
  client.print("<br>"); 
    // Blue LED
  client.print("<tr><td>Blue LED</td><td>");
  if (digitalRead(blueLED)) {
    client.print("<font style='color:green;'>ON</font>");
  } else {
    client.print("<font style='color:red;'>OFF</font>");
  }
  client.println("</td><td><a href='/blueLED/on'>ON</a> / <a href='/blueLED/off'>OFF</a></td></tr>");
   client.print("<br>"); 
 
// White LED
  client.print("<tr><td>White LED</td><td>");
  if (digitalRead(whiteLED)) {
    client.print("<font style='color:green;'>ON</font>");
  } else {
    client.print("<font style='color:red;'>OFF</font>");
  }
  client.println("</td><td><a href='/whiteLED/on'>ON</a> / <a href='/whiteLED/off'>OFF</a></td></tr>");
   client.print("<br>"); 
 // Red LED
  client.print("<tr><td>Red LED</td><td>");
  if (digitalRead(redLED)) {
    client.print("<font style='color:green;'>ON</font>");
  } else {
    client.print("<font style='color:red;'>OFF</font>");
  }
  client.println("</td><td><a href='/redLED/on'>ON</a> / <a href='/redLED/off'>OFF</a></td></tr>");
   client.print("<br>"); 

  // Green LED
  client.print("<tr><td>Green LED</td><td>");
  if (digitalRead(greenLED)) {
    client.print("<font style='color:green;'>ON</font>");
  } else {
    client.print("<font style='color:red;'>OFF</font>");
  }
  client.print("</td><td><a href='/greenLED/on'>ON</a> / <a href='/greenLED/off'>OFF</a></td></tr>");
client.println("</table>");
client.print("</Center>");


  // The HTTP response ends with another blank line
  client.println();

  // ALL LEDS
 // client.print("<tr><td>ALL LEDS</td><td>");
  
  //client.println("</td><td><a href='/AllLED/on'>ON</a> / <a href='/AllLED/off'>OFF</a></td></tr>");

  //client.println("</table>");

  // The HTTP response ends with another blank line
  client.println();

  
}

void performRequest(String line) {
  if (line.endsWith("GET /redLED/on")) {
    digitalWrite(redLED, HIGH);
    signal = '0';
  } else if (line.endsWith("GET /redLED/off")) {
    digitalWrite(redLED, LOW);
    signal = '1';
  } else if (line.endsWith("GET /yellowLED/on")) {
    digitalWrite(yellowLED, HIGH);
    signal = '2';
  } else if (line.endsWith("GET /yellowLED/off")) {
    digitalWrite(yellowLED, LOW);
    signal = '3';
  } else if (line.endsWith("GET /greenLED/on")) {
    digitalWrite(greenLED, HIGH);
    signal = '4';
  } else if (line.endsWith("GET /greenLED/off")) {
    digitalWrite(greenLED, LOW);
    signal = '5';
  } else if (line.endsWith("GET /blueLED/on")) {
    digitalWrite(blueLED, HIGH);
    signal ='6';
  } else if (line.endsWith("GET /blueLED/off")) {
    digitalWrite(blueLED, LOW);
    signal = '7';
  } else if (line.endsWith("GET /whiteLED/on")) {
    digitalWrite(whiteLED, HIGH);
    signal = '8';
  } else if (line.endsWith("GET /whiteLED/off")) {
    digitalWrite(whiteLED, LOW);
    signal = '9';
  } else if (line.endsWith("GET /AllLED/on")) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(whiteLED, HIGH);
    digitalWrite(blueLED, HIGH);
  } else if (line.endsWith("GET /AllLED/off")) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
    digitalWrite(whiteLED, LOW);
    digitalWrite(blueLED, LOW);
  } 

}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}

void requestEvent() {
  Wire.write(signal); // respond with message of 6 bytes
  // as expected by master
}
