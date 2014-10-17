/*
libreria contenente le variabili generali 
e funzioni utili
*/

/*-----------------------definizione costanti -------------------------------*/
#define ARRAY_LENGTH 20


/*---------------------dichiarazioni variabili-----------------------------*/

//dati da inviare
String dispositivo;
String proprieta;
String valore;
String content; //contiene tutta la stringa: dispositivo+proprieta1+valore1+...+proprietan+valoren
String proprietaArray_out[ARRAY_LENGTH];
String valoreArray_out[ARRAY_LENGTH];
int numberkey_out=0;
int j=0;

//dati ricevuti
String dispositivo1;
String proprieta1;
String valore1;
String content1; //contiene tutta la stringa: dispositivo+proprieta+valore
String proprietaArray_in[ARRAY_LENGTH];
String valoreArray_in[ARRAY_LENGTH];
int numberkey_in=0;

bool TX_has_gone; //forse queste due sono da mettere e gestire nella libreria?
bool RX_has_arrived;

char interfaccia;//indica quale interfaccia di comunicazione si deve usare
int flag2; //flag che gestisce la logica della select
int x;//serve per tenere traccia dell'attuale chiave valore nel loop

/*---------------------dichiarazioni funzioni-----------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void select()
{
  if(numberkey_in!=0)
  {
    proprieta=proprietaArray_in[x];
    valore=valoreArray_in[x];
    x++;
    flag2=1;
    Serial.println(proprieta+":"+valore);
  }
  if(x==numberkey_in && flag2==1)
  {
    x=0;
    for(int k=0; k<numberkey_in; k++)
    {
      proprietaArray_in[k]="";
      valoreArray_in[k]="";
    }
    numberkey_in=0;
    j=0;
    flag2=0;
    
  }

}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//funzione che salva le coppie (da inviare!!!) propireta valore nei rispettivi vettori ovvero proprietaArray_out[ARRAY_LENGTH] e valoreArray_out[ARRAY_LENGTH];
void divide_string_out(String content)  
{
  
  int strlen=content.length();
  Serial.println(strlen);

  int i,j; //contatore
  numberkey_out=0;
  dispositivo="";
  for(i=0;i<ARRAY_LENGTH;i++)
  {
    proprietaArray_out[i]="";
    valoreArray_out[i]="";
  }
  
  for(i=0; i<strlen ; i++)
  {
    if(content.charAt(i)=='-')
      numberkey_out++;
  }
 Serial.println(numberkey_out);
  
  //-----------dispositivo----------------  
  
  for(i=0; content.charAt(i)!=':' && i<strlen ;i++)
  {
    dispositivo += String(content.charAt(i));
  }
  Serial.println(dispositivo);

  for(j=0; j<numberkey_out ;j++)
  {
    //-----------proprietà----------------

    for(i++; content.charAt(i)!=':' && i<strlen ;i++)
    {
      proprietaArray_out[j] += String(content.charAt(i));
    }
     Serial.println(proprietaArray_out[j]);

    
    //-----------valore----------------  
    
    for(i++; content.charAt(i)!='-' && i<strlen ;i++)
    {
      valoreArray_out[j] += String(content.charAt(i)); 
    }
    //i++;
    Serial.println(valoreArray_out[j]);
  }
  
  
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//funzione che salva le coppie (ricevute!!!) propireta valore nei rispettivi vettori ovvero proprietaArray_in[ARRAY_LENGTH] e valoreArray_in[ARRAY_LENGTH];
void divide_string_in(String content)  
{
  
  int strlen=content.length();

  int i; //contatore
  dispositivo1="";
/*  for(i=0;i<ARRAY_LENGTH;i++)
  {
    proprietaArray_in[i]="";
    valoreArray_in[i]="";
  }
*/  
  for(i=0; i<strlen ; i++)
  {
    if(content.charAt(i)=='-')
      numberkey_in++;

  }
  
  //-----------dispositivo----------------  
  
  for(i=0; content.charAt(i)!=':' && i<strlen ;i++)
  {
    dispositivo1 += String(content.charAt(i));
  }

  for(j; j<numberkey_in ;j++)
  {
    //-----------proprietà----------------

    for(i++; content.charAt(i)!=':' && i<strlen ;i++)
    {
      proprietaArray_in[j] += String(content.charAt(i));
    }

    
    //-----------valore----------------  
    
    for(i++; content.charAt(i)!='-' && i<strlen ;i++)
    {
      valoreArray_in[j] += String(content.charAt(i)); 
    }
    //i++;
  }
  
  
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//divide la stringa e la salva sulle tre stringhe dispositivo proprieta valore
//che saranno usate per inviare i messaggi
void divide_string(String content)  
{
  
  int strlen=content.length();
  int i; //contatore
  dispositivo="";
  proprieta="";
  valore="";
  
  
  
  //-----------dispositivo----------------  
    
    for(i=0; content.charAt(i)!=':' && i<strlen ;i++)
    {
      dispositivo += String(content.charAt(i));
    }
    
  
  //-----------proprietà----------------
    
    
    for(i++; content.charAt(i)!=':' && i<strlen ;i++)
    {
      proprieta += String(content.charAt(i));
    }
    
  
  //-----------valore----------------  
    
    for(i++; content.charAt(i)!=':' && i<strlen ;i++)
    {
      valore += String(content.charAt(i)); 
    }
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//divide la stringa e la salva sulle tre stringhe dispositivo1 proprieta1 valore1
//che saranno usate per ricevere i messaggi
void divide_string1(String content)  
{
  
  int strlen=content.length();
  int i; //contatore
  dispositivo1="";
  proprieta1="";
  valore1="";
  
  
  
  //-----------dispositivo----------------  
    
    for(i=0; content.charAt(i)!=':' && i<strlen ;i++)
    {
      dispositivo1 += String(content.charAt(i));
    }
    
  
  //-----------proprietà----------------
    
    
    for(i++; content.charAt(i)!=':' && i<strlen ;i++)
    {
      proprieta1 += String(content.charAt(i));
    }
    
  
  //-----------valore----------------  
    
    for(i++; content.charAt(i)!=':' && i<strlen ;i++)
    {
      valore1 += String(content.charAt(i)); 
    }
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




