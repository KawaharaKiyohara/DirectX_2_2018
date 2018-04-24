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
		//親がいる。
		//ローカル座標に親の行列を乗算して、ワールド座標に変換する。
		D3DXVec3Transform(&pos, &bone->localPosition, &parentBone->mWorld);
		bone->position.x = pos.x;
		bone->position.y = pos.y;
		bone->position.z = pos.z;

		//ローカル回転に親の回転を加えて、ワールド回転に変換する。
		bone->rotation = bone->localRotation * parentBone->rotation;

		//ワールド行列を計算する。
		D3DXMATRIX mRot, mTrans;
		D3DXMatrixRotationQuaternion(&mRot, &bone->rotation);
		D3DXMatrixTranslation(&mTrans, bone->position.x, bone->position.y, bone->position.z);
		bone->mWorld = mRot * mTrans;
	}
	else {
		//親がいない。
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
//グローバルポーズの計算。
void Skelton::CalcGlobalPose()
{
	if (boneArray.empty()) {
		return;
	}
	Bone* root = &boneArray.front();
	D3DXMATRIX rootMatrix;
	D3DXMatrixIdentity(&rootMatrix);
	//ルートから潜っていく
	CalcGlobalPose(root, NULL);
}
//ボーンを追加。
void Skelton::AddBone(int parentNo, const Bone* bone)
{

	//ボーン追加時にはグローバルポーズを計算する。
	CalcGlobalPose();
	if (parentNo != -1) {
		//ボーンを追加。
		boneArray.push_back(*bone);
		Bone* newBone = &boneArray.back();
		//親のボーンを取得。
		Bone* parentBone = &boneArray[parentNo];
		int childNo = (int)boneArray.size() - 1;
		parentBone->children.push_back((int)boneArray.size()-1);
		//ローカルポーズを計算する。(親の座標系でのポーズを計算する。)
		D3DXMATRIX mParentWorldInv;
		D3DXMatrixInverse(&mParentWorldInv, NULL, &parentBone->mWorld);
		//まずは座標。
		//親の骨のワールド行列の逆行列を、この骨のワールド座標に乗算すると
		//親の座標系での座標が求まる。
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &bone->position, &mParentWorldInv);
		newBone->localPosition.x = pos.x;
		newBone->localPosition.y = pos.y;
		newBone->localPosition.z = pos.z;
		
		//続いて回転。
		//回転の座標と同じで、親の骨の回転の逆クォータニオンを求めて、
		//逆クォータニオンを、骨のワールドクォータニオンに乗算すると、
		//親の座標系での回転クォータニオンが求まる。
		D3DXQUATERNION qParentRotInv;
		D3DXQuaternionInverse(&qParentRotInv, &parentBone->rotation);
		newBone->localRotation = newBone->rotation * qParentRotInv;
	}
	else {
		//ルート
		boneArray.clear();
		boneArray.push_back(*bone);
		boneArray[0].localPosition = boneArray[0].position;
		boneArray[0].localRotation = boneArray[0].rotation;
	}
}
//ワールド行列を取得。
const D3DXMATRIX* Skelton::GetWorldMatrix(int boneNo)
{
	return &boneArray[boneNo].mWorld;
}
//ボーンを取得。
Bone* Skelton::GetBone(int boneNo)
{
	return &boneArray[boneNo];
}