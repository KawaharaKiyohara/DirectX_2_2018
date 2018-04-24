#include "stdafx.h"
#include "Skelton.h"

Skelton::Skelton()
{

}
Skelton::~Skelton()
{

}
void Skelton::CalcGlobalPose(Bone* bone, Bone* parentBone)
{
	D3DXVECTOR4 pos;
	if (parentBone != NULL) {
		//�e������B
		//���[�J�����W�ɐe�̍s�����Z���āA���[���h���W�ɕϊ�����B
		D3DXVec3Transform(&pos, &bone->localPosition, &parentBone->mWorld);
		bone->position.x = pos.x;
		bone->position.y = pos.y;
		bone->position.z = pos.z;

		//���[�J����]�ɐe�̉�]�������āA���[���h��]�ɕϊ�����B
		bone->rotation = bone->localRotation * parentBone->rotation;

		//���[���h�s����v�Z����B
		D3DXMATRIX mRot, mTrans;
		D3DXMatrixRotationQuaternion(&mRot, &bone->rotation);
		D3DXMatrixTranslation(&mTrans, bone->position.x, bone->position.y, bone->position.z);
		bone->mWorld = mRot * mTrans;
	}
	else {
		//�e�����Ȃ��B
		D3DXMATRIX mRot, mTrans;
		D3DXMatrixRotationQuaternion(&mRot, &bone->localRotation);
		D3DXMatrixTranslation(&mTrans, bone->localPosition.x, bone->localPosition.y, bone->localPosition.z);
		bone->position = bone->localPosition;
		bone->rotation = bone->localRotation;
		bone->mWorld = mRot * mTrans;
	}
	for (auto child : bone->children) {
		CalcGlobalPose(&boneArray[child], bone);
	}
}
//�O���[�o���|�[�Y�̌v�Z�B
void Skelton::CalcGlobalPose()
{
	if (boneArray.empty()) {
		return;
	}
	Bone* root = &boneArray.front();
	D3DXMATRIX rootMatrix;
	D3DXMatrixIdentity(&rootMatrix);
	//���[�g��������Ă���
	CalcGlobalPose(root, NULL);
}
//�{�[����ǉ��B
void Skelton::AddBone(int parentNo, const Bone* bone)
{

	//�{�[���ǉ����ɂ̓O���[�o���|�[�Y���v�Z����B
	CalcGlobalPose();
	if (parentNo != -1) {
		//�{�[����ǉ��B
		boneArray.push_back(*bone);
		Bone* newBone = &boneArray.back();
		//�e�̃{�[�����擾�B
		Bone* parentBone = &boneArray[parentNo];
		int childNo = (int)boneArray.size() - 1;
		parentBone->children.push_back((int)boneArray.size()-1);
		//���[�J���|�[�Y���v�Z����B(�e�̍��W�n�ł̃|�[�Y���v�Z����B)
		D3DXMATRIX mParentWorldInv;
		D3DXMatrixInverse(&mParentWorldInv, NULL, &parentBone->mWorld);
		//�܂��͍��W�B
		//�e�̍��̃��[���h�s��̋t�s����A���̍��̃��[���h���W�ɏ�Z�����
		//�e�̍��W�n�ł̍��W�����܂�B
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &bone->position, &mParentWorldInv);
		newBone->localPosition.x = pos.x;
		newBone->localPosition.y = pos.y;
		newBone->localPosition.z = pos.z;
		
		//�����ĉ�]�B
		//��]�̍��W�Ɠ����ŁA�e�̍��̉�]�̋t�N�H�[�^�j�I�������߂āA
		//�t�N�H�[�^�j�I�����A���̃��[���h�N�H�[�^�j�I���ɏ�Z����ƁA
		//�e�̍��W�n�ł̉�]�N�H�[�^�j�I�������܂�B
		D3DXQUATERNION qParentRotInv;
		D3DXQuaternionInverse(&qParentRotInv, &parentBone->rotation);
		newBone->localRotation = newBone->rotation * qParentRotInv;
	}
	else {
		//���[�g
		boneArray.clear();
		boneArray.push_back(*bone);
		boneArray[0].localPosition = boneArray[0].position;
		boneArray[0].localRotation = boneArray[0].rotation;
	}
}
//���[���h�s����擾�B
const D3DXMATRIX* Skelton::GetWorldMatrix(int boneNo)
{
	return &boneArray[boneNo].mWorld;
}
//�{�[�����擾�B
Bone* Skelton::GetBone(int boneNo)
{
	return &boneArray[boneNo];
}