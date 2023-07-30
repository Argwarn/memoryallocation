#include <stdio.h>
#include <stdlib.h>
#define N 256
#define KB 1024*4
#define MB 1024*1024

int fit;
//int memory[N][4*KB/3+1];


/*void mem_initialise(void){
  for(int i=0;i<N;i++){
    memory[i][0]=4096;
  }
}*/
//start é deslocamento
struct Page{
  int pid;
  int start;
  int mem_units;
  struct Page* next;
};
struct Page* createHole(int mem_units,int start) {
  struct Page* newHole = (struct Page*)malloc(sizeof(struct Page));
  newHole->pid=-1;
  newHole->start=start;
  newHole->mem_units=mem_units;
  newHole->next = NULL;
 
  return newHole;
}
struct Page* createPage(int pid,int mem_units ,int start) {
    struct Page* newProcess = (struct Page*)malloc(sizeof(struct Page));
    newProcess->pid= pid;
    newProcess->mem_units = mem_units;
    newProcess->start = start;
    newProcess->next = NULL;
    return newProcess;
}
struct Page* initializePages(struct Page* head) {
  struct Page* newHole = createHole(N,0);
  return newHole;
}
struct Page* insert(struct Page* currentProcess,int pid,int mem_units,int start){
  struct Page* newProcess = createPage(pid,mem_units,start);
  currentProcess->next=newProcess;
  
  return newProcess;
}
void first_fit(){
  
}

int alloc_mem (struct Page* head, int pid, int mem_units){
  struct Page* processHead = head;
  struct Page* hole;
  int start = 0;
  int skip = 0;
  int sort;
  switch(fit){
    case 1:
      //first fit
      for(;processHead!=NULL;processHead=processHead->next){
        //testa se é um hole
        if(processHead->pid ==-1 &&processHead->mem_units >= mem_units){
          
          hole=processHead;
          hole->mem_units= hole->mem_units - mem_units;
          start = hole->start;
          hole->start=hole->start +mem_units;
          struct Page* newProcess=insert(processHead,pid,mem_units,start);
          printf("processo de pid: %d criado\n",newProcess->pid);
        }
      }
      
      
      
      break;
    case 2:
      //next fit
      for(;processHead!=NULL;processHead=processHead->next){
        if(processHead->pid ==-1 &&processHead->mem_units >= mem_units){
          if(skip||processHead->next==NULL){
            hole=processHead;
            hole->mem_units= hole->mem_units - mem_units;
            start = hole->mem_units+hole->start;
            struct Page* newProcess=insert(processHead,pid,mem_units,start);
            printf("processo de pid: %d criado\n",newProcess->pid);
            break;
         }
          skip++;
        }
      }
      break;
    case 3:
      //best fit
      sort = 9999;
      for(int i=0;processHead!=NULL;processHead=processHead->next,i++){
        if(processHead->pid ==-1 &&processHead->mem_units >= mem_units){
          if(processHead->mem_units<sort){
            sort=processHead->mem_units;
            hole=processHead;
          }
        }
      }
      if (sort !=9999){
      hole->mem_units= hole->mem_units - mem_units;
      start = hole->start;
      hole->start=hole->start +mem_units;
      struct Page* newProcess=insert(processHead,pid,mem_units,start);
      printf("processo de pid: %d criado\n",newProcess->pid);
      return newProcess->pid;}
      break;
    case 4:
      //worst fit
      sort = -1;
      for(int i=0;processHead!=NULL;processHead=processHead->next,i++){
        if(processHead->pid ==-1 &&processHead->mem_units >= mem_units){
          if(processHead->mem_units>sort){
            sort=processHead->mem_units;
            hole=processHead;
          }
        }
      }
      if (sort !=-1){
      hole->mem_units= hole->mem_units - mem_units;
      start = hole->start;
      hole->start=hole->start +mem_units;
      struct Page* newProcess=insert(processHead,pid,mem_units,start);
      printf("processo de pid: %d criado\n",newProcess->pid);
      return newProcess->pid;}
      break;
    default:
    printf("Erro");
  }
  return 0;
}
int main(void) {
  struct Page* head; 
  head = initializePages(head);
  fit=2;
  for(int n=0;n<256;n++){
    alloc_mem(head, n, 1);
  }
  return 0;
}