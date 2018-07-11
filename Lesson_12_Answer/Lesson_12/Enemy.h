#pragma once

class Player;
struct PathPoint;

class Enemy
{
public:
	Enemy( CVector3 pos, CQuaternion rot, Player* player);
	~Enemy();
	void Update();
	void Draw();
private:
	//パス移動中の更新処理。
	void Update_StateMovePath();
	//プレイヤーを追跡中の更新処理。
	void Update_StateFollowPlayer();
	//パスに帰還中の更新処理。
	void Update_ReturnPath();
	//プレイヤーを発見した？
	bool IsFindPlayer();
	//帰還状態に遷移。
	void ChangeStateReturnPath();
private:
	//ステート。
	enum EnState {
		enState_MovePath,		//パス上を移動中。
		enState_FollowPlayer,	//プレイヤーを追跡中。
		enState_ReturnPath,		//パスに帰還中。
	};
	CVector3 m_returnPoint = CVector3::Zero();			//帰還座標。
	CVector3 m_startPosReturn = CVector3::Zero();		//帰還を開始したときの開始座標。
	CVector3 m_position = CVector3::Zero();				//座標。
	CQuaternion m_rotation = CQuaternion::Identity();	//回転。
	SkinModel m_model;									//モデル。
	Player* m_player = nullptr;
	EnState m_state = enState_MovePath;					//パス移動中。
	int m_currentPointNo = 0;	
};

