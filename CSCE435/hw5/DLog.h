
/***********************************************************

 *  DLog.h

 *  Simple logging mechanism for CUDA device code

 *

 *  Usage: 

 *	   1. include it in your .cu file

 *	   2. call DLog_Init(size) to reserve size bytes as output buffer 

 *		   on device

 *	   3. call DLog<<data in your CUDA device code

 *	   4. call DLog_Dump() after kernel invocation to dump the output

 *

 *  This implementation is very simple, and inefficient. It supports only 

 *	 char, int and const char *.

 *

 *  Author: Chuntao HONG (chuntao.hong@gmail.com)

 *  Last modified: Oct. 13th, 2009

************************************************************/

#ifndef DLOG_H

#define DLOG_H



#include <cuda.h>

#include <iostream>

using namespace std;



const int MIN_ALIGN=4;



// align n to b bytes

template<class T>

__device__ T Align(T n, uint32_t b){

		return ((uint32_t)n&(b-1))==NULL ? n : n+b-((uint32_t)n&(b-1));

}



template<class T>

__device__ T MinAlign(T n){

		return ((uint32_t)n&(MIN_ALIGN-1))==NULL ? n : n+MIN_ALIGN-((uint32_t)n&(MIN_ALIGN-1));

}



// set some empty bytes, so that the logging data structures won't be polluted by out-of-bound writes

const int SAFTY_BYTES=1024*1024;



// data types supported, now only three

enum DataType{

		CHAR,

		INT,

		STRING

};



struct LogPack{

		int size;

		DataType type;

		union{

				char c;

				int i;

				char str[];

		}data;

};



__device__ int requiredLogSpace(const char*);

__device__ int requiredLogSpace(const int);

__device__ int requiredLogSpace(const unsigned int);

__device__ int requiredLogSpace(const char);



__device__ void assignLog(LogPack *, const char c);

__device__ void assignLog(LogPack *, const char * c);

__device__ void assignLog(LogPack *, const int c);

__device__ void assignLog(LogPack *, const unsigned int c);





struct MyLog{

public:

		char empty_bytes[SAFTY_BYTES];

		char * buf;

		unsigned int curPos;

		char empty_bytes2[SAFTY_BYTES];

public:

		template <class T>

		__device__ MyLog & operator<<(const T & t){

				int packSize=MinAlign(requiredLogSpace(t));

				int start=atomicAdd(&curPos, packSize);

				LogPack * pack=(LogPack *)(buf+start);

				assignLog(pack,t);

				pack->size=packSize;

				return *this;

		}

};



__device__ MyLog DLog;



__device__ int requiredLogSpace(const int i){

		return sizeof(i)+sizeof(DataType)+sizeof(int);

}

__device__ int requiredLogSpace(const char * str){

		int len=0;

		while(*str++){

				len++;

		}

		return len+1+sizeof(DataType)+sizeof(int);

}

__device__ int requiredLogSpace(const unsigned int i){

		return sizeof(i)+sizeof(DataType)+sizeof(int);

}

__device__ int requiredLogSpace(const char c){

		return sizeof(c)+sizeof(DataType)+sizeof(int);

}



__device__ void assignLog(LogPack * pack, const char c){

		pack->data.c=c;

		pack->type=CHAR;

}

__device__ void assignLog(LogPack * pack, const int i){

		pack->data.i=i;

		pack->type=INT;

}

__device__ void assignLog(LogPack * pack, const unsigned int i){

		pack->data.i=i;

		pack->type=INT;

}

__device__ void assignLog(LogPack * pack, const char * str){

		int i=0;

		while(*str){

				pack->data.str[i++]=*str;

				str++;

		}

		pack->type=STRING;

}





__host__ void DLog_Init(unsigned int size){

		MyLog localLog;

		localLog.curPos=SAFTY_BYTES;

		cudaMalloc((void**)&localLog.buf, size+SAFTY_BYTES);

		cudaMemset(localLog.buf, 0, size);

		cudaMemcpyToSymbol(DLog, &localLog, sizeof(MyLog), 0, cudaMemcpyHostToDevice);

}



__host__ void DLog_Dump(){

		MyLog localLog;

		cudaMemcpyFromSymbol(&localLog, DLog, sizeof(MyLog), 0, cudaMemcpyDeviceToHost);

		char * h_buf=new char[localLog.curPos+1];

		cudaMemcpy(h_buf, localLog.buf, localLog.curPos, cudaMemcpyDeviceToHost);

		cudaFree(localLog.buf);



		char * ptr=h_buf+SAFTY_BYTES;

		while(ptr<h_buf+localLog.curPos){

				LogPack * pack=(LogPack *)ptr;

				if(pack->type==CHAR){
						printf(pack->data.c);
						//cout<<pack->data.c<<endl;

				}

				else if(pack->type==INT){
						printf("blah balh");
						//cout<<"0x"<<hex<<pack->data.i<<endl;

				}

				else{

						//cout<<pack->data.str<<endl;

				}

				ptr+=pack->size;

		}



		delete[] h_buf;

}



#endif