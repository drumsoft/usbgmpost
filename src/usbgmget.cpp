//usbgmget.cpp
/*

Strawberry Linux 社の USB-GEIGER を使って計測したcpmを出力

次の行を標準出力または指定されたファイルへ出力する
YYYY/MM/DD hh:mm:ss,Count,Time\n

bcc32 でのコンパイルのための準備(Makeでできる様にした)
	1. bcc32 をセットアップする
		参考) http://apis.jpn.ph/fswiki/wiki.cgi?page=Win32%2FCompiler%2FBcc32
		DL  ) http://update.codegear.com/forms/jp_cpp_download_reg
		インストールしたBinフォルダにパスを通す
		Binフォルダに bcc32.cfg, ilink32.cfg を設置する
	2. ライブラリの準備
		Strawberry Linux のサイト
		http://strawberry-linux.com/catalog/items?code=53001
		からライブラリをダウンロードして、
		gmlib.dll をこのフォルダに設置する
	3. make でコンパイル
*/

//デバイス名を表示する
//#define DEBUG
//この指定秒数ごとにカウントをリセットする // 365*24*60*60
#define RESETINTERVAL 31536000
//この指定カウントを超えるとリセットする // 2^29-1
#define RESETCOUNT 536870911

#include <windows.h>
#include <stdio.h>
#include <time.h>

#include "usbgm.h"

//prototypes
int main(int argc, const char *argv[]);
void printValues(BSTR dev, FILE *out);
void printTime(FILE *out);

//------------------------------------------------------main

int main(int argc, const char *argv[]) {
	FILE *fp;
	
#ifdef DEBUG
	fprintf(stderr, "usbgmget...\n");
#endif

	if (argc > 1) {
		fp = fopen(argv[1], "a");
		if (NULL == fp) {
			fprintf(stderr, "ERROR: Cannot open log file.\n");
			exit(74);
		}
	}else{
		fp = stdout;
	}

	//デバイスの検索
	int devindex = 0;
	BSTR dev = FindUSB(&devindex);
	if ( ((char *)dev)[0] == 0) {
		fprintf(stderr, "ERROR: Cannot find USB-GEIGER device.\n");
		printTime(fp);
		fprintf(fp, "ERROR: Cannot find USB-GEIGER device.\n");
		SysFreeString(dev);
		if (fp != stdout) fclose(fp);
		exit(69);
	}
#ifdef DEBUG
	fprintf(stderr, "(USB-GEIGER device '%s')\n", (char *)dev);
#endif

	printValues(dev, fp);

	SysFreeString(dev);
	if (fp != stdout) fclose(fp);
	return 0;
}

//測定値の出力
void printValues(BSTR dev, FILE *out) {
	//取得
	int count, time;
	int re;
	re = GetCountTime(dev, &count, &time);

	//書き出し
	printTime(out);
	if ( re == 0 ) {
		fprintf(out, "%d,%d\n", count, time);
		if (time >= RESETINTERVAL || count >= RESETCOUNT) Clear(dev);
	}else{
		fprintf(out, "ERROR: Cannot get values from USB-GEIGER (%d) .\n", re);
		fprintf(stderr, "ERROR: Cannot get values from USB-GEIGER (%d) .\n", re);
	}
}

//時刻の出力
void printTime(FILE *out) {
	time_t timer;
	struct tm *t_st;
	time(&timer);
	t_st = localtime(&timer);
	fprintf(out, "%04d-%02d-%02d %02d:%02d:%02d,", 
		   t_st->tm_year+1900, t_st->tm_mon+1, t_st->tm_mday, 
		   t_st->tm_hour, t_st->tm_min, t_st->tm_sec);
}
