#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 4   // Número de frames (páginas físicas en memoria)
#define NUM_PAGES 10   // Número total de páginas virtuales

// Estructura para un frame de página en memoria física
typedef struct Frame {
    int page;           
    bool valid;         
    int frequency;      
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
        frame->frequency = 0; 
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

// Función para insertar un frame al frente de la lista (más recientemente usado)
void insertFrame(FrameList *frameList, Frame *frame) {
    if (frameList->head == NULL) {
        frameList->head = frame;
        frameList->tail = frame;
    } else {
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
            current->frequency++;  
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Función para encontrar el frame con la menor frecuencia (LFU)
Frame* findLFUFrame(FrameList *frameList) {
    Frame *current = frameList->head;
    Frame *lfuFrame = current;
    while (current != NULL) {
        if (current->frequency < lfuFrame->frequency) {
            lfuFrame = current;
        }
        current = current->next;
    }
    return lfuFrame;
}

// Función para simular la carga de una página a memoria física utilizando LFU
void loadPage(FrameList *frameList, int page) {
    Frame *frame = findFrame(frameList, page);
    if (frame != NULL) {

        return;
    }
    
    frame = createFrame();
    frame->page = page;
    frame->valid = true;
    frame->frequency = 1; 

    // Si la lista de frames ya está llena, eliminar el frame LFU
    if (frameList->numFrames == NUM_FRAMES) {
        Frame *lfuFrame = findLFUFrame(frameList);
        removeFrame(frameList, lfuFrame);
    }

    insertFrame(frameList, frame);
}

// Función para imprimir el estado actual de la lista de frames (solo para fines de depuración)
void printFrameList(FrameList *frameList) {
    printf("Estado actual de la lista de frames:\n");
    Frame *current = frameList->head;
    while (current != NULL) {
        printf("Página: %d, Frecuencia: %d, ", current->page, current->frequency);
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

    // Simular la carga de varias páginas a memoria física
    loadPage(frameList, 1);
    loadPage(frameList, 2);
    loadPage(frameList, 3);
    loadPage(frameList, 4);
    printFrameList(frameList);  
    loadPage(frameList, 5);
    printFrameList(frameList); 
    loadPage(frameList, 2);
    printFrameList(frameList);  

    // Liberar la memoria utilizada por la lista de frames
    free(frameList);

    return 0;
}