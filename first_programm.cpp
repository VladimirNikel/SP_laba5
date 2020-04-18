#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main(int argc, char *argv[]){
	char *argumenty[5];
	string command = "ping";
	string par = "-c";
	string znac = "1";

	argumenty[0]=(char*) command.c_str();
	argumenty[1]=(char*) par.c_str();
	argumenty[2]=(char*) znac.c_str();
	argumenty[3]=argv[1];
	argumenty[4]=NULL; 

	if(execvp (argumenty[0],argumenty) == -1){
		perror ("exec");
	}
	else
		exit(0);
}