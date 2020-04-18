#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 

using namespace std;

string tmp = "";

void *content_start(void *s){
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
}

int main(int argc, char *argv[]){
	int rc;
	void* status;
	cout<<"Введите интересующий Вас ip-адрес: ";
	string adres;
	cin>>adres;
	/*
	string name="first";
	string tmp="";
	char *argm[3];
	argm[0]=(char*) name.c_str();
	argm[2]=NULL;
	*/
	for(int i=adres.size()-1;adres[i]!='.';i--)	//удаление символов до первой точки
		adres.pop_back();

	pthread_t thread[254];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
   	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for(int i=1;i<255;i++){
		tmp = adres+std::to_string(i);
		rc = pthread_create(&thread[i], &attr, content_start, (void*) &tmp);
		
		if(rc){
 			cout<<" Error:unable to create thread, "<<rc<<endl;
         	exit(-1);
      	}
		pthread_join(thread[i], &status);
	}
	return 0;
}