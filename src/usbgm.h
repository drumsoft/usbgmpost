// usbgm.h

// �o�[�W�����擾
extern "C" __declspec(dllexport) BSTR __stdcall GetVers(BSTR devname);
// USB-GEIGER�f�o�C�X�̌���
extern "C" __declspec(dllexport) BSTR __stdcall FindUSB(int *index);
// �J�E���g���Ǝ��Ԃ̎擾
extern "C" __declspec(dllexport) int __stdcall GetCountTime(BSTR devname, int *count, int *time);
// ������
extern "C" __declspec(dllexport) int __stdcall Clear(BSTR devname);
