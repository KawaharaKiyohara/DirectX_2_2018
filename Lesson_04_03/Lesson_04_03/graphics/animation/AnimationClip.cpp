/*!
 *@brief	�A�j���[�V�����N���b�v�B
 */

#include "stdafx.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/skeleton.h"


AnimationClip::~AnimationClip()
{
}

void AnimationClip::Load(const wchar_t* filePath, const wchar_t* clipName)
{
	auto fp = _wfopen(filePath, L"rb");
	if (fp == nullptr) {
#ifdef _DEBUG
		char message[256];
		sprintf(message, "AnimationClip::Load, �t�@�C���̃I�[�v���Ɏ��s���܂����B%s\n", filePath);
		MessageBox(NULL, message, "Error", MB_OK);
		//�~�߂�B
		std::abort();
#endif
		return;
	}
	if (clipName != nullptr) {
		m_clipName = clipName;
	}
	//�A�j���[�V�����N���b�v�̃w�b�_�[�����[�h�B
	AnimClipHeader header;
	fread(&header, sizeof(header), 1, fp);
		
	if (header.numAnimationEvent > 0) {
		//�A�j���[�V�����C�x���g�͖��Ή��B
		std::abort();
	}


	//���g���������ƃ��[�h�B
	auto keyframes = std::make_unique<KeyframeRow[]>(header.numKey);
	fread(keyframes.get(), sizeof(KeyframeRow), header.numKey, fp);
	fclose(fp);
	for (auto i = 0; i < header.numKey; i++) {
		auto keyframe = std::make_unique<Keyframe>();
		keyframe->boneIndex = keyframes[i].boneIndex;
		keyframe->transform = CMatrix::Identity;
		keyframe->time = keyframes[i].time;
		for (auto j = 0; j < 4; j++) {
			keyframe->transform.m[j][0] = keyframes[i].transform[j].x;
			keyframe->transform.m[j][1] = keyframes[i].transform[j].y;
			keyframe->transform.m[j][2] = keyframes[i].transform[j].z;
		}
		m_keyframes.push_back(std::move(keyframe));
	}

	//�{�[���C���f�b�N�X���Ƃ̃L�[�t���[���̘A�����X�g���쐬����B
	m_keyFramePtrListArray.resize(MAX_BONE);
	for (auto& keyframe : m_keyframes) {
		m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
		if (m_topBoneKeyFramList == nullptr) {
			m_topBoneKeyFramList = &m_keyFramePtrListArray[keyframe->boneIndex];
		}
	}
	m_loaded = true;
}

