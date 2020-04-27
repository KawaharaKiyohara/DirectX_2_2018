#pragma once
#include <map>

/*!
*@brief	�X�L�����f���f�[�^�}�l�[�W���[�B�B
*/
class SkinModelDataManager
{
public:
	/*!
	*@brief	���f�������[�h�B
	*@param[in]	filePath	�t�@�C���p�X�B
	*/
	DirectX::Model* Load(const wchar_t* filePath);
	/*!
	*@brief	���f���f�[�^��S�J���B
	*/
	void Release();
private:
	//�t�@�C���p�X���L�[�ADirectXModel�̃C���X�^���X��l�Ƃ���}�b�v�B
	//�����݂����Ȃ��̂ł��B
	map< wstring, DirectX::ModelPtr > m_directXModelMap;
};

//g_skinModelDataManager��extern�錾�B
//extern�錾�͎��Ԃł͂Ȃ��̂Œ��ӁI
//�R���p�C���ɂǂ����ɂ��邩��g���Ă˂Ƌ�������́B
extern SkinModelDataManager g_skinModelDataManager;

