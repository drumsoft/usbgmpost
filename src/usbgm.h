// usbgm.h

// バージョン取得
extern "C" __declspec(dllexport) BSTR __stdcall GetVers(BSTR devname);
// USB-GEIGERデバイスの検索
extern "C" __declspec(dllexport) BSTR __stdcall FindUSB(int *index);
// カウント数と時間の取得
extern "C" __declspec(dllexport) int __stdcall GetCountTime(BSTR devname, int *count, int *time);
// 初期化
extern "C" __declspec(dllexport) int __stdcall Clear(BSTR devname);
