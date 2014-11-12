/*-----------------------definizione costanti -------------------------------*/
#define ARRAY_LENGTH 50
#define INDIRIZZO_COORIDATORE_LWM 0
/*-----------------------definizione variabili ------------------------------*/

String content; //contiene tutta la stringa: dispositivo+proprieta1+valore1+...+proprietan+valoren 
char comando; //quale interfaccia di comunizazione utilizzare (+ altri vari comandi di controllo)

String dispositivo; //indirizzo della destinazione
String proprietaArray[ARRAY_LENGTH]; 
String valoreArray[ARRAY_LENGTH];
int numberkey=0; //numero di coppie chiave:valore

//dichiarazioni variabili relative all' LWM	
static bool nwkDataReqBusy = false;
char sendThis[109]; //se lo dichiaro locale non funziona bene

//dichiarazioni variabili relative all' XBEE	
XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse(); //per il pacchetto in ricezione vero e proprio
ZBTxRequest zbTx = ZBTxRequest(); 
ZBTxStatusResponse txStatus = ZBTxStatusResponse(); // per la risposta dell'xbee 


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//fa la potenza di due interi: mi serve perche la funzione pow aveva problemi di
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

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//trasforma una stringa fatta di soli numeri (che siboleggiano un numero in base hex) in un tipo di dato uint32_t-----------
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
    
    }
    
    
    if(buf[i]>='A'  && buf[i]<='F') //se il carattere è una lettera maiuscola valida -valore ascii compreso tra 65('A') e 70('F') - allora sottrai 'A'
    {                               //poi aggiungo 10 perchè ad esempio A in esadecimale vale 10 (in alternativa posso sottrarre '7' = 'A'-10)
    num += ( (buf[i] - 'A' + 10)*power(16,len-i-1) ); 
    
    }
    
    
    if(buf[i]>='a'  && buf[i]<='f') //se il carattere è una lettera minuscola valida -valore ascii compreso tra 97('a') e 102('f') - allora sottrai 'a'
    {                               //poi aggiungo 10 perchè ad esempio A in esadecimale vale 10 (in alternativa posso sottrarre 'W' = 'a'-10)
    num += ( (buf[i] - 'a' + 10)*power(16,len-i-1) ); 
    
    }
    
  }
  
  return num;
  
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//trasforma una stringa fatta di soli numeri in un tipo di dato uint32_t-----------
uint16_t stringDEC_To_uint16_t(String stringa) //da cambiare perche per l wm abbiamo valori decimali e non hex
{
  uint16_t num = 0;
  uint16_t numprec = 0; //serve per controllare se la variabile num va in overflow cioè num > 65535
  char buf[12];
  int len = stringa.length();
  stringa.toCharArray(buf, 12);
  int i;
  
  for(i=len-1; i>=0; i--)
  {
    //numprec=num; per verificare l'overflow
    if(buf[i]>='0'  && buf[i]<='9') //se il carattere è un numero(valore ascii compreso tra 48('0') e 57('9') ) allora sottrai '0'
    {
      num += ( (buf[i] - '0')*power(10,len-i-1) ); 
    
    }
    return num;
    
    /*if(num<numprec)  //se num va in overflow ricomincia da 0 quindi sarà minore del suo valore al ciclo precedente
    {
      return NULL; 
    }*/
  }
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//funzione che salva le coppie (da inviare!!!) propireta valore nei rispettivi vettori ovvero proprietaArray[ARRAY_LENGTH] e valoreArray[ARRAY_LENGTH];
void divide_string(String stringaCompleta)  
{
  
  int strlen=stringaCompleta.length();


  int i,j; //contatore
  numberkey=0;
  dispositivo="";
  //Svuota i vettori
  for(i=0;i<ARRAY_LENGTH;i++)
  {
    proprietaArray[i]="";
    valoreArray[i]="";
  }
  //Conta le Coppie (chiave:valore) da inviare
  for(i=0; i<strlen ; i++)
  {
    if(stringaCompleta.charAt(i)=='-')
      numberkey++;
  }
  
  //-----------dispositivo----------------  
  
  for(i=0; stringaCompleta.charAt(i)!=':' && i<strlen ;i++)
  {
    dispositivo += String(stringaCompleta.charAt(i));
  }

 //Cicla questo per tutte le chiavi e valori
  for(j=0; j<numberkey ;j++)
  {
    //-----------proprietà----------------

    for(i++; stringaCompleta.charAt(i)!=':' && i<strlen ;i++)
    {
      proprietaArray[j] += String(stringaCompleta.charAt(i));
    }
    
    //-----------valore----------------  
    
    for(i++; stringaCompleta.charAt(i)!='-' && i<strlen ;i++)
    {
      valoreArray[j] += String(stringaCompleta.charAt(i)); 
    }

    //i++;
  }
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
char ReadFromWebServer()
{
  //Serial.println("readfrom");
  char interfaccia=NULL;
  delay(1); //serve altrimenti ogni tanto si perde il primo carattere da leggere!!!
  interfaccia = Serial.read();
  delay(1);
  while (Serial.available())
  {
    char buf = Serial.read();
    delay(1);
    content += buf;
    delay(1);
  }
  Serial.println(content);

  divide_string(content);
  return interfaccia;
}
/*-----------------------------------------------------LWM----------------------------------*/

/***********************************************************************/
/*+++++++++++++++++++++++++++++++++++XBEE++++++++++++++++++++++++++++++*/
/***********************************************************************/


//-----------------------------------------funzione che invia dati all'xbee-----------------

bool XBeeOutput_62(String indirizzo_str , String daInviare)
{   //per la gestrione degli errori dobbiamo decidere se ritornare un int a cui associo il tipo di errore
    //dove poi dentro SerialToWebServer decidero cosa fare a seconda del tipo di errore
 
  Serial.println(daInviare);
  char daInviare_char[100]; //contiene la stringa daInviare (ma in char ). Serve perche la funzione
                            //ZBTXRequest( ) prende come secondo parametro un tipo uint8_t che è praticamente il char
  daInviare.toCharArray(daInviare_char, 100);
  
  uint32_t indirizzo = stringHEX_To_uint32_t(indirizzo_str);
  
  XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, indirizzo);//creo l indirizzo
  
  zbTx = ZBTxRequest(addr64, (uint8_t*)(daInviare_char), strlen(daInviare_char)); //compilazione della struct da inviare (strlen NON include anche '\0')
  
  xbee.send(zbTx);
  
  // after sending a tx request, we expect a status response
  // wait up to half second for the status response
  if (xbee.readPacket(500)) 
  {
    // got a response!

    // should be a znet tx status            	
    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) 
    {
      xbee.getResponse().getZBTxStatusResponse(txStatus);
            // get the delivery status, the fifth byte
      if (txStatus.getDeliveryStatus() == SUCCESS) 
      {
        // success.  time to celebrate
        //flashLed(statusLed, 5, 50);
        return true;
      } 
      else 
      {
        // the remote XBee did not receive our packet. is it powered on?
        //flashLed(errorLed, 3, 500);
        return false;

      }
    }
    else if (xbee.getResponse().isError()) 
       {
         //nss.print("Error reading packet.  Error code: ");  
         //nss.println(xbee.getResponse().getErrorCode());
         return false;
       } 
       else 
       {
          // local XBee did not provide a timely TX Status Response -- should not happen
          //flashLed(errorLed, 2, 50);
          return false;
       }
  }
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//crea i pacchetti da inviare controllandone la lughezza 
//poi usa XbeeOutput per inviare il sigolo pacchetto
void XBeeOutput()
{
     //Serial.println("XbeeOutput");//debug

      int j=0;
      
      String appoggio1 , appoggio2;
      //i primi proprieta valora da inviare (j=0)
      appoggio1=dispositivo+":";
      //Inserisco la prima coppia.
      appoggio2=proprietaArray[j]+":"+valoreArray[j]+"-";
      //Serial.print("numberkey: ");//debug
      //Serial.println(numberkey);//debug

      while(j<numberkey)
      {

        //aggiungo le coppie finche la lunghezza è minore o uguale di 62 oppure sono finite le coppie da aggiungere(j=numberkey)
        while( (appoggio1+appoggio2).length()<=62 && j<numberkey) 
        {
          j++;
          appoggio1+=appoggio2;
          appoggio2=proprietaArray[j]+":"+valoreArray[j]+"-";
          //Serial.println(appoggio1);
        }
        
        //invio effettivo 
        XBeeOutput_62(dispositivo , appoggio1);
       
        //re-inizializzazione
        appoggio1=dispositivo+":";
        appoggio2="";
                      
      }          
} 

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool XBeeInput()
{
  // 1. This will read any data that is available:
  xbee.readPacket();

  // 2. Now, to check if a packet was received: 
  if (xbee.getResponse().isAvailable()) //se è vero ho ricevuto qualcosa
  {
    char bufferX[62];
    String receivedX;
    if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) //se è vero ho ricevuto un pacchetto zb rx
    {
       xbee.getResponse().getZBRxResponse(zbRx); //riempio la classe zb rx
       /*flashLed(led, zbRx.getDataLength(), 500);*/
       for (int i = 0; i < zbRx.getDataLength(); i++) 
       {
           /*buffer[i] = char*/
           bufferX[i]=zbRx.getData()[i];
           receivedX+=bufferX[i];
       }
       Serial.println(receivedX);
       receivedX="";
       for (int i = 0; i < zbRx.getDataLength(); i++) 
       {
           /*buffer[i] = char*/
           bufferX[i]=NULL;
       }
       return true;
     }
  }
}


void ApioCoordinatorSetup()
{ 
  //setup Xbee
  Serial.begin(9600);//per la comunicazione con l xbee
  xbee.setSerial(Serial);
}
