#include <windows.h>
#include <iostream> 
using namespace std;

#define BUF_SIZE 4096

HANDLE g_EventRead;		// 读信号灯
HANDLE g_EventWrite;	// 写信号灯
// 定义共享数据
char szBuffer[] = "LinXi07";
/* 读取con1串口的线程 */
DWORD __stdcall WriteThread(const LPVOID lp)
{
	while (true)
	{
		WaitForSingleObject(g_EventWrite, INFINITE); // 等待写数据的信号

		// 将数据拷贝到共享内存
		strcpy((char*)lp, szBuffer);
		cout << "服务端 写成功!等待客户端读取：" << (char*)lp << endl;
		
		Sleep(1000);
		
		ResetEvent(g_EventWrite);
		SetEvent(g_EventRead);
	}
	return DWORD();
}

int main()
{

	// 创建共享文件句柄 
	HANDLE hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,   // 物理文件句柄  NVALID_HANDLE_VALUE  则创建一个进程间共享的对象
		NULL,                   // 默认安全级别
		PAGE_READWRITE,         // 可读可写
		0,                      // 高位文件大小
		BUF_SIZE,               // 低位文件大小
		L"ShareMemoryPDU"       // 映射文件名，即共享内存的名称
	);

	if (0 == hMapFile)  //
	{					//
		return 0;		//
	}					//

	// 映射缓存区视图 , 得到指向共享内存的指针
	// 将hFileMapping共享内存衍射到本进程的地址空间中
	LPVOID lpBase = MapViewOfFile(
		hMapFile,            // 共享内存的句柄
		FILE_MAP_ALL_ACCESS, // 可读写许可
		0,					 // 表示文件映射起始偏移的高32位.
		0,					 // 表示文件映射起始偏移的低32位
		BUF_SIZE             //dwNumberOfBytesToMapにはマッピングするバイト数を指定します。0を指定するとファイル全体をマッピングします。
	);

	if (0 == lpBase)
	{
		return 0;
	}

	g_EventRead = CreateEventW(
		NULL,                 //安全属性 默认为NULL
		TRUE,				  //复位方式 (true-手工恢复， false-自动恢复)
		FALSE, 				  //初始状态 (true-有信号，false-无信号)
		TEXT("EventRead"));	  //事件名称
	if (nullptr == g_EventRead)
	{
		return 0;
	}

	g_EventWrite = CreateEventW(
		NULL,                  //安全属性 默认为NULL
		TRUE, 				   //复位方式 (true-手工恢复， false-自动恢复)
		TRUE, 				   //初始状态 (true-有信号，false-无信号)
		TEXT("EventWrite"));   //事件名称
	if (nullptr == g_EventWrite)
	{
		return 0;
	}

	HANDLE handle = CreateThread(NULL, 0, WriteThread, lpBase, 0, NULL);

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