
#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    string strMapName("ShareMemory");                // 坪贋啌符斤?鹵?各
    string strComData("This is common data!");        // 慌?軣擺耿亠鎚?象
    LPVOID pBuffer;                                    // 慌?軣擺耿胡?

    // 遍枠編夕嬉蝕匯倖凋兆議坪贋啌符猟周斤??  
    HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, strMapName.c_str());
    if (NULL == hMap)
    {    // 嬉蝕払移??幹秀岻
        hMap = ::CreateFileMapping(
            INVALID_HANDLE_VALUE,         // 麗尖猟周鞘凹  NVALID_HANDLE_VALUE  夸幹秀匯倖序殻寂慌?躓超塹?
            NULL,                         // 潮範芦畠雫艶
            PAGE_READWRITE,               // 辛響辛亟
            0,                            // 互了猟周寄弌
            strComData.length() + 1,      // 詰了猟周寄弌
            strMapName.c_str());          // 啌符猟周兆??軸慌?軣擺羌鎮?各

        // 啌符斤?鶺漬燦?篇夕??誼欺峺?鮃河軣擺羌綴胡襭?譜崔戦中議方象
        pBuffer = ::MapViewOfFile(
            hMap, 
            FILE_MAP_ALL_ACCESS, 
            0, 
            0, 
            0);                     //dwNumberOfBytesToMapにはマッピングするバイト方を峺協します。0を峺協するとファイル畠悶をマッピングします。
        strcpy((char*)pBuffer, strComData.c_str());
        cout << "亟秘慌?軣擺翳?象??" << (char*)pBuffer << endl;
    }
    else
    {    // 嬉蝕撹孔??啌符斤?鶺漬燦?篇夕??誼欺峺?鮃河軣擺羌綴胡襭??塋廠?戦中議方象
        pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 
            0); //dwNumberOfBytesToMapにはマッピングするバイト方を峺協します。0を峺協するとファイル畠悶をマッピングします。
        cout << "響函慌?軣擺翳?象??" << (char*)pBuffer << endl;
    }

    getchar();            // 廣吭??序殻購液朔??侭嗤鞘凹徭強購液??侭參勣壓宸戦壙唯

    // 盾茅猟周啌符??購液坪贋啌符猟周斤?鷯箟?
    ::UnmapViewOfFile(pBuffer);
    ::CloseHandle(hMap);
    system("pause");
    return 0;
}
//！！！！！！！！！！！！！！！！
//井幡蕗苧?艮称栂?CSDN鴬麼仝賠邦哭劾剩々議圻幹猟嫗??恆儉CC 4.0 BY - SA井幡亅咏??廬墮萩現貧圻猟竃侃全俊式云蕗苧。
//圻猟全俊??https ://blog.csdn.net/shuilan0066/article/details/87979315