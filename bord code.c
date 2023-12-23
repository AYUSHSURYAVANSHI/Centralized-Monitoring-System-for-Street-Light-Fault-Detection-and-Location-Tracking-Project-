// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "Redmi 12 5G";
const char* password = "SATI25ayush";

int ldrStatus = 0;
const int ldrPin = A0; 
// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";

// Assign output variables to GPIO pins
const int output5 = 5;
const int output4 = 4;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            int ldrStatus = analogRead(ldrPin);
//    client.println("<p>LDR Value: " + String(ldrStatus) + "</p>");

//    int ledState = digitalRead(output5); // Assuming output5 is connected to the LED
//    client.println("<p>LED State: " + (ledState == HIGH ? "ON" : "OFF") + "</p>");
//

//     if (ldrStatus >= 900) {
//      client.println("<p>LDR Status: DARK</p>");
//    } else {
//      client.println("<p>LDR Status: LIGHT</p>");
//    }
    
    if (ldrStatus >= 900) {
      Serial.println("LDR is DARK, LED is OFF");
    } 
    else {
      Serial.println("LDR is LIGHT, LED is ON");
    }

    
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
client.println("<!DOCTYPE html>\n");
client.println("<html lang=\"en\" class=\"js-focus-visible\">\n");
client.println("\n");
client.println("<title>Web Page Update Demo</title>\n");
client.println("\n");
client.println("  <style>\n");
client.println("*{\n");



client.println("margin: 0;\n");
client.println("padding: 0;\n");
client.println("}\n");
client.println("\n");
client.println("html{\n");
client.println("    scroll-behavior: smooth;\n");
client.println("}\n");
client.println("\n");
client.println("\n");
client.println("\n");
client.println("    table {\n");
client.println("      position: relative;\n");
client.println("      /* width:100%; */\n");
client.println("      border-spacing: 0px;\n");
client.println("    }\n");
client.println("    tr {\n");
client.println("      border: 1px solid white;\n");
client.println("      font-family: \"Verdana\", \"Arial\", sans-serif;\n");
client.println("      font-size: 20px;\n");
client.println("    }\n");
client.println("    th {\n");
client.println("      height: 20px;\n");
client.println("      padding: 3px 15px;\n");
client.println("      background-color: #343a40;\n");
client.println("      color: #FFFFFF !important;\n");
client.println("      }\n");
client.println("    td {\n");
client.println("      height: 20px;\n");
client.println("       padding: 3px 15px;\n");
client.println("    }\n");
client.println("    .tabledata {\n");
client.println("      font-size: 24px;\n");
client.println("      position: relative;\n");
client.println("      padding-left: 20px;\n");
client.println("      padding-top: 7px;\n");
client.println("      padding-bottom:13px;\n");
client.println("      height:30px;\n");
client.println("      border-radius: 5px;\n");
client.println("      color: black;\n");
client.println("      line-height: 20px;\n");
client.println("      /* transition: all 200ms ease-in-out; */\n");
client.println("      background-color: #00AA00;\n");
client.println("    }\n");
client.println("    \n");
client.println("    .fanrpmslider {\n");
client.println("      width: 30%;\n");
client.println("      height: 55px;\n");
client.println("      outline: none;\n");
client.println("      height: 25px;\n");
client.println("      background-color: red;\n");
client.println("    }\n");
client.println("    .bodytext {\n");
client.println("      font-family: \"Verdana\", \"Arial\", sans-serif;\n");
client.println("      font-size: 24px;\n");
client.println("      text-align: left;\n");
client.println("      font-weight: light;\n");
client.println("      border-radius: 5px;\n");
client.println("      display:inline;\n");
client.println("    }\n");
client.println("    .navbar {\n");
client.println("      width: 100%;\n");
client.println("      height: 50px;\n");
client.println("      margin: 0;\n");
client.println("      padding: 10px 0px;\n");
client.println("      background-color: #FFF;\n");
client.println("      color: #000000;\n");
client.println("      border-bottom: 5px solid #293578;\n");
client.println("    .fixed-top {\n");
client.println("      position: fixed;\n");
client.println("      top: 0;\n");
client.println("      right: 0;\n");
client.println("      left: 0;\n");
client.println("      z-index: 1030;\n");
client.println("    }\n");
client.println("    .navtitle {\n");
client.println("      float: left;\n");
client.println("      height: 50px;\n");
client.println("      font-family: \"Verdana\", \"Arial\", sans-serif;\n");
client.println("      font-size: 50px;\n");
client.println("      font-weight: bold;\n");
client.println("      line-height: 50px;\n");
client.println("      padding-left: 20px;\n");
client.println("    }\n");
client.println("   .navheading {\n");
client.println("     position: fixed;\n");
client.println("     left: 60%;\n");
client.println("     height: 50px;\n");
client.println("     font-family: \"Verdana\", \"Arial\", sans-serif;\n");
client.println("     font-size: 20px;\n");
client.println("     font-weight: bold;\n");
client.println("     line-height: 20px;\n");
client.println("     padding-right: 20px;\n");
client.println("   }\n");
client.println("   .navdata {\n");
client.println("      justify-content: flex-end;\n");
client.println("      position: fixed;\n");
client.println("      left: 70%;\n");
client.println("      height: 50px;\n");
client.println("      font-family: \"Verdana\", \"Arial\", sans-serif;\n");
client.println("      font-size: 20px;\n");
client.println("      font-weight: bold;\n");
client.println("      line-height: 20px;\n");
client.println("      padding-right: 20px;\n");
client.println("   }\n");
client.println("    .category {\n");
client.println("      font-family: \"Verdana\", \"Arial\", sans-serif;\n");
client.println("      font-weight: bold;\n");
client.println("      font-size: 32px;\n");
client.println("      line-height: 50px;\n");
client.println("      padding: 20px 10px 0px 10px;\n");
client.println("      color: #000000;\n");
client.println("    }\n");
client.println("    .heading {\n");
client.println("      font-family: \"Verdana\", \"Arial\", sans-serif;\n");
client.println("      font-weight: normal;\n");
client.println("      font-size: 28px;\n");
client.println("      text-align: left;\n");
client.println("    }\n");
client.println("  \n");
client.println("    .btn {\n");
client.println("      background-color: #444444;\n");
client.println("      border: none;\n");
client.println("      color: white;\n");
client.println("      padding: 10px 20px;\n");
client.println("      text-align: center;\n");
client.println("      text-decoration: none;\n");
client.println("      display: inline-block;\n");
client.println("      font-size: 16px;\n");
client.println("      margin: 4px 2px;\n");
client.println("      cursor: pointer;\n");
client.println("    }\n");
client.println("    .foot {\n");
client.println("      font-family: \"Verdana\", \"Arial\", sans-serif;\n");
client.println("      font-size: 20px;\n");
client.println("      position: relative;\n");
client.println("      height:   30px;\n");
client.println("      text-align: center;   \n");
client.println("      color: #AAAAAA;\n");
client.println("      line-height: 20px;\n");
client.println("    }\n");
client.println("    .container {\n");
client.println("      max-width: 1800px;\n");
client.println("      margin: 0 auto;\n");
client.println("    }\n");
client.println("    table tr:first-child th:first-child {\n");
client.println("      border-top-left-radius: 5px;\n");
client.println("    }\n");
client.println("    table tr:first-child th:last-child {\n");
client.println("      border-top-right-radius: 5px;\n");
client.println("    }\n");
client.println("    table tr:last-child td:first-child {\n");
client.println("      border-bottom-left-radius: 5px;\n");
client.println("    }\n");
client.println("    table tr:last-child td:last-child {\n");
client.println("      border-bottom-right-radius: 5px;\n");
client.println("    }\n");
//client.println("\n");
//client.println("    /* html {font-family: Times New Roman; display: inline-block; text-align: center;} */\n");
//client.println("    h2 {font-size: 2.3rem; font-family: \"Verdana\", \"Arial\", sans-serif;}\n");
//client.println("    p {font-size: 2.0rem; text-align: center;}\n");
//client.println("    /* body {max-width: 400px; margin:0px auto; padding-bottom: 25px; position: absolute;} */\n");
//client.println("    .slider {-webkit-appearance: none; margin: 14px; width: 360px; height: 25px; \n");
//client.println("      outline: none; -webkit-transition: .2s; transition: opacity .2s;}\n");
//client.println("    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 35px; height: 35px; background:#01070a; cursor: pointer;}\n");
//client.println("    .slider::-moz-range-thumb { width: 35px; height: 35px; background: #01070a; cursor: pointer; } \n");
//client.println("    \n");
//client.println("\n");
client.println("    \n");


 client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");

client.println("    \n");
client.println("  </style>\n");
client.println("\n");
client.println("  <body style=\"background-color: #efefef\" onload=\"process()\">\n");

client.println("  \n");
client.println("    <header>\n");
client.println("      <div class=\"navbar fixed-top\">\n");
client.println("          <div class=\"container\">\n");
client.println("            <div class=\"navtitle\">Sensor Monitor</div>\n");
client.println("            <div class=\"navdata\" id = \"date\">mm/dd/yyyy</div>\n");
client.println("            <div class=\"navheading\">DATE</div><br>\n");
client.println("            <div class=\"navdata\" id = \"time\">00:00:00</div>\n");
client.println("            <div class=\"navheading\">TIME</div>\n");
client.println("            \n");
client.println("          </div>\n");
client.println("    </header>\n");
client.println("  \n");
client.println("<main class=\"container\" style=\"margin-top:0px\">\n");
//client.println("<div class=\"category\">Sensor Readings</div>\n");
client.println("      <div style=\"border-radius: 10px !important;\">\n");
client.println("      <table style=\"width:100%\">\n");
client.println("      <colgroup>\n");
client.println("        <col span=\"1\" style=\"background-color:rgb(230,230,230); width: 16%; color:#000000 ;\">\n");
client.println("        <col span=\"1\" style=\"background-color:rgb(200,200,200); width: 4%; color:#000000 ;\">\n");
client.println("        <col span=\"1\" style=\"background-color:rgb(180,180,180); width: 23%; color:#000000 ;\">\n");
client.println("        <col span=\"1\" style=\"background-color:rgb(180,180,180); width: 23%; color:#000000 ;\">\n");
client.println("      </colgroup>\n");
client.println("      <col span=\"2\"style=\"background-color:rgb(0,0,0); color:#FFFFFF\">\n");
client.println("      <col span=\"2\"style=\"background-color:rgb(0,0,0); color:#FFFFFF\">\n");
client.println("      <col span=\"2\"style=\"background-color:rgb(0,0,0); color:#FFFFFF\">\n");
client.println("      <tr>\n");
client.println("        <th colspan=\"1\"><div class=\"heading\">Pin</div></th>\n");
client.println("        <th colspan=\"1\"><div class=\"heading\">Button</div></th>\n");
client.println("        <th colspan=\"1\"><div class=\"heading\">LED Status</div></th>\n");
client.println("        <th colspan=\"1\"><div class=\"heading\">LDR</div></th>\n");
//client.println("        <th colspan=\"1\"><div class=\"heading\">Volts</div></th>\n");
client.println("      </tr>\n");
client.println("      <tr>\n");
client.println("        <td><div class=\"bodytext\">Analog pin 34</div></td>\n");
//client.println("        <td><div class=\"tabledata\" id = \"b0\"><a href=\"/ledon\\\"><button class=\"tabledata\" style=\"background-color: rgb(227, 217, 22); height: 35px; width: 95px;  border-radius: 20px; text-align: center; position: relative;\">  ON  </button></a><a href=\"/ledoff\\\"><button class=\"tabledata\" style=\"background-color: red; height: 35px; width: 95px;  border-radius: 20px; text-align: center; position: relative;\"> OFF </button></a></div></td>\n");
// client.println("<a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
if (output4State=="off"){ 
client.println("        <td><div class=\"tabledata\" id = \"b1\"><a href=\"/4/on\"><button class=\"button\">ON</button></a></div></td>\n");
//client.println("        <td><div class=\"tabledata\" id = \"b1\"><p>GPIO 4 - State " + output4State + "</p></div></td>\n");
}else {
//              client.println("<p><a href=\"/4/off\"><button class=\"tabledata button2\">OFF</button></a></p>");
            
client.println("        <td><div class=\"tabledata\" id = \"v0\"><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></div></td>\n");
 }
client.println("        <td><div class=\"tabledata\" id = \"b1\"><p>GPIO 4 - State " + output4State + "</p></div></td>\n");
     if (ldrStatus >= 900) {
      client.println("<td><div class=\"tabledata\" id = \"b1\"><p>LDR Status: DARK</p><p>LDR Value: " + String(ldrStatus) + "</p></div></td>\n");
    } else {
//      client.println("<p>LDR Status: LIGHT</p>");
      client.println("<td><div class=\"tabledata\" id = \"b1\"><p>LDR Status: LIGHT</p><p>LDR Value: " + String(ldrStatus) + "</p></div></td>\n");
    }

//   client.println("<p>LDR Value: " + String(ldrStatus) + "</p>");
client.println("      </tr>\n");
client.println("      <tr>\n");
client.println("        <td><div class=\"bodytext\">Analog pin 35</div></td>\n");
if (output5State=="off"){
//  client.println("<p>GPIO 4 - State " + output4State + "</p>");

  client.println("        <td><div class=\"tabledata\" id = \"b1\"><a href=\"/5/on\"><button class=\"button\">ON</button></a></div></td>\n");
//  client.println("        <td><div class=\"tabledata\" id = \"b1\"><p>GPIO 5 - State " + output5State + "</p></div></td>\n");
//  client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("        <td><div class=\"tabledata\" id = \"v1\"><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></div></td>\n");
//  client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
  } 
client.println("        <td><div class=\"tabledata\" id = \"b1\"><p>GPIO 5 - State " + output5State + "</p></div></td>\n");
//client.println("        <td><div class=\"tabledata\" id = \"b1\"><a href=\"/5/on\"><button class=\"button\">ON</button></a></div></td>\n");
//client.println("        <td><div class=\"tabledata\" id = \"v1\"><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></div></td>\n");
client.println("      </tr>\n");

client.println("      <tr>\n");
client.println("        <td><div class=\"bodytext\">Analog pin 35</div></td>\n");
if (output5State=="off"){
//  client.println("<p>GPIO 4 - State " + output4State + "</p>");

  client.println("        <td><div class=\"tabledata\" id = \"b1\"><a href=\"/5/on\"><button class=\"tabledata\">ON</button></a></div></td>\n");
//  client.println("        <td><div class=\"tabledata\" id = \"b1\"><p>GPIO 5 - State " + output5State + "</p></div></td>\n");
//  client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("        <td><div class=\"tabledata\" id = \"v1\"><a href=\"/5/off\"><button class=\"tabledata button2\">OFF</button></a></div></td>\n");
//  client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
  } 
    client.println("        <td><div class=\"tabledata\" id = \"b1\"><p>GPIO 5 - State " + output5State + "</p></div></td>\n");
//client.println("        <td><div class=\"tabledata\" id = \"b1\"><a href=\"/5/on\"><button class=\"button\">ON</button></a></div></td>\n");
//client.println("        <td><div class=\"tabledata\" id = \"v1\"><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></div></td>\n");
client.println("      </tr>\n");

client.println("        <tr>\n");
client.println("        <td><div class=\"bodytext\">Digital switch</div></td>\n");
client.println("        <td><div class=\"tabledata\" id = \"switch\"></div></td>\n");
client.println("      </tr>\n");
client.println("      </table>\n");
client.println("    </div>\n");
client.println("    <br>\n");
//client.println("    <div class=\"category\">Sensor Controls</div>\n");
client.println("    <br>\n");
client.println("\n");
//client.println("    <h2>Lights Brightness Control </h2>\n");
//client.println("    <p><span id=\"textslider_value\">%SLIDERVALUE%</span></p>\n");
//client.println("    <p><input type=\"range\" onchange=\"updateSliderPWM(this)\" id=\"pwmSlider\" class=\"fanrpmslider\" min=\"0\" max=\"255\" value=\"%SLIDERVALUE%\" step=\"1\" class=\"slider\"></p>\n");
//client.println("\n");
//client.println("\n");
client.println("  <script>\n");
client.println("  function updateSliderPWM(element) {\n");
client.println("    var slider_value = document.getElementById(\"pwmSlider\").value;\n");
client.println("    document.getElementById(\"textslider_value\").innerHTML = slider_value;\n");
client.println("    console.log(slider_value);\n");
client.println("    var xhr = new XMLHttpRequest();\n");
client.println("    xhr.open(\"GET\", \"/slider?value=\"+slider_value, true);\n");
client.println("    xhr.send();\n");
client.println("  }\n");
client.println("  </script>\n");
client.println("\n");
client.println("\n");
client.println("\n");
client.println("\n");
client.println("  </main>\n");
client.println("\n");
//client.println("  <footer div class=\"foot\" id = \"temp\" >ESP32 Web Page Creation and Data Update Demo</div></footer>\n");
client.println("  \n");
client.println("  </body>\n");
client.println("\n");
client.println("\n");
client.println("  <script type = \"text/javascript\">\n");
client.println("  \n");
client.println("    // global variable visible to all java functions\n");
client.println("    var xmlHttp=createXmlHttpObject();\n");
client.println("\n");
client.println("    // function to create XML object\n");
client.println("    function createXmlHttpObject(){\n");
client.println("      if(window.XMLHttpRequest){\n");
client.println("        xmlHttp=new XMLHttpRequest();\n");
client.println("      }\n");
client.println("      else{\n");
client.println("        xmlHttp=new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
client.println("      }\n");
client.println("      return xmlHttp;\n");
client.println("    }\n");
client.println("\n");
client.println("    function response(){\n");
client.println("      var message;\n");
client.println("      var barwidth;\n");
client.println("      var currentsensor;\n");
client.println("      var xmlResponse;\n");
client.println("      var xmldoc;\n");
client.println("      var dt = new Date();\n");
client.println("      var color = \"#e8e8e8\";\n");
client.println("     \n");
client.println("      // get the xml stream\n");
client.println("      xmlResponse=xmlHttp.responseXML;\n");
client.println("  \n");
client.println("      // get host date and time\n");
client.println("      document.getElementById(\"time\").innerHTML = dt.toLocaleTimeString();\n");
client.println("      document.getElementById(\"date\").innerHTML = dt.toLocaleDateString();\n");
client.println("     }\n");
client.println("\n");
client.println("    function process(){\n");
client.println("     \n");
client.println("     if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {\n");
client.println("        xmlHttp.open(\"PUT\",\"xml\",true);\n");
client.println("        xmlHttp.onreadystatechange=response;\n");
client.println("        xmlHttp.send(null);\n");
client.println("      }       \n");
client.println("        // you may have to play with this value, big pages need more porcessing time, and hence\n");
client.println("        // a longer timeout\n");
client.println("        setTimeout(\"process()\",0;100\n");
client.println("    }\n");
client.println("  \n");
client.println("  \n");
client.println("  </script>\n");
client.println("\n");
//client.println("</html>\n");
//client.println("\n");
//client.println("\n");
//client.println("\n");
//client.println("");
            // Display the HTML web page
//            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #00AA00; border: none; color: white; padding: 0px 20px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #00AA00;}</style></head>");
            
            // Web Page Heading
//            client.println("<body><h1>ESP8266 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
//            client.println("<p>GPIO 5 - State " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
//            if (output5State=="off"){
//              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
//            } else {
//              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
//            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
//            client.println("<p>GPIO 4 - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
//            if (output4State=="off"){ 
//              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
//            } else {
//              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
//            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}