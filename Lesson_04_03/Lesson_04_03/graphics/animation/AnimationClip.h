/*!
 *@brief	�A�j���[�V�����N���b�v�B
 */

#pragma once


/*!
*@brief	�A�j���[�V�����N���b�v�̃w�b�_�[�B
*/
struct AnimClipHeader {
	std::uint32_t numKey;				//!<�L�[�t���[���̐��B
	std::uint32_t numAnimationEvent;	//!<�A�j���[�V�����C�x���g�̐��B
};
/*!
*@brief	�A�j���[�V�����C�x���g
*@�A�j���[�V�����C�x���g�͖��Ή��B
* ��肽�������玩���Ŏ�������悤�ɁB
*/
struct AnimationEventData {
	float	invokeTime;					//!<�A�j���[�V�����C�x���g���������鎞��(�P��:�b)
	std::uint32_t eventNameLength;		//!<�C�x���g���̒����B
};
/*!
*@brief	�L�[�t���[���B
*/
struct Keyframe {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	CMatrix transform;			//!<�g�����X�t�H�[���B
};
/*!
*@brief	�L�[�t���[���B
*/
struct KeyframeRow {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	CVector3 transform[4];		//!<�g�����X�t�H�[���B
};

/*!
*@brief	�A�j���[�V�����N���b�v�B
*/
class AnimationClip  {
public:
	/*!
		*@brief	�{�[���̃t���[�Y���B
		*/
	struct SFreezeBoneInfo {
		int boneNo;		//!<�t���[�Y������{�[���ԍ��B
		bool freezeX;	//!<X�����̈ړ����t���[�Y������H
		bool freezeY;	//!<Y�����̈ړ����t���[�Y������H
		bool freezeZ;	//!<Z�����̈ړ����t���[�Y������H
	};
	typedef std::vector<Keyframe*>		keyFramePtrList;
	/*!
	* @brief	�R���X�g���N�^
	*/
	AnimationClip() 
	{
	}
	/*!
		*@brief	�f�X�g���N�^�B
		*/
	~AnimationClip();
	/*!
		*@brief	�A�j���[�V�����N���b�v�����[�h�B
		*@param[in]	filePath	�t�@�C���p�X�B
		*@param[in]	clipName	�N���b�v���B
		*/
	void Load(const wchar_t* filePath, const wchar_t* cliipName = nullptr);

	/*!
	*@brief	���[�v����H
	*/
	bool IsLoop() const
	{
		return m_isLoop;
	}
	/*!
	*@brief	���[�v�t���O��ݒ肷��B
	*/
	void SetLoopFlag(bool flag)
	{
		m_isLoop = flag;
	}
	/*!
	*@brief
	*/
	const std::vector<keyFramePtrList>& GetKeyFramePtrListArray() const
	{
		return m_keyFramePtrListArray;
	}
	const keyFramePtrList& GetTopBoneKeyFrameList() const
	{
		return *m_topBoneKeyFramList;
	}
	/*!
	*@brief	�N���b�v�����擾�B
	*/
	const wchar_t* GetName() const
	{
		return m_clipName.c_str();
	}
	
	/*!
	*@brief	�A�j���[�V�����N���b�v�̓��[�h�ς݁H
	*/
	bool IsLoaded() const
	{
		return m_loaded;
	}
private:
	using KeyframePtr = std::unique_ptr<Keyframe>;
	std::wstring m_clipName;	//!<�A�j���[�V�����N���b�v�̖��O�B
	bool m_isLoop = false;	//!<���[�v�t���O�B
	std::vector<KeyframePtr>		m_keyframes;				//�L�[�t���[���B
	std::vector<keyFramePtrList>	m_keyFramePtrListArray;		//�{�[�����Ƃ̃L�[�t���[���̃��X�g���Ǘ����邽�߂̔z��B
	keyFramePtrList*				m_topBoneKeyFramList = nullptr;
	bool m_loaded = false;	//�A�j���[�V�����N���b�v�����[�h����Ă���H
};
using AnimationClipPtr = std::unique_ptr<AnimationClip>;
