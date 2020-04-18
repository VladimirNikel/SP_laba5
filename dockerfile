FROM ubuntu

RUN apt update && apt install git -y && apt install build-essential -y && apt install bash -y && apt-get install gcc-multilib -y && apt install iputils-ping -y

WORKDIR /home/app/

RUN git clone https://github.com/VladimirNikel/SP_laba5.git \
	&& cd SP_laba5/ \
	&& g++ first_programm.cpp -o first -pthread \
	&& g++ second_programm.cpp -o second -lstdc++fs -pthread

WORKDIR /home/app/SP_laba5