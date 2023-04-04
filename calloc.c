#include <sys/mman.h> // Pour mmap
#include <unistd.h> // Pour sysconf
#include <string.h> // Pour memset

void* my_calloc(size_t nmemb, size_t size) {
    size_t total_size = nmemb * size; // Calcul de la taille totale nécessaire

    int pagesize = sysconf(_SC_PAGESIZE); // Obtention de la taille de page du système
    size_t num_pages = (total_size + pagesize - 1) / pagesize; // Calcul du nombre de pages nécessaires

    size_t mmap_size = num_pages * pagesize; // Calcul de la taille totale de mémoire à allouer

    void* ptr = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); // Appel à mmap pour allouer de la mémoire

    if (ptr == MAP_FAILED) { // Vérification si mmap a échoué
        return NULL; // Retourne NULL en cas d'échec
    }

    memset(ptr, 0, mmap_size); // Utilisation de memset pour initialiser la mémoire à zéro

    return ptr; // Retourne le pointeur vers le bloc de mémoire alloué
}
