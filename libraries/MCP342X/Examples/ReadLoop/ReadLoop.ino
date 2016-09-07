
// Include libraries this sketch will use
#include  <Wire.h>
#include  <MCP342X.h>

// Instantiate objects used in this project
MCP342X myADC1(0xD1);
MCP342X myADC2(0xD3);
MCP342X myADC3(0xD5);


void setup() {
  Wire.begin();  // join I2C bus
  TWBR = 12;  // 400 kHz (maximum)
  
  Serial.begin(9600); // Open serial connection to send info to the host
  while (!Serial) {}  // wait for Serial comms to become ready
  Serial.println("Starting up");
  Serial.println("Testing device connection...");
    Serial.println(myADC.testConnection() ? "MCP342X connection successful" : "MCP342X connection failed");
    
  myADC1.configure( MCP342X_MODE_CONTINUOUS |
                   MCP342X_CHANNEL_4 |
                   MCP342X_SIZE_18BIT |
                   MCP342X_GAIN_8X
                 );
  myADC2.configure( MCP342X_MODE_CONTINUOUS |
                   MCP342X_CHANNEL_4 |
                   MCP342X_SIZE_18BIT |
                   MCP342X_GAIN_8X
                 );
  myADC3.configure( MCP342X_MODE_CONTINUOUS |
                   MCP342X_CHANNEL_4 |
                   MCP342X_SIZE_18BIT |
                   MCP342X_GAIN_8X
                 );
  

  Serial.println(myADC.getConfigRegShdw(), HEX);
  
}  // End of setup()

void loop() {
  static int16_t  result1;
  
  myADC1.startConversion();
  myADC1.getResult(&result1);
  
  Serial.println(result1, HEX);
  
  
  static int16_t  result2;
  
  myADC2.startConversion();
  myADC2.getResult(&result2);
  
  Serial.println(result2, HEX);
  
  
  
  
  static int16_t  result3;
  
  myADC3.startConversion();
  myADC3.getResult(&result3);
  
  Serial.println(result3, HEX);
  
}  // End of loop()
