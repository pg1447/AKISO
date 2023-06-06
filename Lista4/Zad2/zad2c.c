#include <stdio.h>
#include <pthread.h>

void *create_tread_two(){
    printf("watek w watku\n");
    return NULL;
}

void *create_thread_one(){
  pthread_t t2;
  pthread_create(&t2, NULL, create_tread_two,NULL);
  pthread_join(t2,NULL);
  printf("watek baza\n");

} 

int main(){
  pthread_t t1;
  pthread_create(&t1,NULL,create_thread_one,NULL);
  pthread_join(t1,NULL);
  
 return 0; 
}