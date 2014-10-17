#define BUFFER 50

XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse();
char buffer[30];
int i;
char ch='-1';
int flag=0;
int flag2=0;
int numberKey=0;
int j=0;

String dispositivo;
String proprieta;
String valore;
String content;

String proprietaArray[BUFFER];
String valoreArray[BUFFER];

void select()
{
  if(numberKey!=0)
  {
    proprieta=proprietaArray[j];
    valore=valoreArray[j];
    j++;
    flag2=1;
  }
  if(j==numberKey && flag2==1)
  {
    j=0;
    for(int k=0; k<numberKey; k++)
    {
      proprietaArray[k]="";
      valoreArray[k]="";
    }
    numberKey=0;
    flag2=0;
    
  }

}

void divide_string(String content)  
{
  
  int strlen=content.length();
  Serial.println(strlen);
  int i; //contatore
  dispositivo=NULL;
  proprieta=NULL;
  valore=NULL;
  
  
  
  //-----------dispositivo----------------  
    Serial.print("dispositivo: ");
    for(i=0; content.charAt(i)!=':' && i<strlen ;i++)
    {
      dispositivo += String(content.charAt(i));
    }
    Serial.println(dispositivo);
  
  //-----------proprietà----------------
  while(flag==1)
  {
    Serial.print("proprieta: ");
    for(i++; content.charAt(i)!=':' && i<strlen ;i++)
    {
      proprietaArray[numberKey] += String(content.charAt(i));
    }
    Serial.println(proprietaArray[numberKey]);
  
  //-----------valore----------------  
    Serial.print("valore: ");
    for(i++; content.charAt(i)!=':' && i<strlen ;i++)
    {
      valoreArray[numberKey] += String(content.charAt(i)); 
    }
    Serial.println(valoreArray[numberKey]);
    i++;
    ch=content.charAt(i);
    Serial.print(ch);
    numberKey++;
    if(ch!='-')
    {
      flag=0;
    }
  }
  ch='1';
} 

//fa la potenza di due interi: mi serve perche la funzione pow aveva problemi di -------------
//arrotondamento (pow(10,3)=999,838...) e quando facevo un cast a intero mi
//troncava netto la virgola senza arrotondare 
uint32_t power(int base, int esp)
{
  int i;
  uint32_t result = base;
  if(esp == 0)
  {
    return 1;
  }
  for(i=1; i<esp; i++)
  {
    result *= base;
  }
  return result;
}


//trasforma una stringa fatta di soli numeri in un tipo di dato uint32_t-----------
uint32_t stringHEX_To_uint32_t(String stringa)
{
  uint32_t num = 0;
  char buf[12];
  int len = stringa.length();
  stringa.toCharArray(buf, 12);
  int i;
  
  for(i=len-1; i>=0; i--)
  {
    if(buf[i]>='0'  && buf[i]<='9') //se il carattere è un numero(valore ascii compreso tra 48('0') e 57('9') ) allora sottrai '0'
    {
    num += ( (buf[i] - '0')*power(16,len-i-1) ); 
    //Serial.println(num);
    }
    
    
    if(buf[i]>='A'  && buf[i]<='F') //se il carattere è una lettera maiuscola valida -valore ascii compreso tra 65('A') e 70('F') - allora sottrai 'A'
    {                               //poi aggiungo 10 perchè ad esempio A in esadecimale vale 10 (in alternativa posso sottrarre '7' = 'A'-10)
    num += ( (buf[i] - 'A' + 10)*power(16,len-i-1) ); 
    //Serial.println(num);
    }
    
    
    if(buf[i]>='a'  && buf[i]<='f') //se il carattere è una lettera minuscola valida -valore ascii compreso tra 97('a') e 102('f') - allora sottrai 'a'
    {                               //poi aggiungo 10 perchè ad esempio A in esadecimale vale 10 (in alternativa posso sottrarre 'W' = 'a'-10)
    num += ( (buf[i] - 'a' + 10)*power(16,len-i-1) ); 
    //Serial.println(num);
    }
    
  }
  
  
  return num;
  
  
}


//-----------------------------------------funzione che invia dati all'xbee-----------------

void XBeeSerialOutput(String daInviare){
  divide_string(daInviare);
  char daInviare_char[100]; //contiene la stringa daInviare (ma in char ). Serve perche la funzione
                            //ZBTXRequest( ) prende come secondo parametro un tipo uint8_t che è praticamente il char
  //C'è da convertire questa in logica API: FATTO
  //char daInviare1[100] = toString(daInviare);
  //int str_len = daInviare.length() + 1 ;
  daInviare.toCharArray(daInviare_char, 100);
  //Diego l'inidirizzo sarebbe meglio in esadecimale per il fatto che non lo possiamo provare per ora
  uint32_t indirizzo = stringHEX_To_uint32_t(dispositivo);
  XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, indirizzo);
  ZBTxRequest zbTx = ZBTxRequest(addr64, (uint8_t*)(daInviare_char), strlen(daInviare_char)); //strlen NON include anche '\0'
  xbee.send(zbTx);
}


void XBeeInput()
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
       for ( i = 0; i < zbRx.getDataLength(); i++) 
       {
           /*buffer[i] = char*/
           buffer[i]=zbRx.getData()[i];
       }
       content= String(buffer);
       flag=1;
       
//Devi fare la parte di funzione che divide la stringa content in dispositivo, chiave, valore
       
       divide_string(content);
       
     
    }
  }
}

//funzione che invia ciò che gli viene passato al cordinatore della rete.
void XBeeSend(String daInviare){
  char daInviare_char[100]; //contiene la stringa daInviare (ma in char ). Serve perche la funzione
  daInviare.toCharArray(daInviare_char, 100);
  XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40B3C132);
  ZBTxRequest zbTx = ZBTxRequest(addr64, (uint8_t*)(daInviare_char), strlen(daInviare_char)); //strlen NON include anche '\0'
  xbee.send(zbTx);
}
