#pragma once

#include <vector>

//ボーン。
struct Bone {
	D3DXVECTOR3			localPosition;	//ボーンのローカル座標。
	D3DXQUATERNION		localRotation;	//ボーンのローカル回転。
	D3DXVECTOR3			position;		//ボーンのグローバル座標。
	D3DXQUATERNION		rotation;		//ボーンのグローバル回転。
	std::vector<int>	children;		//子供。
	D3DXMATRIX			mWorld;			//ワールド行列、
};
class Skelton {
	std::vector<Bone>			boneArray;		//間接の配列。
public:
	Skelton();
	~Skelton();
	//グローバルポーズの計算。
	void CalcGlobalPose();
	//ボーンを追加。
	void AddBone(int parentNo, const Bone* bone);
	//ワールド行列を取得。
	const D3DXMATRIX* GetWorldMatrix(int boneNo);
	//ボーンを取得。
	Bone* GetBone(int jointNo);
private:
	void CalcGlobalPose(Bone* bone, Bone* parentBone);
};