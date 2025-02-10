/*
 * Voice-Controlled Payload Mechanism
 * Project by Saurabh Mali and Prabhu Badkar
 * Annasaheb Dange College of Engineering & Technology
 * 
 * Description: Arduino sketch for voice-controlled payload dropping mechanism
 * Uses DFRobot Voice Recognition Module and Servo Motor
 */

#include "DFRobot_DF2301Q.h"
#include <Servo.h>

#define SERVO_PIN 9  // Servo motor connected to pin 9

// Initialize voice recognition and servo objects
DFRobot_DF2301Q_I2C asr;
Servo servo;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Attach servo to specified pin
  servo.attach(SERVO_PIN);
  
  // Initialize voice recognition module
  while (!asr.begin()) {
    Serial.println("Device connection failed");
    delay(3000);
  }
  Serial.println("Device connected successfully");
  
  // Configure voice module settings
  asr.setVolume(20);        // Set volume to 20%
  asr.setMuteMode(0);       // Disable mute mode
  asr.setWakeTime(20);      // Set wake time
}

void loop() {
  // Get command ID from voice recognition module
  uint8_t CMDID = asr.getCMDID();
  
  // Process voice commands
  if (CMDID == 5) {
    // "Catch" command - close gripper
    servo.write(90);
    Serial.println("Received command: catch");
  } else if (CMDID == 6) {
    // "Drop" command - open gripper
    servo.write(180);
    Serial.println("Received command: drop");
  } else if (CMDID != 0) {
    // Unknown command
    Serial.print("Unknown command ID: ");
    Serial.println(CMDID);
  }
  
  // Small delay to prevent overwhelming the system
  delay(300);
}
