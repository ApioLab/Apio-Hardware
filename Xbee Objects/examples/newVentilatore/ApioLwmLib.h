/*
libreria che contiene funzioni e variabili per l'utilizzo del Light Weight Mesh
in APIO
*/



/*---------------------dichiarazioni costanti-----------------------------*/

#define INDIRIZZO_COORDINATORE  1

/*---------------------dichiarazioni variabili-----------------------------*/

int ack;


/*---------------------dichiarazioni funzioni-----------------------------*/
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
static void LwmSerialOutput(String daInviare) {
  divide_string(daInviare);
  char daInviare_char[100]; //serve perche l attributo data di message che non funziona con con un puntatore a String
  daInviare.toCharArray(daInviare_char, 100);
  int16_t indirizzo = stringDEC_To_uint16_t(dispositivo);
  
  
  NWK_DataReq_t *message = (NWK_DataReq_t*)malloc(sizeof(NWK_DataReq_t));
  message->dstAddr = indirizzo; //indirizzo dell'oggetto
  message->dstEndpoint = 1; 
  message->srcEndpoint = 1;
  message->options = NWK_OPT_ACK_REQUEST; //richiedo un ack
  message->data = (uint8_t*)(daInviare_char);
  message->size = strlen(daInviare_char);
  message->confirm = appDataConf; //callback per la gestione della conferma (campo opzioni)
                                  //e verifica dell'ack richiesto qui sopra
  NWK_DataReq(message); //invio messaggio
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//per ricevere un pacchetto com lwm
static bool LwmSerialInput(NWK_DataInd_t *ind) 
{ 
  
  int message_size=ind->size;
  String Buffer;
  for(int i=0; i<message_size; i++)
  {
    //Buffer[i] = ind->data[i];
    Buffer += ind->data[i];
  }
  //Buffer += '\0'; da verificare se la stringa inviata contiene già il 'fine riga'
  
       
  divide_string(Buffer); //utilizza le variabili dispositivo1 proprieta1 valore1
  
  RX_has_arrived = true; //dice allo sketch del coordinatore che è arrivato qualcosa
                         //(non è molto elegante metterlo qui forse)

  
  return true;
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//la usano gli oggetti per comunicare col coordinatore
void Lwm_to_coordinator(String daInviare)

{
  char daInviare_char[100]; //serve perche l attributo data di message che non funziona con con un puntatore a String
  daInviare.toCharArray(daInviare_char, 100);
  int16_t indirizzo = INDIRIZZO_COORDINATORE; //1 è l'indirizzo del coordinatore
  
  
  NWK_DataReq_t *message = (NWK_DataReq_t*)malloc(sizeof(NWK_DataReq_t));
  message->dstAddr = indirizzo; //indirizzo dell'oggetto
  message->dstEndpoint = 1; 
  message->srcEndpoint = 1;
  message->options = NWK_OPT_ACK_REQUEST; //richiedo un ack
  message->data = (uint8_t*)(*daInviare_char);
  message->size = strlen(daInviare_char);
  message->confirm = appDataConf; //callback per la gestione della conferma (campo opzioni)
                                  //e verifica dell'ack richiesto qui sopra
  NWK_DataReq(message); //invio messaggio
}

