/*---------------------dichiarazioni costanti-----------------------------*/

#define INDIRIZZO_COORDINATORE  0
#define ARRAY_LENGTH 50
#define INDIRIZZO_OGGETTO  34

/*---------------------dichiarazioni variabili-----------------------------*/

String content; //contiene tutta la stringa: dispositivo+property1+value1+...+propertyn+valuen 

String dispositivo;
String property; // variabili che sono da processare nel loop in corso
String value;  // variabili che sono da processare nel loop in corso
//String content; //contiene tutta la stringa: dispositivo+property1+value1+...+propertyn+valuen
String propertyArray[ARRAY_LENGTH];
String valueArray[ARRAY_LENGTH];
int numberkey=0;
int j=0;


char sendThis[109]; //se lo dichiaro locale non funziona bene


int flag; //flag che gestisce la logica della select
int x=0;//serve per tenere traccia dell'attuale chiave value nel loop



/*---------------------dichiarazioni funzioni-----------------------------*/

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//funzione che salva le coppie propireta value nei rispettivi vettori ovvero propertyArray[ARRAY_LENGTH] 
//e valueArray[ARRAY_LENGTH];

void divide_string(String stringa_da_dividere) {
  
  int strlen=stringa_da_dividere.length();
 
  int i; //contatore
  dispositivo=""; 
  for(i=0; i<strlen ; i++)
  {
    if(stringa_da_dividere.charAt(i)=='-')
      numberkey++;
  }
  Serial.println(numberkey);
  //-----------dispositivo----------------  
  
  for(i=0; stringa_da_dividere.charAt(i)!=':' && i<strlen ;i++)
  {
    dispositivo += String(stringa_da_dividere.charAt(i));
  }

  for(j; j<numberkey ;j++)//j non viene inizializzato perche deve tener conto anche delle coppie che sono arrivate prima
  {
    //-----------proprietà----------------

    for(i++; stringa_da_dividere.charAt(i)!=':' && i<strlen ;i++)
    {
      propertyArray[j] += String(stringa_da_dividere.charAt(i));
    }

    
    //-----------value----------------  
    
    for(i++; stringa_da_dividere.charAt(i)!='-' && i<strlen ;i++)
    {
      valueArray[j] += String(stringa_da_dividere.charAt(i)); 
    }
    Serial.println(propertyArray[j]+":"+valueArray[j]);

  }
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


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
    Serial.print("select: ");
    Serial.print(property);
    Serial.println(":"+value);
  }

}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

void apioReceive()
{
  if(Serial.available()>0)
  {
    while (Serial.available())
    {
      char buf = Serial.read();
      delayMicroseconds(100);
      content += buf;
      delayMicroseconds(100);
    }
    Serial.println(content);

    divide_string(content);    
    content="";
  }    
}

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void apioLoop(){
    apioReceive();
    select();
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void apioSetup()
{
  Serial.begin(9600);
  Serial.println("setup oggetto");

}

