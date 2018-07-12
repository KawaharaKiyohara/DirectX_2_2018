#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Bullet.h"

Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo", enFbxUpAxisY);

	//tkaファイルの読み込み。
	m_animationClips[0].Load(L"Assets/animData/walk.tka");
	m_animationClips[0].SetLoopFlag(true);

	m_animationClips[1].Load(L"Assets/animData/run.tka");
	m_animationClips[1].SetLoopFlag(true);
	//アニメーションの初期化。
	m_animation.Init(
		m_model,			//アニメーションを流すスキンモデル。
							//これでアニメーションとスキンモデルが関連付けされる。
		m_animationClips,	//アニメーションクリップの配列。
		2					//アニメーションクリップの数。
	);

	m_position.y = 100.0f;
	m_charaCon.Init(10.0f, 50.0f, m_position);
}


Player::~Player()
{
}

void Player::Update()
{
	//実習課題　Bボタンを押して弾を撃ってみよう。
	//弾丸のインスタンスは下記のコードを呼び出すと作ることができる。
	//
	//	Bullet* bullet = g_game->GetBulletManager().NewBullet();
	//
	//Bulletクラスの実装は自分で読んで調べよう。
	//また、プレイヤーの回転行列はスキンモデルが持っていて下記のコードで取得できる。。
	//
	//	CMatrix rotMatrix = m_model.GetRotationMatrix();
	//
	
	if (g_pad[0].IsTrigger(enButtonA) == true
		&& m_charaCon.IsOnGround() == true
		) {
		m_moveSpeed.y += 500.0f;
	}

	//m_moveSpeedはプレイヤークラスのメンバ変数。
	//XZ平面の移動速度はパッドの入力から引っ張ってくる。
	m_moveSpeed.x = g_pad[0].GetLStickXF() * -300.0f;
	m_moveSpeed.z = g_pad[0].GetLStickYF() * -300.0f;
	//Y方向の移動速度は重力加速を行う。
	m_moveSpeed.y -= 980.0f * (1.0f / 60.0f);
	//キャラクターコントローラーに１フレームの経過時間:秒(第一引数)、時間ベースの移動速度(第二引数)を渡している。
	//Execute関数の中で行っている計算は下記のようなもの。
	//
	// CVector3 addPos = moveSpeed * ( 1.0f / 60.0f ); //１フレームで移動する量を計算する。
	// position += addPos;  //1フレームの移動量を座標に加算する。これをオイラー積分という。
	//
	m_position = m_charaCon.Execute(1.0f / 60.0f, m_moveSpeed);

	//向きも変える。
	if (fabsf(m_moveSpeed.x) > 0.1f || fabsf(m_moveSpeed.z) > 0.1f) {
		m_rotation.SetRotation(CVector3::AxisY(), atan2f(m_moveSpeed.x, m_moveSpeed.z));
	}
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	m_animation.Update(1.0f / 30.0f);
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}