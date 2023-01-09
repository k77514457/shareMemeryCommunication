
#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    string strMapName("ShareMemory");                // �ڴ�ӳ���������
    string strComData("This is common data!");        // �����ڴ��е�����
    LPVOID pBuffer;                                    // �����ڴ�ָ��

    // ������ͼ��һ���������ڴ�ӳ���ļ�����  
    HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
    if (NULL == hMap)
    {    // ��ʧ�ܣ�����֮
        hMap = ::CreateFileMapping(
            INVALID_HANDLE_VALUE,         // �����ļ����  NVALID_HANDLE_VALUE  �򴴽�һ�����̼乲��Ķ���
            NULL,                         // Ĭ�ϰ�ȫ����
            PAGE_READWRITE,               // �ɶ���д
            0,                            // ��λ�ļ���С
            strComData.length() + 1,      // ��λ�ļ���С
            strMapName.c_str());          // ӳ���ļ������������ڴ������

        // ӳ������һ����ͼ���õ�ָ�����ڴ��ָ�룬�������������
        pBuffer = ::MapViewOfFile(
            hMap, 
            FILE_MAP_ALL_ACCESS, 
            0, 
            0, 
            0);                     //dwNumberOfBytesToMap�ˤϥޥåԥ󥰤���Х�������ָ�����ޤ���0��ָ������ȥե�����ȫ���ޥåԥ󥰤��ޤ���
        strcpy((char*)pBuffer, strComData.c_str());
        cout << "д�빲���ڴ����ݣ�" << (char*)pBuffer << endl;
    }
    else
    {    // �򿪳ɹ���ӳ������һ����ͼ���õ�ָ�����ڴ��ָ�룬��ʾ�����������
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 
            0); //dwNumberOfBytesToMap�ˤϥޥåԥ󥰤���Х�������ָ�����ޤ���0��ָ������ȥե�����ȫ���ޥåԥ󥰤��ޤ���
        cout << "��ȡ�����ڴ����ݣ�" << (char*)pBuffer << endl;
    }

    getchar();            // ע�⣬���̹رպ����о���Զ��رգ�����Ҫ��������ͣ

    // ����ļ�ӳ�䣬�ر��ڴ�ӳ���ļ�������
    ::UnmapViewOfFile(pBuffer);
    ::CloseHandle(hMap);
    system("pause");
    return 0;
}
//��������������������������������
//��Ȩ����������ΪCSDN��������ˮӭ��������ԭ�����£���ѭCC 4.0 BY - SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https ://blog.csdn.net/shuilan0066/article/details/87979315