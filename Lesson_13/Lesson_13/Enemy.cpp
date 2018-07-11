#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "Path.h"

using namespace std;
Enemy::Enemy(CVector3 pos, CQuaternion rot, Player* player) :
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
	m_model.Init(L"Assets/modelData/enemy.cmo");
	//パス移動中に遷移する。
	m_currentPointNo = 0;
}
Enemy::~Enemy()
{
}
bool Enemy::IsFindPlayer()
{
	CVector3 enemyForward = CVector3::AxisZ();
	m_rotation.Multiply(enemyForward);
	//エネミーからプレイヤーに伸びるベクトルを求める。
	CVector3 toPlayerDir = m_player->GetPosition() - m_position;
	//正規化を行う前に、プレイヤーまでの距離を求めておく。
	float toPlayerLen = toPlayerDir.Length();
	//正規化！
	toPlayerDir.Normalize();
	//enemyForwardとtoPlayerDirとの内積を計算する。
	float d = enemyForward.Dot(toPlayerDir);
	//内積の結果をacos関数に渡して、enemyForwardとtoPlayerDirのなす角を求める。
	float angle = acos(d);
	//視野角判定
	//fabsfは絶対値を求める関数！
	//角度はマイナスが存在するから、絶対値にする。
	if (fabsf(angle) < CMath::DegToRad(45.0f)
		&& toPlayerLen < 300.0f
		) {
		//見つけた。
		return true;
	}
	//見つけていない。
	return false;
}
//パス移動中の更新処理。
void Enemy::Update_StateMovePath()
{
	//パスを取得。
	vector< PathPoint* >& pathArray = g_game->GetPath();
	//次のポイント番号を求める。
	int nextPointNo = (m_currentPointNo + 1) % pathArray.size();
	//次のポイントに向かうベクトルを求める。
	CVector3 vNextPointDir = pathArray[nextPointNo]->position 
						- pathArray[m_currentPointNo]->position;
	//次のポイントまでの距離を計算する。
	float pathLen = vNextPointDir.Length();
	//次のポイントまでのベクトルを正規化して大きさ1にする。
	vNextPointDir.Normalize();
	//エネミーの座標を動かす。
	m_position += vNextPointDir * 2.0f;
	//移動後の座標をパスの線分上に射影する。
	CVector3 posInPath = m_position - pathArray[m_currentPointNo]->position;
	//パス上でのプレイヤーの位置を射影する。
	float t = posInPath.Dot(vNextPointDir);
	if (t > pathLen) {
		//終点超えてるね。
		m_position = pathArray[nextPointNo]->position;
		m_currentPointNo = nextPointNo;
	}
	//向きも変える。
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(vNextPointDir.x, vNextPointDir.z));

	//プレイヤの視野角判定
	if (IsFindPlayer() == true) {
		//プレイヤーを見つけた。
		//プレイヤーを追跡状態に遷移する。
		m_state = enState_FollowPlayer;
	}
}
//プレイヤーを追跡中の更新処理。
void Enemy::Update_StateFollowPlayer()
{
	CVector3 toPlayer = m_player->GetPosition() - m_position;
	float len = toPlayer.Length();
	toPlayer.Normalize();
	m_position += toPlayer * 2.0f;

	if (len > 500.0f) {
		//あきらめるパスに帰る。
		ChangeStateReturnPath();
	}
	//向きも変える。
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toPlayer.x, toPlayer.z));
}
//パスに帰還中の更新処理。
void Enemy::Update_ReturnPath()
{
	CVector3 toReturnPoint = m_returnPoint - m_startPosReturn;
	float len = toReturnPoint.Length();
	toReturnPoint.Normalize();
	m_position += toReturnPoint * 2.0f;
	CVector3 posInPath = m_position - m_startPosReturn;
	float t = posInPath.Dot(toReturnPoint);
	if (t > len) {
		//とうちゃっく。
		m_position = m_returnPoint;
		m_state = enState_MovePath;
	}
	//向きも変える。
	m_rotation.SetRotation(CVector3::AxisY(), atan2f(toReturnPoint.x, toReturnPoint.z));
}
void Enemy::ChangeStateReturnPath()
{
	//帰還開始座標を記憶しておく。
	m_startPosReturn = m_position;
	//実習 帰還先となる、m_returnPointも計算するプログラムを記述しましょう。
	//とりあえずの実装は帰還先は0番目のポイントの始点にしている。
	//もうちょっとましな実装に変更してください。
	vector<PathPoint*>& pathList = g_game->GetPath();
	m_returnPoint = pathList[0]->position;

	m_state = enState_ReturnPath;
}
void Enemy::Update()
{
	switch (m_state) {
	case enState_MovePath:
		Update_StateMovePath();
		break;
	case enState_FollowPlayer:
		Update_StateFollowPlayer();
		break;
	case enState_ReturnPath:
		Update_ReturnPath();
		break;
	}
	//ワールド行列を求める。
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 3.0f, 3.0f, 3.0f });
}
void Enemy::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}
