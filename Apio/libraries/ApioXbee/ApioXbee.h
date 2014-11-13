/*
library containing variables in general and useful functions
*/

/*-----------------------constants definition -------------------------------*/
#define ARRAY_LENGTH 20
#define MAX_PAYLOAD_XBEE 89
#define COORDINATOR_ADDRESS_XBEE 0x0000000
/*---------------------variables definition-----------------------------*/

String deviceAddr;
String property; // variabili che sono da processare nel loop in corso
String value;  // variabili che sono da processare nel loop in corso
//String content; //contiene tutta la stringa: deviceAddr+property1+value1+...+propertyn+valuen
String propertyArray[ARRAY_LENGTH];
String valueArray[ARRAY_LENGTH];
int numberkey=0;
int j=0;

//dati ricevuti


bool TX_has_gone; 
bool RX_has_arrived;

int flag=1; //flag which manages the logic of the select
int x=0;//is used to keep track the current property value in the loop

XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse(); //for the packet in reception
ZBTxRequest zbTx = ZBTxRequest(); 
ZBTxStatusResponse txStatus = ZBTxStatusResponse(); // for the response of xbee 

char Buffer[MAX_PAYLOAD_XBEE]; //used on the function apioRecive() 


//----------------------------------------------------------------------------------------
//reception
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//This function choose property and value from propertyArray valueArray. This must be declared on every loop(Can be
//placed in input?)
void select()
{
  if(x==numberkey && flag==1)
  {
    x=0;
    for(int k=0; k<numberkey; k++)
    {
      propertyArray[k]="";
      valueArray[k]="";
    }
    numberkey=0;
    j=0;
    flag=0;
    
  }
  if(numberkey!=0)
  {
    property=propertyArray[x];
    value=valueArray[x];
    x++;
    flag=1;
    Serial.println(property+":"+value);
   
  }

}

//function that saves the pairs propiretà: value in their respective vectors or propertyArray [array_length] and valueArray [array_length]
void divide_string(String stringToSplit) {
  
  int strlen=stringToSplit.length();

  int i; //COUNTER
  deviceAddr=""; 
  for(i=0; i<strlen ; i++)
  {
    if(stringToSplit.charAt(i)=='-')
      numberkey++;

  }
  
  //-----------deviceAddr----------------  
  
  for(i=0; stringToSplit.charAt(i)!=':' && i<strlen ;i++)
  {
    deviceAddr += String(stringToSplit.charAt(i));
  }

  for(j; j<numberkey ;j++)
  {
    //-----------proprietà----------------

    for(i++; stringToSplit.charAt(i)!=':' && i<strlen ;i++)
    {
      propertyArray[j] += String(stringToSplit.charAt(i));
      
    }

    
    //-----------value----------------  
    
    for(i++; stringToSplit.charAt(i)!='-' && i<strlen ;i++)
    {
      valueArray[j] += String(stringToSplit.charAt(i)); 
    }
    
  }
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//This function receive from comunication channel(in this case XBee) launch divide string for populate propertyArry
//valueArray
void apioReceive()
{
  // 1. This will read any data that is available:
  xbee.readPacket();

  // 2. Now, to check if a packet was received: 
  if (xbee.getResponse().isAvailable()) //se è vero ho ricevuto qualcosa
  {
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) //se è vero ho ricevuto un pacchetto zb rx
    {
       xbee.getResponse().getZBRxResponse(zbRx); //riempio la classe zb rx
       /*flashLed(led, zbRx.getDataLength(), 500);*/
       for (int i = 0; i < zbRx.getDataLength(); i++) 
       {

           Buffer[i]=zbRx.getData()[i];
       }
       Serial.println(String(Buffer));
       divide_string(String(Buffer));
       //content="";
       for (int i = 0; i < MAX_PAYLOAD_XBEE; i++) 
       {

           Buffer[i]=NULL;
       }
    }
  }
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


//SEND
/*------------------------------------------------------------------------*/
//function that sends what is passed, the coordinator of the network.
void apioSend(String toSend)
{
  char toSend_char[MAX_PAYLOAD_XBEE]; //contains the string toSend (but in char type). 
  toSend.toCharArray(toSend_char, MAX_PAYLOAD_XBEE);
  XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, COORDINATOR_ADDRESS_XBEE);
  zbTx = ZBTxRequest(addr64, (uint8_t*)(toSend_char), strlen(toSend_char));
  xbee.send(zbTx);
}

//inizialization
void apioSetup()
{
  Serial.begin(9600);
  Serial.println("setup object");
  
  Serial1.begin(9600);
  xbee.setSerial(Serial1);
}


