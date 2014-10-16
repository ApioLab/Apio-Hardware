

XBee xbee = XBee();
ZBRxResponse zbRx = ZBRxResponse(); //per il pacchetto in ricezione vero e proprio
ZBTxRequest zbTx = ZBTxRequest(); 
ZBTxStatusResponse txStatus = ZBTxStatusResponse(); // per la risposta dell'xbee 

char buffer[62]; //serve sulla funzione XbeeInput()



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//-----------------------------------------funzione che invia dati all'xbee-----------------

bool XBeeSerialOutput_62(String indirizzo_str , String daInviare)
{   //per la gestrione degli errori dobbiamo decidere se ritornare un int a cui associo il tipo di errore
    //dove poi dentro SerialToWebServer decidero cosa fare a seconda del tipo di errore
 

  char daInviare_char[62]; //contiene la stringa daInviare (ma in char ). Serve perche la funzione
                            //ZBTXRequest( ) prende come secondo parametro un tipo uint8_t che è praticamente il char
  daInviare.toCharArray(daInviare_char, 62);
  
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
//poi usa xbeeSerialOutput per inviare il sigolo pacchetto
bool XBeeSerialOutput(String daInviare)
{
      int j=0;
      divide_string_out(daInviare);
      String appoggio1 , appoggio2;
      //i primi proprieta valora da inviare (j=0)
      appoggio1=dispositivo+":";
      appoggio2=proprietaArray_out[j]+":"+valoreArray_out[j]+"-";
      while(j<numberkey_out)
      {
        //aggiungo le coppie finche la lunghezza è minore o uguale di 62 oppure sono finite le coppie da aggiungere(j=numberkey_out)
        while( (appoggio1+appoggio2).length()<=62 && j<numberkey_out) 
        {
          j++;
          appoggio1+="-"+appoggio2; //se metto i doppi apici non funziona bene (aggiunge un trattino di troppo)
          appoggio2=proprietaArray_out[j]+":"+valoreArray_out[j];
         
        }
      
        //invio effettivo 
        XBeeSerialOutput_62(dispositivo , content);
        
        //re-inizializzazione
        appoggio1=appoggio2;
        appoggio2="";
                      
      }          
      

} 
   
      
      
      
      



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
bool XBeeSerialInput()
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
           /*buffer[i] = char*/
           buffer[i]=zbRx.getData()[i];
       }
       content= String(buffer);
       divide_string_in(content);
       content="";
       for (int i = 0; i < zbRx.getDataLength(); i++) 
       {
           /*buffer[i] = char*/
           buffer[i]=NULL;
       }
       return true;

    }
    else return false;
    
  }
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//funzione che invia ciò che gli viene passato al cordinatore della rete.
void XBeeSend_to_coordinator(String daInviare)
{
  char daInviare_char[100]; //contiene la stringa daInviare (ma in char ). Serve perche la funzione
  daInviare.toCharArray(daInviare_char, 100);
  XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x00000000);
  zbTx = ZBTxRequest(addr64, (uint8_t*)(daInviare_char), strlen(daInviare_char)); //strlen NON include anche '\0'
  xbee.send(zbTx);
  
//  // after sending a tx request, we expect a status response
//  // wait up to half second for the status response
//  if (xbee.readPacket(500)) 
//  {
//    // got a response!
//
//    // should be a znet tx status            	
//    if (xbee.getResponse().getApiId() == ZB_TX_STATUS_RESPONSE) 
//    {
//      xbee.getResponse().getZBTxStatusResponse(txStatus);
//            // get the delivery status, the fifth byte
//      if (txStatus.getDeliveryStatus() == SUCCESS) 
//      {
//        // success.  time to celebrate
//        //flashLed(statusLed, 5, 50);
//      } 
//      else 
//      {
//        // the remote XBee did not receive our packet. is it powered on?
//        //flashLed(errorLed, 3, 500);
//      }
//    }
//    else if (xbee.getResponse().isError()) 
//       {
//         //nss.print("Error reading packet.  Error code: ");  
//         //nss.println(xbee.getResponse().getErrorCode());
//       } 
//       else 
//       {
//          // local XBee did not provide a timely TX Status Response -- should not happen
//          //flashLed(errorLed, 2, 50);
//       }
//  }
}
