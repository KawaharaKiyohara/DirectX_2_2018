#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(CVector3 pos, CQuaternion rot, Player* player) :
	m_position(pos),
	m_rotation(rot),
	m_player(player)
{
	m_model.Init(L"Assets/modelData/enemy.cmo");
	m_charaCon.Init( 10.0f, 30.0f, m_position );
}
Enemy::~Enemy()
{
}
void Enemy::Update()
{
	if (m_state == State_Search) {
		//毎フレームちょっとづつ回す。
		CQuaternion addRot;
		//Y軸周りに0.01(ラジアン単位)回転するクォータニオンを作成する。
		addRot.SetRotation(CVector3::AxisY(), 0.01f);
		//エネミーの回転にaddRotを加算する。
		m_rotation.Multiply(addRot);

		//Hands-On 1 エネミーの視野角をプログラミングしてみる。
		//エネミーの前方方向を求める。
		//前方方向は{0, 0, 1}のベクトルをm_rotationで回して求めてみる。
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
			&& toPlayerLen < 200.0f
			) {
			//状態を追跡状態にする。
			m_state = State_Tracking;
		}
	}
	else if (m_state == State_Tracking) {
		//ここに追跡状態のプログラムを記述する。
		CVector3 toPlayer = m_player->GetPosition()- m_position;
		//toPlayerを正規化して、大きさ1にする。
		toPlayer.Normalize();
		m_moveSpeed.x = toPlayer.x * 200.0f;
		m_moveSpeed.z = toPlayer.z * 200.0f;
		m_moveSpeed.y -= 20.0f;
		m_position = m_charaCon.Execute(
							1.0f/60.0f, 
							m_moveSpeed
		);
	}
	//
	//ワールド行列を求める。
	m_model.UpdateWorldMatrix(m_position, m_rotation, { 3.0f, 3.0f, 3.0f });
}
void Enemy::Draw()
{
	m_model.Draw(g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
}
