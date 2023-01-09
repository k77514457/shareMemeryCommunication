#include <iostream>  
#include <windows.h>  
#include <string>
using namespace std;

#define BUF_SIZE 4096

HANDLE g_EventRead;		// 读信号灯
HANDLE g_EventWrite;	// 写信号灯


DWORD __stdcall ReadThread(const LPVOID lp)
{
	while (true)
	{
		WaitForSingleObject(g_EventRead, INFINITE); // 等待读数据的信号
	// 将数据拷贝到共享内存

	// 将共享内存数据拷贝出来
		char szBuffer[BUF_SIZE]{ 0 };
		
		strcpy_s(szBuffer, (char*)lp);
		
		std::cout << "客户端 数据读取成功！：" << szBuffer << endl;

		ResetEvent(g_EventRead); /* 将读取信号关闭  */
		SetEvent(g_EventWrite);
	}
}

int main()
{
	// 打开共享的文件对象
	HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"ShareMemoryPDU");

	if (0 == hMapFile)                         //
	{										   //
		// 打开共享内存句柄失败				   //
		std::cout << "打开共享失败！" << endl; //
		return 0;							   //
	}

	LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 
		0); //dwNumberOfBytesToMapにはマッピングするバイト数を指定します。0を指定するとファイル全体をマッピングします。
	if (0 == lpBase)
	{
		return 0;
	}

	g_EventRead = CreateEventW(
		NULL, 				   //安全属性 默认为NULL
		TRUE, 				   //复位方式 (true-手工恢复， false-自动恢复)
		FALSE, 				   //初始状态 (true-有信号，false-无信号)
		TEXT("EventRead"));	   //事件名称
	if (nullptr == g_EventRead)
	{
		return 0;
	}

	g_EventWrite = CreateEventW(
		NULL, 				   //安全属性 默认为NULL
		TRUE, 				   //复位方式 (true-手工恢复， false-自动恢复)
		TRUE, 				   //初始状态 (true-有信号，false-无信号)
		TEXT("EventWrite"));   //事件名称
	if (nullptr == g_EventWrite)
	{
		return 0;
	}

	HANDLE handle = CreateThread(NULL, 0, ReadThread, lpBase, 0, NULL);
	if (0 == handle)
	{
		return 0;
	}
	
	WaitForSingleObject(handle, INFINITE);
	// 解除文件映射
	
	UnmapViewOfFile(lpBase);
	// 关闭内存映射文件对象句柄
	CloseHandle(hMapFile);


	return 0;
}
//————————————————
//版权声明：本文为CSDN博主「林夕07」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/qq_45254369/article/details/128152170