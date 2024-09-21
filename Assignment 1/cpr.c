/*--------------------------------------------------------------------------
Nom: Jonathan Domingue (CS/MATH) 
Numéro d'étudiant: 300246863 
Devoire:1
Groupe: 21

Explication de l'état zombie:
Lorsqu'un processus enfant termine, mais que son processus parent n'a pas encore lu son état de sortie (statut de terminaison), le processus enfant reste dans l'état "zombie". Cela signifie qu'il a terminé son exécution, mais son entrée dans la table des processus est toujours présente jusqu'à ce que le parent lise son état via un appel à wait() ou waitpid(). Dans notre code plus bas, le processus enfant apparaît comme un zombie jusqu'à ce que le processus parent termine ou appelle wait().

*/

#include <stdio.h>     
#include <sys/select.h>  
#include <stdlib.h>     
#include <unistd.h>    
#include <sys/types.h>  
#include <sys/wait.h>   


void creerEnfantEtLire(int prcNum);

/*-------------------------------------------------------------
Function: main
Arguments: 
    int ac    - nombre d'arguments de la commande
    char **av - tableau de pointeurs aux arguments de commande
Description:
    Extrait le nombre de processus à créer de la ligne de 
    commande. Si une erreur a lieu, le processus termine.
    Appelle creerEnfantEtLire pour créer un enfant, et lire 
    les données de l'enfant.
-------------------------------------------------------------*/
int main(int ac, char **av)
{
    int numeroProcessus;  // Variable pour stocker le nombre de processus

    if(ac == 2)  // Vérifie si exactement un argument est fourni
    {
       if(sscanf(av[1], "%d", &numeroProcessus) == 1)  // Analyse l'argument comme un entier
       {
           creerEnfantEtLire(numeroProcessus);  // Crée et lit depuis le processus enfant quon a definie plus au bas
       }
       else fprintf(stderr,"Ne peut pas traduire argument\n");  // Erreur si l'argument n'est pas un entier
    }
    else fprintf(stderr,"Arguments pas valides\n");  // Erreur si le nombre d'arguments est incorrect
    return(0);  // Retourne le succès
}

/*-------------------------------------------------------------
Function: creerEnfantEtLire
Arguments: 
    int prcNum - le numéro de processus
Description:
    Crée un processus enfant, en y passant prcNum-1. Utilise 
    prcNum comme identificateur de ce processus. Aussi lit les 
    messages du bout de lecture du tuyau et les envoie à 
    la sortie standard df1. Termine lorsque plus aucune donnée 
    ne peut être lue du tuyau, termine.
-------------------------------------------------------------*/

void creerEnfantEtLire(int prcNum)
{
    int fd[2];  // Tableau pour les descripteurs de fichiers du tuyau
    if (pipe(fd) == -1)  // Crée un tuyau quon test ensuite pour voire si echec 
    {
        perror("pipe");  // Erreur si la création du tuyau échoue
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();  // Crée un processus enfant
    if (pid == -1)  // Erreur si fork échoue
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) // Processus enfant
    {
        close(fd[0]); // Ferme lextrémité de lecture du tuyau dans l'enfant
        dup2(fd[1], STDOUT_FILENO); // Duplique l'extrémité d'écriture du tuyau vers stdout
        close(fd[1]); // Ferme l'extrémité d'écriture dupliquée

        if (prcNum > 1)
        {
            char nextNum[10];
            snprintf(nextNum, sizeof(nextNum), "%d", prcNum - 1);  // Prépare pour le prochain numéro de processus
            char *args[] = { "./cpr", nextNum, NULL };  // Prépare les arguments pour exec
            execvp(args[0], args);  // Remplace le processus enfant par le nouveau programme
            perror("execvp");  // Erreur si execvp échoue
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Processus %d commence\n", prcNum);  // Affiche le message de début
            fflush(stdout);  //écriture immédiate
            sleep(5);  // Simulate some work with the sleep for 5 seconds as requested 
            printf("Processus %d termine\n", prcNum);  // Affiche le message de fin
            fflush(stdout);  // Force l'écriture immédiate
            sleep(10);  // Simule le temps pour observer l'état zombie
            exit(0);  // Termine le processus enfant. Nous nutilisons pas kill() car on veut sassurer que le processus se termine proprement et que les tampons de sorties soient vid'es
        }
    }
    else // Processus parent
    {
        close(fd[1]); // Ferme l'extrémité d'écriture du tuyau dans le parent

        char buffer[1024];  // Tampon pour la lecture des données
        ssize_t bytesRead;

        if (prcNum > 1) {
            printf("Processus %d commence\n", prcNum);  // Affiche le message de début
            fflush(stdout);  // Force l'écriture immédiate
        }

        while ((bytesRead = read(fd[0], buffer, sizeof(buffer) - 1)) > 0)  // Lit les données du tuyau
        {
            buffer[bytesRead] = '\0';  // Ajoute le caractère de fin de chaîne
            printf("%s", buffer);  // Affiche les données sur stdout
            fflush(stdout);  // Force l'écriture immédiate
        }

        if (prcNum > 1) {
            printf("Processus %d termine\n", prcNum);  // Affiche le message de fin
            fflush(stdout);  // Force l'écriture immédiate
        }
        close(fd[0]); // Ferme l'extrémité de lecture du tuyau

        wait(NULL); // Attend que le processus enfant se termine
    }
}
