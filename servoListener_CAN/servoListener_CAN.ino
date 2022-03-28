#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);

uint8_t currentState = 0;

void setup() {
  Serial.begin(115200);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  pinMode(4, OUTPUT);
  
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");
}

void loop() {
  
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if(canMsg.can_id == 0x1E)
    {
    Serial.println("Message received from 0x1E:");
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" : ");
      for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
        Serial.print(canMsg.data[i],HEX);
      }
      Serial.println(" ");
      currentState = canMsg.data[0];
      if(currentState == 1)
      {
        Serial.println("Turning LED on");
        digitalWrite(4, HIGH);
        delay(1000);
      }
      else if(currentState == 0)
      {
        digitalWrite(4, LOW);
      }
      else
      {
        digitalWrite(4, LOW);
      }
    }
  }
}
