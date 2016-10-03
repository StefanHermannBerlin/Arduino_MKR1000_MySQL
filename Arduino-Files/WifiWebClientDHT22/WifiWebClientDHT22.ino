#include <SPI.h>                                           // Library for SPI communication included
#include <WiFi101.h>                                       // Library for WIFI module included
#include <DHT.h>                                           // Library for DHT (DHT22/RHT03 Temperature and Humidity) module included

#define DHTPIN 4                                           // Connection pin for the DHT
#define DHTTYPE DHT22                                      // Defining type of the DHT module : DHT 22 equals RHT03
DHT dht(DHTPIN, DHTTYPE);                                  // Creation of the DHT object

char ssid[] = "Wlan_Name";                                 // your network SSID (name)
char pass[] = "Wlan_Passwort";                             // your network password (use for WPA, or use as key for WEP)

float humidity, temperature;                               // Global variable to store humidity and temperature information
int status = WL_IDLE_STATUS;                               // This variable stores the Wifi status
char server[] = "www.meineURL.de";                         // name address for your web space (without path)

WiFiClient client;                                         // Initialize the Ethernet client library

/* *** *** *** *** *** *** *** *** *** *** *** *** *** ***  SETUP  *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** */
void setup() {
  dht.begin();                                             // Start the DHT object
  Serial.begin(9600);                                      // Initialize serial and wait for port to open:
  
  if (WiFi.status() == WL_NO_SHIELD) {                     // check for the presence of the shield:
    Serial.println("WiFi shield not present");
    while (true);                                          // don't continue: Stop everything
  }

  while (status != WL_CONNECTED) {                         // attempt to connect to Wifi network:
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);                                  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    countdownDelay(5);                                     // Wait a certain time to get the connection established

  }
  Serial.println("Connected to wifi");                     // Status output
  printWifiStatus();                                       // Status output
}

/* *** *** *** *** *** *** *** *** *** *** *** *** *** ***  sendData  *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** */
void sendData(){
 readDHT();                                                // Read data from DHT sensor

    Serial.println("\nStarting connection to server...");  // Status output
    if (client.connect(server, 80)) {                      // if you get a connection, report back via serial:
    Serial.println("connected to server");                 // Status output
    
    client.print("GET /iot/writeData.php?value1=");        // HTTP request  call certain url and send data using GET
    client.print(temperature);                             // HTTP request  send temperature
    client.print("&value2=");                              // HTTP request  
    client.print(humidity);                                // HTTP request  send humidity
    client.println(" HTTP/1.1");
    client.println("Host: www.meineURL.de");               // HTTP request  Host to connect to
    client.println("Connection: close");                   // HTTP request  close connection 
    client.println();                                      // HTTP request  clear
    
    client.println("Connection: close");                   // HTTP request  close connection 
    client.println();                                      // HTTP request  clear
  }  
}

/* *** *** *** *** *** *** *** *** *** *** *** *** *** ***  readDHT  *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** */
void readDHT() {
  humidity = dht.readHumidity();                           // Read data of DHT and store to variable
  temperature = dht.readTemperature();                     // Read data of DHT and store to variable

  if (isnan(humidity) || isnan(temperature)) {             // Check if any reads failed and exit early (to try again).
    Serial.println("Failed to read from DHT sensor!");     // Status output
    return;
  }
}

/* *** *** *** *** *** *** *** *** *** *** *** *** *** ***  countdownDelay  *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** */
void countdownDelay(int theTime){
    for (int i=theTime; i>0; i--){                        // Waits for a given time (in seconds) and outputs a countdown
      Serial.print(i);Serial.print(" ");                  // Output
      delay(1000);                                        // Wait one second
    }  
    Serial.println("");                                   // Clear
}

/* *** *** *** *** *** *** *** *** *** *** *** *** *** ***  LOOP  *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** */
void loop() {
  while (client.available()) {                            // if there are incoming bytes available
    char c = client.read();                               // from the server, read them and print them:
    Serial.write(c);
  }
  Serial.println("");

  if (!client.connected()) {                              // if the server's disconnected, stop the client:
    Serial.println("disconnecting from server.");         // Status output
    client.stop();                                        // stop client
    
    countdownDelay(5);                                     // wait, then start over
    sendData();                                            // sends the HTTP request
  }
}

/* *** *** *** *** *** *** *** *** *** *** *** *** *** ***  printWifiStatus  *** *** *** *** *** *** *** *** *** *** *** *** *** *** *** */
void printWifiStatus() {
  Serial.print("SSID: ");                                  // print the SSID of the network you're attached to:
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();                           // print your WiFi shield's IP address:
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();                                 // print the received signal strength:
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}





