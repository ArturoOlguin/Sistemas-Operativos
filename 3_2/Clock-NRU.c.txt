#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 4   // Número de frames (páginas físicas en memoria)

// Estructura para un frame de página en memoria física
typedef struct Frame {
    int page;            
    bool valid;          
    bool referenceBit;  
    bool modifiedBit;   
    struct Frame *next;  // Puntero al siguiente frame (para lista circular)
} Frame;

// Estructura para la lista de frames en memoria física
typedef struct FrameList {
    int numFrames;       
    Frame *head;         
} FrameList;

// Función para crear un nuevo frame
Frame* createFrame() {
    Frame *frame = (Frame *)malloc(sizeof(Frame));
    if (frame != NULL) {
        frame->page = -1;        
        frame->valid = false;
        frame->referenceBit = false;
        frame->modifiedBit = false;
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
    }
    return frameList;
}

// Función para insertar un frame en la lista
void insertFrame(FrameList *frameList, Frame *frame) {
    if (frameList->head == NULL) {
        frameList->head = frame;
        frame->next = frame; 
    } else {
        // Insertar en la lista 
        Frame *tail = frameList->head;
        while (tail->next != frameList->head) {
            tail = tail->next;
        }
        tail->next = frame;
        frame->next = frameList->head;
    }
    frameList->numFrames++;
}

// Función para buscar un frame específico por número de página
Frame* findFrame(FrameList *frameList, int page) {
    Frame *current = frameList->head;
    if (current == NULL) return NULL;
    do {
        if (current->page == page) {
            return current;
        }
        current = current->next;
    } while (current != frameList->head);
    return NULL;
}

// Función para seleccionar y eliminar un frame de acuerdo al algoritmo NRU
Frame* selectFrame(FrameList *frameList) {
    Frame *current = frameList->head;
    Frame *target = NULL;
    
    do {
        // Seleccionar el primer frame que sea de Clase 0 o 1
        if (!current->referenceBit) {
            target = current;
            break;
        }
        current = current->next;
    } while (current != frameList->head);
    
    // Si no hay frames de Clase 0 o 1, buscar Clase 2
    if (!target) {
        current = frameList->head;
        do {
            if (current->referenceBit && !current->modifiedBit) {
                target = current;
                break;
            }
            current = current->next;
        } while (current != frameList->head);
    }

    // Si todavía no se encuentra un objetivo, usar Clase 3
    if (!target) {
        current = frameList->head;
        do {
            if (current->referenceBit && current->modifiedBit) {
                target = current;
                break;
            }
            current = current->next;
        } while (current != frameList->head);
    }

    return target;
}

// Función para simular la carga de una página a memoria física utilizando NRU
void loadPage(FrameList *frameList, int page, bool modified) {
    Frame *frame = findFrame(frameList, page);
    if (frame != NULL) {
        frame->referenceBit = true;
        frame->modifiedBit = modified;
        return;
    }

    // Si la lista de frames ya está llena, aplicar el algoritmo NRU
    if (frameList->numFrames == NUM_FRAMES) {
        Frame *frameToReplace = selectFrame(frameList);
        if (frameToReplace) {
            frameToReplace->page = page;
            frameToReplace->valid = true;
            frameToReplace->referenceBit = true;
            frameToReplace->modifiedBit = modified;
            return;
        }
    }

    // Crear un nuevo frame y añadirlo a la lista
    frame = createFrame();
    frame->page = page;
    frame->valid = true;
    frame->referenceBit = true;
    frame->modifiedBit = modified; 
    insertFrame(frameList, frame);
}

// Función para imprimir el estado actual de la lista de frames
void printFrameList(FrameList *frameList) {
    printf("Estado actual de la lista de frames:\n");
    Frame *current = frameList->head;
    if (current == NULL) return;
    do {
        printf("Página: %d, ", current->page);
        printf("Estado: %s, ", current->valid ? "Ocupado" : "Vacío");
        printf("Bit de Referencia: %d, ", current->referenceBit);
        printf("Bit de Modificado: %d\n", current->modifiedBit);
        current = current->next;
    } while (current != frameList->head);
    printf("\n");
}

int main() {
    FrameList *frameList = createFrameList();

    // Simular la carga de varias páginas a memoria física
    loadPage(frameList, 1, false);
    loadPage(frameList, 2, false);
    loadPage(frameList, 3, true);
    loadPage(frameList, 4, false);
    printFrameList(frameList);  

    loadPage(frameList, 5, true);
    printFrameList(frameList);  

    // Liberar la memoria utilizada por la lista de frames
    Frame *current = frameList->head;
    if (current != NULL) {
        Frame *temp;
        do {
            temp = current;
            current = current->next;
            free(temp);
        } while (current != frameList->head);
    }
    free(frameList);

    return 0;
}