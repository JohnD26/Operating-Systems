/*--------------------------------------------------------------------------
Nom: Jonathan Domingue (CS/MATH) + Yasmina Baba (SEG) 
Numéro d'étudiant: 300246863 + 300298674
Devoire:3
Groupe: 21
*/



#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Définir des temps de sommeil aléatoires pour simuler le travail
#define RANDOM_SLEEP_TIME (rand() % 3 + 1)
#define RANDOM_PROGRAMMING_TIME (rand() % 5 + 1)

// Déclaration des constantes= Nombres de chaises
#define NUM_CHAIRS 3

// Déclaration des sémaphores et du mutex
sem_t students; // Sémaphore pour les étudiants en attente
sem_t taSleeping; // Sémaphore pour réveiller le TA
pthread_mutex_t chairMutex; // Mutex pour gérer l'accès aux chaises

int waitingStudents = 0; // Nombre d'étudiants en attente

// Fonction exécutée par le TA
void* ta(void* arg) {
    while (1) {
        printf("TA est endormi.\n");
        sem_wait(&students); // Attendre qu'un étudiant arrive
        printf("TA est réveillé par un étudiant.\n");

        while (1) {
            pthread_mutex_lock(&chairMutex);

            if (waitingStudents == 0) {
                pthread_mutex_unlock(&chairMutex);
                break; // Sortir de la boucle si aucun étudiant n'attend
            }

            waitingStudents--; // Réduire le nombre d'étudiants en attente
            printf("TA aide un étudiant. Étudiants en attente: %d\n", waitingStudents);

            pthread_mutex_unlock(&chairMutex);
            sem_post(&taSleeping); // Signaler que le TA est prêt à aider

            // Simuler le temps d'aide (1 à 3 secondes)
            sleep(RANDOM_SLEEP_TIME);

            printf("TA a terminé d'aider un étudiant.\n");
        }
    }
}

// Fonction exécutée par chaque étudiant
void* student(void* num) {
    int id = *(int*)num;
    while (1) {
        // Simuler le temps de programmation (1 à 5 secondes)
        sleep(RANDOM_PROGRAMMING_TIME);
        pthread_mutex_lock(&chairMutex);

        if (waitingStudents < NUM_CHAIRS) {
            waitingStudents++;
            printf("Étudiant %d attend. Étudiants en attente: %d\n", id, waitingStudents);

            sem_post(&students); // Notifier le TA qu'un étudiant attend
            pthread_mutex_unlock(&chairMutex);
            sem_wait(&taSleeping); // Attendre que le TA aide

            printf("Étudiant %d est aidé par le TA.\n", id);
        } else {
            pthread_mutex_unlock(&chairMutex);
            printf("Étudiant %d trouve toutes les chaises occupées. Reviendra plus tard.\n", id);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_students>\n", argv[0]);
        return 1;
    }

    int num_students = atoi(argv[1]);
    pthread_t taThread;
    pthread_t studentThreads[num_students];
    int studentIds[num_students];

    // Initialiser les sémaphores et le mutex
    sem_init(&students, 0, 0);
    sem_init(&taSleeping, 0, 0);
    pthread_mutex_init(&chairMutex, NULL);

    // Créer le thread du TA
    pthread_create(&taThread, NULL, ta, NULL);

    // Créer les threads des étudiants
    for (int i = 0; i < num_students; i++) {
        studentIds[i] = i + 1;
        pthread_create(&studentThreads[i], NULL, student, &studentIds[i]);
    }

    // Attendre la fin des threads des étudiants 
    for (int i = 0; i < num_students; i++) {
        pthread_join(studentThreads[i], NULL);
    }

    // Détruire les sémaphores et le mutex 
    sem_destroy(&students);
    sem_destroy(&taSleeping);
    pthread_mutex_destroy(&chairMutex);

    return 0;
}

