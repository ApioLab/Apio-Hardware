struct struttura {
	String temperatura;
        int flag;
	struttura* succ;
};
typedef struttura* list;

//Lista è il nome della struttura che immagazzina tutti i dati
list lista=0;

void insert_new(String value)
{
	list q, r;
	r = new struttura;
	r->temperatura= value;
        r->flag=0;
    Serial.setTimeout(100);
    r->succ=0;
	q=lista;
	while(q->succ!=0)
	{
		q=q->succ;
	}
	if (lista==0) lista=r;
	else q->succ=r;
    Serial.println("OK");
} 
	
void print_list()
{
	list q;
	q=lista;
	while(q!=0)
	{
		Serial.println(q->temperatura);
		q=q->succ;
	}
}

void elimina(String value){
  list q, p=0;
  q=lista;
  while(q!=0){
        p=q;
	if (value==q->temperatura)
	{
            p->succ=q->succ;
            delete q;
            if (p==lista) lista=0;
            Serial.println("Eliminato");
	}
        q=q->succ;
  }
}

int esiste(String value){
	list q;
	q=lista;
	while(q!=0){
		if (value==q->temperatura){
			return 1;
		}
		q=q->succ;
	}
	return 0;
}

void controlla(int temp){
        Serial.print(temp);
	list q;
	q=lista;
	while(q!=0){
                //Serial.print(q->flag);
		String temperatura=q->temperatura;
		if (temperatura.toInt()-0.5 <= temp && temperatura.toInt()+0.5 >= temp && q->flag!=temp){
                        //Stampa sulla seriale verso gli oggetti le condizioni
			//Dopo mandali anche al coordinatore
			Serial.println("aggiorna");
                        q->flag=temp;
                        q=q->succ;
		} else if (q->flag==temp) {
                       q=q->succ;
                }
                else
                {
                  q->flag=0;
                  q=q->succ;
                }
		
	}
}
