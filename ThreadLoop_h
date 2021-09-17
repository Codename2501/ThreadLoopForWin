#include<stdio.h>
#include <string.h>
#include<Windows.h>
#include<process.h>

#include<math.h>
#include<time.h>
#include<limits.h>
/*正常系及び異常系の処理回数*/
int g_errcount=0;
int g_erroutputcount=0;
int g_normalcount=0;
/*正常系及び異常系の終了値*/
const int g_totaltimes=1;
/*グローバルエラーフラグ*/
bool g_errflag=false;
/*グローバルエディットフラグ*/
int g_editflagnormal1=0;
int g_editflagnormal2=0;
int g_editflagerr1=0;
int g_editflagerr2=0;
/*グローバルファイナルフラグ*/
bool g_finalflag=false;
/*グローバルスレッドハンドル*/
HANDLE g_CreateThreadHandle=NULL;
HANDLE g_NormalThreadHandleFirst=NULL;
HANDLE g_NormalThreadHandle=NULL;
HANDLE g_ErrThreadHandle=NULL;
HANDLE g_EndThreadHandle=NULL;
HANDLE g_MethodHandle[2]={NULL};
HANDLE g_EndThreadMethodHandle=NULL;
HANDLE g_LoopThreadMethodHANDLE=NULL;
/*グローバルポインター*/
char *g_p=NULL;
/*グローバルウェイトタイム*/
unsigned int g_waittime=INFINITE;
/*グローバルスレッドフラグ*/
unsigned g_threadflag=INFINITE;

int g_str=NULL;
