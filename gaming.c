#include<stdio.h>

typedef struct Echipa
{   
    char* EchipaName;
    int nrPlayers;
    Player* players;
    struct Echipa* next;
}Echipa;

typedef struct Player
{
    char* firstName;
    char* secondName;
    int points;
    struct Player* next;
}Player;
    

typedef struct Node
{
    Echipa* echipainfo;
    struct Node* next;
}Node;

int nrEchipe(FILE* file)
{
    int numarEchipe=0;
    fscanf(file,"%d", &numarEchipe);
    return numarEchipe;
}

Node* creareNode(Echipa* echipa)
{
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->echipainfo=echipa;
    newNode->next=NULL;
    return newNode;
}

void addAtBeginning(Node** head,Echipa* echipa)
{
    Node* newNode=creareNode(echipa);
    newNode->next=*head;
    *head=newNode;
}


void freeLista(Node* head)
{
    Node* nodCurent=head;
    Node* nodUrmator=NULL;

    while(nodCurent!=NULL)
    {   
        Echipa* echipa=nodCurent->echipainfo;
        Player* jucatorCurent=echipa->players;
        Player* jucatorUrmator=NULL;
        

        while(jucatorCurent!=NULL)
        {
            jucatorUrmator=jucatorCurent->next;
            free(jucatorCurent->firstName);
            free(jucatorCurent->secondName);
            free(jucatorCurent);
            jucatorCurent=jucatorUrmator;
        }

        free(echipa->EchipaName);
        free(echipa);
        nodUrmator=nodCurent->next;
        free(nodCurent);
        nodCurent=nodUrmator;
        
    }
}


//suma puncte echipa

int SumaPuncteEchipa(Echipa* echipa)
{
    int sumaPuncte=0;
    Player* jucatorCurent=echipa->players;

    while(jucatorCurent!=NULL)
    {
         sumaPuncte +=jucatorCurent->points;
         jucatorCurent=jucatorCurent->next;

    }
    return sumaPuncte;
}

//Punctaj minim
int PunctajMinim(Node* head)
{
    int punctajmin=10000;

    Node* nodCurent=head;

    while(nodCurent!=NULL)
    {
        Echipa* echipa=nodCurent->echipainfo;
        int sumaPuncte=SumaPuncteEchipa(echipa);
        if(sumaPuncte<punctajmin)
        {
            punctajmin=sumaPuncte;
        }
        nodCurent=nodCurent->next;

    }
    return punctajmin;
}

//Eliminarea echipelor
void EliminareEchipa(Node** head)
{   
    int punctajmin=PunctajMinim(*head);
    Node* nodCurent=head;
    Node* nodAnterior=NULL;

    while(nodCurent!=NULL)
    {
        Echipa* echipa=nodCurent->echipainfo;
        int sumaPuncte=SumaPuncteEchipa(echipa);

        if(sumaPuncte==punctajmin)
        {
            if(nodAnterior!=NULL)
            {
                nodAnterior->next=nodCurent->next;
                nodCurent=nodAnterior->next;

            }
            else
            {
              *head=nodCurent->next;
              nodCurent=(*head)->next;
            }
            freeLista(nodCurent);
        }
        else{
            nodAnterior=nodCurent;
            nodCurent=nodCurent->next;
        }
    }
}


void AfisareaEchipelor(Node* head)
{
    FILE* file=fopen("r.out","w");
    if(file!=NULL)
    {
    Node* current=head;

    while(current!=NULL)
    {
        Echipa* echipa=current->echipainfo;
        fprintf(file,"%s\n",echipa->EchipaName);

        current=current->next;

    }
    fclose(file);
    }
    else 
    {
        puts("NFisierul nu poate fi modificat\n");
        return 1;
    }

}
 
int main()
{
    FILE* file;
    Node* head=NULL;
    

    if((file=fopen("d.in","r"))==NULL)
    {
     puts("Fisierul nu poate sa fie deschis!\n");
     return 1;
    }
    else
    { int numarEchipe=nrEchipe(file);
      fgetc(file);
    
    for(int i=0;i<numarEchipe;i++)
    {
        Echipa* echipa=(Echipa*)malloc(sizeof(Echipa));
        echipa->next=head;
        head=echipa;

        //citirea numarului de jucatori
        fscanf(file,"%d",&echipa->nrPlayers);

        //citirea numelui echipei
        char EchipaName[100];
        fgets(EchipaName,sizeof(EchipaName),file);
        fgetc(file);


        
        echipa->players=(Player*)malloc(sizeof(Player));

        //citirea informatiilor despre si adaugarea lor in lista echipei
        Player* prevPlayer=NULL;

        for(int j=0;j<echipa->nrPlayers;j++)
        {
            Player* player=(Player*)malloc(sizeof(Player));
            player->next=prevPlayer;
            

            //citirea numelui si prenumelui jucatorului
            char playerFirstName[100];
            char playerSecondName[100];
            fscanf(file,"%s %s\n",playerFirstName,playerSecondName);

            //citirea nr de puncte ale jucatorului
            fscanf(file,"%d\n",&player->points);
            fgetc(file);
            
    
           
            player->next=NULL;
            //ADAUG PLAYER IN LISTA echipei

            if(echipa->players=NULL)
            {
                echipa->players=player;
            }
            else
            {
                Player* currentPlayer=echipa->players;
                while(currentPlayer->next!=NULL)
                {
                    currentPlayer=currentPlayer->next;
                }
                
                currentPlayer->next=player;
            }
        
        }
           
            addAtBeginning(head,echipa);

            //ignora linia dintre echipe in fisier
            fscanf(file,"\n");
    }
   int n=1;




  while(n*2<numarEchipe)
  {
    n *=2;
  }
  
  while (numarEchipe > n)
  {
    EliminareEchipa(&head);
  }
    }
//scrierea echipelor ramase in fisier
    AfisareaEchipelor(head);

    fclose(file);
    

    //eliberare memorie
    freeLista(&head);

    return 0;

}

