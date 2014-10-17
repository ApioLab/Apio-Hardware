/*---------------------dichiarazioni costanti-----------------------------*/

#define INDIRIZZO_COORDINATORE  1
#define ARRAY_LENGTH 20
#define INDIRIZZO_OGGETTO  3

/*---------------------dichiarazioni variabili-----------------------------*/

String dispositivo;
String proprieta; // variabili che sono da processare nel loop in corso
String valore;  // variabili che sono da processare nel loop in corso
//String content; //contiene tutta la stringa: dispositivo+proprieta1+valore1+...+proprietan+valoren
String proprietaArray[ARRAY_LENGTH];
String valoreArray[ARRAY_LENGTH];
int numberkey=0;
int j=0;

int ack;
bool TX_has_gone; //forse queste due sono da mettere e gestire nella libreria?
bool RX_has_arrived;

int flag; //flag che gestisce la logica della select
int x=0;//serve per tenere traccia dell'attuale chiave valore nel loop

/*---------------------dichiarazioni funzioni-----------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//funzione che salva le coppie propireta valore nei rispettivi vettori ovvero proprietaArray[ARRAY_LENGTH] 
//e valoreArray[ARRAY_LENGTH];

void divide_string(String striga_da_dividere) {
  
  int strlen=striga_da_dividere.length();

  int i; //contatore
  dispositivo=""; 
  for(i=0; i<strlen ; i++)
  {
    if(striga_da_dividere.charAt(i)=='-')
      numberkey++;

  }
  Serial1.println(numberkey);
  //-----------dispositivo----------------  
  
  for(i=0; striga_da_dividere.charAt(i)!=':' && i<strlen ;i++)
  {
    dispositivo += String(striga_da_dividere.charAt(i));
  }

  for(j; j<numberkey ;j++)
  {
    //-----------proprietà----------------

    for(i++; striga_da_dividere.charAt(i)!=':' && i<strlen ;i++)
    {
      proprietaArray[j] += String(striga_da_dividere.charAt(i));
    }

    
    //-----------valore----------------  
    
    for(i++; striga_da_dividere.charAt(i)!='-' && i<strlen ;i++)
    {
      valoreArray[j] += String(striga_da_dividere.charAt(i)); 
    }
    
  }
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//callback per la gestione della conferma (accede al campo message->opzioni) e verifica dell'ack
//deve avere questo prototipo (vedi documentazione LWM)!!!!! 
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
//This function choose property and value from propertyArray valueArray. This must be declared on every loop(Can be
//placed in input?)
void select()
{

  if(x==numberkey && flag==1)
  {
    x=0;
    for(int k=0; k<numberkey; k++)
    {
      proprietaArray[k]="";
      valoreArray[k]="";
    }
    numberkey=0;
    j=0;
    flag=0;
    
  }
  if(numberkey!=0)
  {
    proprieta=proprietaArray[x];
    valore=valoreArray[x];
    x++;
    flag=1;
    Serial1.println(proprieta+":"+valore);
  }

}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//per ricevere un pacchetto com lwm
static bool apioReceive(NWK_DataInd_t *ind) 
{ 
  int message_size=ind->size;
  int i;
  char Buffer[100];
  String receivedL="";
  for(i=0; i<message_size; i++)
  {
    Buffer[i] = ind->data[i];
  }
  Serial1.println(String(Buffer));
  divide_string(String(Buffer)); //utilizza le variabili dispositivo1 proprieta1 valore1
  for(int i=0; i<100; i++)
  {
    Buffer[i]=NULL;
  }
  return true; //la documentazione dice che è cosi
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//la usano gli oggetti per comunicare col coordinatore
void apioSend(String daInviare)

{
  char daInviare_char[100]; //serve perche l attributo data di message che non funziona con con un puntatore a String
  daInviare.toCharArray(daInviare_char, 100);
  int16_t indirizzo = INDIRIZZO_COORDINATORE; //1 è l'indirizzo del coordinatore
  
  
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
void apioSetup()
{
  delay(1000);
  SYS_Init();
  NWK_SetAddr(INDIRIZZO_OGGETTO);
  NWK_SetPanId(0x01);
  PHY_SetChannel(0x1a);
  PHY_SetRxState(true);
  NWK_OpenEndpoint(1, apioReceive);

}

