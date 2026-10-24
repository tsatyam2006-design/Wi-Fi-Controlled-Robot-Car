// Pin definitions for Motor Driver 1


#define ENA1   14           // Enable/speed motors Right (Driver 1)
#define ENB1   12           // Enable/speed motors Left (Driver 1)
#define IN_1_1 15           // Driver 1 in1 motors Right
#define IN_2_1 13           // Driver 1 in2 motors Right
#define IN_3_1 2            // Driver 1 in3 motors Left
#define IN_4_1 5            // Driver 1 in4 motors Left

// Pin definitions for Motor Driver 2

#define ENA2   27           // Enable/speed motors Right (Driver 2)
#define ENB2   26           // Enable/speed motors Left (Driver 2)
#define IN_1_2 25           // Driver 2 in1 motors Right
#define IN_2_2 33           // Driver 2 in2 motors Right
#define IN_3_2 32           // Driver 2 in3 motors Left
#define IN_4_2 4            // Driver 2 in4 motors Left

#include <WiFi.h>
#include <WebServer.h>

String command;            // String to store app command state.
int speedCar = 500;         // Speed range: 0 - 255.
int speed_Coeff = 3;

const char* ssid = "Slog";    // SSID Name
const char* password = "slog@123";   // Password
WebServer server(80);

void setup() {
  // Setup pins for Driver 1
  pinMode(ENA1, OUTPUT);
  pinMode(ENB1, OUTPUT);
  pinMode(IN_1_1, OUTPUT);
  pinMode(IN_2_1, OUTPUT);
  pinMode(IN_3_1, OUTPUT);
  pinMode(IN_4_1, OUTPUT);

  // Setup pins for Driver 2
  pinMode(ENA2, OUTPUT);
  pinMode(ENB2, OUTPUT);
  pinMode(IN_1_2, OUTPUT);
  pinMode(IN_2_2, OUTPUT);
  pinMode(IN_3_2, OUTPUT);
  pinMode(IN_4_2, OUTPUT);

  Serial.begin(115200);

  // Connecting WiFi
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Starting WEB-server
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void controlMotors(int in1, int in2, int en, int speed, bool forward) {
  digitalWrite(in1, !forward);
  digitalWrite(in2, forward);
  analogWrite(en, speed);
}

// Movement functions
void goAhead() {
  controlMotors(IN_1_1, IN_2_1, ENA1, speedCar, true);
  controlMotors(IN_3_1, IN_4_1, ENB1, speedCar, true);

  controlMotors(IN_1_2, IN_2_2, ENA2, speedCar, true);
  controlMotors(IN_3_2, IN_4_2, ENB2, speedCar, true);
}

void goBack() {
  controlMotors(IN_1_1, IN_2_1, ENA1, speedCar, false);
  controlMotors(IN_3_1, IN_4_1, ENB1, speedCar, false);

  controlMotors(IN_1_2, IN_2_2, ENA2, speedCar, false);
  controlMotors(IN_3_2, IN_4_2, ENB2, speedCar, false);
}

void goRight() {
  controlMotors(IN_1_1, IN_2_1, ENA1, speedCar, false);
  controlMotors(IN_3_1, IN_4_1, ENB1, speedCar, true);

  controlMotors(IN_1_2, IN_2_2, ENA2, speedCar, false);
  controlMotors(IN_3_2, IN_4_2, ENB2, speedCar, true);
}

void goLeft() {
  controlMotors(IN_1_1, IN_2_1, ENA1, speedCar, true);
  controlMotors(IN_3_1, IN_4_1, ENB1, speedCar, false);

  controlMotors(IN_1_2, IN_2_2, ENA2, speedCar, true);
  controlMotors(IN_3_2, IN_4_2, ENB2, speedCar, false);
}

void stopRobot() {
  controlMotors(IN_1_1, IN_2_1, ENA1, 0, true);
  controlMotors(IN_3_1, IN_4_1, ENB1, 0, true);

  controlMotors(IN_1_2, IN_2_2, ENA2, 0, true);
  controlMotors(IN_3_2, IN_4_2, ENB2, 0, true);
}

void loop() {
  server.handleClient();

  command = server.arg("State");
  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "0") speedCar = 40;
  else if (command == "1") speedCar = 60;
  else if (command == "2") speedCar = 80;
  else if (command == "S") stopRobot();
}

void HTTP_handleRoot() {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}
