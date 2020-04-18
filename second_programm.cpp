#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h>

using namespace std;

string tmp = "";
sem_t semaphore;

void *content_start(void *s){
	sem_wait(&semaphore);
	pid_t pr;
 	pr = fork();
	int status;
	if(pr == 0){
		cout<<"\nPID: "<<getpid()<<endl;
		execl("first", "-c 1", (char*) tmp.c_str(), NULL);
	}
	else if (pr > 0){
		wait(&status);
	}
	//sleep(2);
	sem_post(&semaphore);
}

int main(int argc, char *argv[]){
	int rc;
	void* status;
	cout<<"Введите интересующий Вас ip-адрес: ";
	string adres;
	cin>>adres;
	for(int i=adres.size()-1;adres[i]!='.';i--)	//удаление символов до первой точки
		adres.pop_back();
	pthread_t thread[254];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
   	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   	sem_init(&semaphore, 0, 1);
	for(int i=1;i<255;i++){
		tmp = adres+std::to_string(i);
		rc = pthread_create(&thread[i], &attr, content_start, (void*) &tmp);
		if(rc){
 			cout<<" Error:unable to create thread, "<<rc<<endl;
         	exit(-1);
      	}
		pthread_join(thread[i], &status);
	}
	sem_destroy(&semaphore);
	pthread_attr_destroy(&attr); 
	return 0;
}