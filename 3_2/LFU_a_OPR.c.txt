#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 4   // Número de frames (páginas físicas en memoria)
#define NUM_PAGES 10   // Número total de páginas virtuales

// Estructura para un frame de página en memoria física
typedef struct Frame {
    int page;        
    bool valid;         
    struct Frame *prev;
    struct Frame *next;
} Frame;

// Estructura para la lista de frames en memoria física
typedef struct FrameList {
    int numFrames;      
    Frame *head;        
    Frame *tail;        
} FrameList;

// Función para crear un nuevo frame
Frame* createFrame() {
    Frame *frame = (Frame *)malloc(sizeof(Frame));
    if (frame != NULL) {
        frame->page = -1;   
        frame->valid = false;
        frame->prev = NULL;
        frame->next = NULL;
    }
    return frame;
}

// Función para inicializar la lista de frames en memoria física
FrameList* createFrameList() {
    FrameList *frameList = (FrameList *)malloc(sizeof(FrameList));
    if (frameList != NULL) {
        frameList->numFrames = 0;
        frameList->head = NULL;
        frameList->tail = NULL;
    }
    return frameList;
}

// Función para insertar un frame al frente de la lista
void insertFrame(FrameList *frameList, Frame *frame) {
    if (frameList->head == NULL) {
        // Lista vacía
        frameList->head = frame;
        frameList->tail = frame;
    } else {
        // Insertar al frente de la lista
        frame->next = frameList->head;
        frameList->head->prev = frame;
        frameList->head = frame;
    }
    frameList->numFrames++;
}

// Función para eliminar un frame de la lista
void removeFrame(FrameList *frameList, Frame *frame) {
    if (frame->prev != NULL) {
        frame->prev->next = frame->next;
    } else {
        frameList->head = frame->next;
    }
    if (frame->next != NULL) {
        frame->next->prev = frame->prev;
    } else {
        frameList->tail = frame->prev;
    }
    frameList->numFrames--;
    free(frame);
}

// Función para buscar un frame específico por número de página
Frame* findFrame(FrameList *frameList, int page) {
    Frame *current = frameList->head;
    while (current != NULL) {
        if (current->page == page) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Función para encontrar la página óptima para reemplazar basada en futuros accesos
Frame* findOptimalFrame(FrameList *frameList, int futurePages[], int currentIndex, int futureSize) {
    Frame *current = frameList->head;
    Frame *optimalFrame = current;
    int maxDistance = -1;

    while (current != NULL) {
        int distance = futureSize;  
        for (int i = currentIndex; i < futureSize; i++) {
            if (futurePages[i] == current->page) {
                distance = i - currentIndex;
                break;
            }
        }

        if (distance > maxDistance) {
            maxDistance = distance;
            optimalFrame = current;
        }

        current = current->next;
    }

    return optimalFrame;
}

// Función para simular la carga de una página a memoria física utilizando OPR
void loadPage(FrameList *frameList, int page, int futurePages[], int currentIndex, int futureSize) {
    Frame *frame = findFrame(frameList, page);
    if (frame != NULL) {
        return;
    }

    frame = createFrame();
    frame->page = page;
    frame->valid = true;
    if (frameList->numFrames == NUM_FRAMES) {
        Frame *optimalFrame = findOptimalFrame(frameList, futurePages, currentIndex, futureSize);
        removeFrame(frameList, optimalFrame);
    }
    insertFrame(frameList, frame);
}

// Función para imprimir el estado actual de la lista de frames (solo para fines de depuración)
void printFrameList(FrameList *frameList) {
    printf("Estado actual de la lista de frames:\n");
    Frame *current = frameList->head;
    while (current != NULL) {
        printf("Página: %d, ", current->page);
        if (current->valid) {
            printf("Estado: Ocupado\n");
        } else {
            printf("Estado: Vacío\n");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    FrameList *frameList = createFrameList();
    int futurePages[] = {1, 2, 3, 4, 2, 3, 5, 1, 2, 4};
    int futureSize = sizeof(futurePages) / sizeof(futurePages[0]);

    // Simular la carga de páginas a memoria física usando OPR
    for (int i = 0; i < futureSize; i++) {
        loadPage(frameList, futurePages[i], futurePages, i, futureSize);
        printFrameList(frameList);  
    }
    free(frameList);

    return 0;
}