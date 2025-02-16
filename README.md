Am facut 3 structuri: una pentru player, alta pt Echipa si una pentru nodurile listei cu informatiile despre echipa si totodata despre jucatori.
In int main() am deschis fisierul d.in, am testat mai intai daca se poate deschide sau nu.Daca fisierul s-a deschis am luat o variabila numarEchipe 
care este egala cu primul lucru citit de fisier care este pe prima linie. Apoi, in for am urmat aceeasi pasi pt toate echipele.Am citit din fisier 
numarul de jucatori si numele echipei.Apoi in alt for am citit toate informatiile despre jucatori si ii adaug in lista echipei, apoi creez nod si il
adaug la inceputul listei si dupa ignor linia dintre echipe.Apoi aflu numarul de echipe permise ca putere a lui 2 si cat timp numarEchipe> echipele 
permise elimin echipele. In functia de eliminare a echipelor se apeleaza si functia care calculeaza punctajul minim a echipelor si suma de puncte pe echipa.
Apoi scriu echipele ramase in fisierul r.out.
Inchid fisierul si eliberez memoria.
