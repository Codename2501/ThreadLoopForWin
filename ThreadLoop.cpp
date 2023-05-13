/* ThreadLoop.cpp */ 
#include "Threadloop.h" 

unsigned __stdcall CreateThreadMethod(void *); 
unsigned __stdcall NormalSwitchMethod(void *); 
unsigned __stdcall ErrSwitchMethod(void *); 
unsigned __stdcall LoopThreadMethod(void *); 
unsigned __stdcall EndThreadMethod(void *); 
int MainRoutineMethod(); 
void EndMethod(); 

int main() 
{ 
g_MethodHandle[0]=(HANDLE)_beginthreadex(NULL,0,CreateThreadMethod,0,NULL,&g_threadflag); 
g_MethodHandle[1]=(HANDLE)_beginthreadex(NULL,0,LoopThreadMethod,0,NULL,&g_threadflag); 
WaitForMultipleObjects(2,g_MethodHandle,true,g_waittime); 

return EXIT_SUCCESS; 
} 
unsigned __stdcall CreateThreadMethod(void *p) 
{ 
/*メインルーチンの挙動判定（仮）*/ 
int errjudge=MainRoutineMethod(); 
if(errjudge>=0) 
{ 
/*正常系の処理に移行する*/ 
CloseHandle(g_NormalThreadHandle); 
g_NormalThreadHandle=(HANDLE)_beginthreadex(NULL,0,NormalSwitchMethod,&errjudge,NULL,&g_threadflag); 
WaitForSingleObject((HANDLE)g_NormalThreadHandle,g_waittime); 
} 
else if(errjudge<=-1) 
{ 
/*異常系の処理に移行する（仮）*/ 
CloseHandle(g_ErrThreadHandle); 
g_ErrThreadHandle=(HANDLE)_beginthreadex(NULL,0,ErrSwitchMethod,&errjudge,NULL,&g_threadflag); 
WaitForSingleObject((HANDLE)g_ErrThreadHandle,g_waittime); 
} 
return 0; 
} 
unsigned __stdcall LoopThreadMethod(void *p) 
{ 
g_EndThreadMethodHandle=(HANDLE)_beginthreadex(NULL,0,EndThreadMethod,0,NULL,&g_threadflag); 
WaitForSingleObject((HANDLE)g_EndThreadMethodHandle,g_waittime); 
return 0; 
} 
int MainRoutineMethod() 
{ 
static int count=0; 
//printf("%d\n",g_waittime); 
//最小値 +(int)( rand() * (最大値 - 最小値 + 1.0) / (1.0 + RAND_MAX) ) 
//srand(time_t(NULL)); 
g_editflagnormal1=(int)pow(-1.0,count); 
Sleep(100); 
count++; 
return g_editflagnormal1; 
} 
unsigned __stdcall NormalSwitchMethod(void *p) 
{ 
/*正常系スレッド処理*/ 
int* i=(int*)p; 
g_normalcount++; 
printf("引き続き正常系[%d]の処理を実行します[回数[%d]]\n",*i,g_normalcount); 

CloseHandle(g_CreateThreadHandle); 
g_CreateThreadHandle=(HANDLE)_beginthreadex(NULL,0,CreateThreadMethod,0,NULL,&g_threadflag); 
return 0; 
} 
unsigned __stdcall ErrSwitchMethod(void *p) 
{ 
/*異常系スレッド処理*/ 
int* i=(int*)p; 
g_errcount++; 
printf("引き続き異常系[%d]の処理を実行します[回数[%d]]\n",*i,g_errcount); 
CloseHandle(g_CreateThreadHandle); 
if(g_errcount>100){ 
printf("Err count over 100\n"); 
} 
else{ 
g_CreateThreadHandle=(HANDLE)_beginthreadex(NULL,0,CreateThreadMethod,0,NULL,&g_threadflag); 
} 
return 0; 
} 
unsigned __stdcall EndThreadMethod(void *p) 
{ 
int i; 
int ch,ch2; 
fpos_t fpos=0; 
fflush(stdin); 
ch2='\n'; 
while((ch=fgetc(stdin))!='\n') 
{ 
fgetpos(stdin,&fpos); 
ch2=ch; 
} 
if(ch2=='q' || ch2=='Q') 
{ 
if(fpos==1) 
{ 
CloseHandle((HANDLE)g_MethodHandle[0]); 
CloseHandle((HANDLE)g_MethodHandle[1]); 
printf("PROGRAM END\n"); 
return EXIT_SUCCESS; 
} 
} 

g_LoopThreadMethodHANDLE=(HANDLE)_beginthreadex(NULL,0,LoopThreadMethod,0,NULL,&g_threadflag); 
WaitForSingleObject((HANDLE)g_LoopThreadMethodHANDLE,g_waittime); 
return 0; 
}
