#ifndef  DEBUG_H
    #define DEBUG_H



#ifdef	_DEBUG    
#define ASSERT(bool)	do{if(!bool){\
								printf("assert error");\
								while(1);\
						}while(0);\
						

#else
#define ASSERT(bool)	

#endif


//do{while(!bool){
//								printf("assert 0");
//							}
//						}while(0);    
    
    
#endif    