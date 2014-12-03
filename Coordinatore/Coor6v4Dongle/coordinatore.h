/*-----------------------definizione costanti -------------------------------*/
#define ARRAY_LENGTH 15


/*---------------------dichiarazioni variabili-----------------------------*/

//varie 
char interfaccia;//indica quale interfaccia di comunicazione si deve usare (usata su readFromWebServer)
bool TX_has_gone; //forse queste due sono da mettere e gestire nella libreria?
bool RX_has_arrived;

//dati da inviare
String dispositivo; //indirizzo della destinazione

String content; //contiene tutta la stringa: dispositivo+proprieta1+valore1+...+proprietan+valoren 
String proprietaArray[ARRAY_LENGTH];
String valoreArray[ARRAY_LENGTH];
int numberkey=0;


String dispositivo1;
String proprieta1;
String valore1;

//dati ricevuti dagli oggetti
String contentX; //contiene tutta la stringa: dispositivo+proprieta1+valore1+...+proprietan+valoren per LWM
String contentL; //contiene tutta la stringa: dispositivo+proprieta1+valore1+...+proprietan+valoren per LWM

//dichiarazioni variabili relative all' XBEE	
XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse(); //per il pacchetto in ricezione vero e proprio
ZBTxRequest zbTx = ZBTxRequest(); 
ZBTxStatusResponse txStatus = ZBTxStatusResponse(); // per la risposta dell'xbee 



//dichiarazioni variabili relative all' LWM
int ack;


/*---------------------dichiarazioni funzioni-----------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//funzione che salva le coppie (da inviare!!!) propireta valore nei rispettivi vettori ovvero proprietaArray[ARRAY_LENGTH] e valoreArray[ARRAY_LENGTH];
void divide_string_out(String stringaCompleta)  
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
  //Conta le Coppie chiave:valore da inviare
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

//Se il webServer invia qualcosa legge la stringa e restituisce il
char ReadFromWebServer()
{
  char buf=NULL;//per la lettura delle stringhe dal webserver sulla Seria1

  
    interfaccia=Serial.read();
    buf=0;
    delay(1);//c è altrimenti legge della merda sulla seriale
    buf=Serial.read();

    while(Serial.available())
    {
       content+=buf;
       buf=NULL;
       buf=Serial.read();
       delay(1);
    }
    content+=buf;
    divide_string_out(content);

  
  return interfaccia;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
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

/*-----------------------------------------------------XBEE----------------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//-----------------------------------------funzione che invia dati all'xbee-----------------

bool XBeeOutput_62(String indirizzo_str , String daInviare)
{   //per la gestrione degli errori dobbiamo decidere se ritornare un int a cui associo il tipo di errore
    //dove poi dentro SerialToWebServer decidero cosa fare a seconda del tipo di errore
 
  char daInviare_char[100]; //contiene la stringa daInviare (ma in char ). Serve perche la funzione
                            //ZBTXRequest( ) prende come secondo parametro un tipo uint8_t che è praticamente il char
  daInviare.toCharArray(daInviare_char, 100);
  
  uint32_t indirizzo = stringHEX_To_uint32_t(indirizzo_str);
  
  XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, indirizzo);//creo l indirizzo
  
  zbTx = ZBTxRequest(addr64, (uint8_t*)(daInviare_char), strlen(daInviare_char)); //compilazione della struct da inviare (strlen NON include anche '\0')
  
  xbee.send(zbTx);
  Serial.println("INVIATO");
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
      int j=0;
      String appoggio1 , appoggio2;
      //i primi proprieta valora da inviare (j=0)
      appoggio1=dispositivo+":";
      //Inserisco la prima coppia.
      appoggio2=proprietaArray[j]+":"+valoreArray[j]+"-";
      while(j<numberkey)
      {
        appoggio1+=appoggio2;
        j++;
        //aggiungo le coppie finche la lunghezza è minore o uguale di 62 oppure sono finite le coppie da aggiungere(j=numberkey)
        while( (appoggio1).length()<=62 && j<numberkey) 
        {
          
          appoggio2=proprietaArray[j]+":"+valoreArray[j]+"-";
          appoggio1+=appoggio2;
          j++;
          
         
         
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
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



/*-----------------------------------------------------LWM----------------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//callback per la gestione della conferma (accede al campo message->opzioni) e verifica dell'ack
static void appDataConf(NWK_DataReq_t *req)
{
  if (NWK_SUCCESS_STATUS == req->status)
  // frame was sent successfully
  ack=true;
  else
  // some error happened
  ack=false;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//per invirare un pacchetto com lwm
static void LwmOutput_62(String dis,String daInviare, int number) 
{
  Serial.println(daInviare);
  char daInviare_char[50]; //serve perche l attributo data di message che non funziona con con un puntatore a String
  daInviare.toCharArray(daInviare_char, 50);
  Serial.println(String(daInviare_char));
  int16_t indirizzo = stringDEC_To_uint16_t(dis);
  //da inserire inpacchettamento
  
  NWK_DataReq_t *message = (NWK_DataReq_t*)malloc(sizeof(NWK_DataReq_t));
  message->dstAddr = dis.toInt(); //indirizzo dell'oggetto
  message->dstEndpoint = 1; 
  message->srcEndpoint = 1;
  //message->options = NWK_OPT_ACK_REQUEST; //richiedo un ack
  message->size = strlen(daInviare_char);
  message->data = (uint8_t*)(daInviare_char);

  message->confirm = appDataConf; //callback per la gestione della conferma (campo opzioni)
                                  //e verifica dell'ack richiesto qui sopra
  NWK_DataReq(message); //invio messaggio
  Serial.println("ciao");
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//crea i pacchetti da inviare controllandone la lughezza 
//poi usa XbeeOutput per inviare il sigolo pacchetto
void LwmOutput()
{
      int j=0;
      String appoggio1 , appoggio2;
      while(j<numberkey)
      {
        appoggio1=dispositivo+":";
        appoggio2=proprietaArray[j]+":"+valoreArray[j]+"-";
        appoggio1+=appoggio2;

        LwmOutput_62(dispositivo , appoggio1, 1);
       
        //re-inizializzazione
        appoggio1="";
        appoggio2="";
        delay(1000);
        j++; 
      }   
  
} 


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//per ricevere un pacchetto com lwm
static bool LwmInput(NWK_DataInd_t *ind) 
{ 
  
  int message_size=ind->size;
  char bufferL[62];
  for(int i=0; i<message_size; i++)
  {
    //Buffer[i] = ind->data[i];
    bufferL[i] = ind->data[i];
  }
  Serial.println(String(bufferL));
  return true;
}


