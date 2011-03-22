//usbgmget.cpp
/*

Strawberry Linux �Ђ� USB-GEIGER ���g���Čv������cpm���o��

���̍s��W���o�͂܂��͎w�肳�ꂽ�t�@�C���֏o�͂���
YYYY/MM/DD hh:mm:ss,Count,Time\n

bcc32 �ł̃R���p�C���̂��߂̏���(Make�łł���l�ɂ���)
	1. bcc32 ���Z�b�g�A�b�v����
		�Q�l) http://apis.jpn.ph/fswiki/wiki.cgi?page=Win32%2FCompiler%2FBcc32
		DL  ) http://update.codegear.com/forms/jp_cpp_download_reg
		�C���X�g�[������Bin�t�H���_�Ƀp�X��ʂ�
		Bin�t�H���_�� bcc32.cfg, ilink32.cfg ��ݒu����
	2. ���C�u�����̏���
		Strawberry Linux �̃T�C�g
		http://strawberry-linux.com/catalog/items?code=53001
		���烉�C�u�������_�E�����[�h���āA
		gmlib.dll �����̃t�H���_�ɐݒu����
	3. make �ŃR���p�C��
*/

//�f�o�C�X����\������
//#define DEBUG
//���̎w��b�����ƂɃJ�E���g�����Z�b�g���� // 365*24*60*60
#define RESETINTERVAL 31536000
//���̎w��J�E���g�𒴂���ƃ��Z�b�g���� // 2^29-1
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

	//�f�o�C�X�̌���
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

//����l�̏o��
void printValues(BSTR dev, FILE *out) {
	//�擾
	int count, time;
	int re;
	re = GetCountTime(dev, &count, &time);

	//�����o��
	printTime(out);
	if ( re == 0 ) {
		fprintf(out, "%d,%d\n", count, time);
		if (time >= RESETINTERVAL || count >= RESETCOUNT) Clear(dev);
	}else{
		fprintf(out, "ERROR: Cannot get values from USB-GEIGER (%d) .\n", re);
		fprintf(stderr, "ERROR: Cannot get values from USB-GEIGER (%d) .\n", re);
	}
}

//�����̏o��
void printTime(FILE *out) {
	time_t timer;
	struct tm *t_st;
	time(&timer);
	t_st = localtime(&timer);
	fprintf(out, "%04d-%02d-%02d %02d:%02d:%02d,", 
		   t_st->tm_year+1900, t_st->tm_mon+1, t_st->tm_mday, 
		   t_st->tm_hour, t_st->tm_min, t_st->tm_sec);
}
