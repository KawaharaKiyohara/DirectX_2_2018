#pragma once

#include <vector>

//�{�[���B
struct Bone {
	D3DXVECTOR3			localPosition;	//�{�[���̃��[�J�����W�B
	D3DXQUATERNION		localRotation;	//�{�[���̃��[�J����]�B
	D3DXVECTOR3			position;		//�{�[���̃O���[�o�����W�B
	D3DXQUATERNION		rotation;		//�{�[���̃O���[�o����]�B
	std::vector<int>	children;		//�q���B
	D3DXMATRIX			mWorld;			//���[���h�s��A
};
class Skelton {
	std::vector<Bone>			boneArray;		//�Ԑڂ̔z��B
public:
	Skelton();
	~Skelton();
	//�O���[�o���|�[�Y�̌v�Z�B
	void CalcGlobalPose();
	//�{�[����ǉ��B
	void AddBone(int parentNo, const Bone* bone);
	//���[���h�s����擾�B
	const D3DXMATRIX* GetWorldMatrix(int boneNo);
	//�{�[�����擾�B
	Bone* GetBone(int jointNo);
private:
	void CalcGlobalPose(Bone* bone, Bone* parentBone);
};