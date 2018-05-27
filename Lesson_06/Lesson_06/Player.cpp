#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");

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
}


Player::~Player()
{
}

void Player::Update()
{
	
	//　Aボタンが押されたら走りアニメーションを再生する。
	if (g_pad[0].IsTrigger(enButtonA)) {
		//走りアニメーションを再生する。
		m_animation.Play(1);
	}
	//Bボタンが押されたら歩きアニメーションを再生する。
	if (g_pad[0].IsTrigger(enButtonB)) {
		//歩きアニメーションを再生する。
		m_animation.Play(0);
	}

	//Xボタンが押されたら走りアニメーションを補間付きで再生する。
	if (g_pad[0].IsTrigger(enButtonX)) {
		//走りアニメーションを再生する。
		m_animation.Play(1, 0.3f);
	}
	//Yボタンが押されたら歩きアニメーションを補間付きで再生する。
	if (g_pad[0].IsTrigger(enButtonY)) {
		//歩きアニメーションを再生する。
		m_animation.Play(0, 0.3f);
	}
	//上ボタンが押されたら、UnityちゃんのY軸方向の拡大率を増やす。
	if (g_pad[0].IsPress(enButtonUp)) {
		m_scale.y += 0.01f;
	}
	//下ボタンが押されたら、UnityちゃんのY軸方向の拡大率を減らす。
	if (g_pad[0].IsPress(enButtonDown)) {
		m_scale.y -= 0.01f;
	}
	//右ボタンが押されたら、UnityちゃんのX軸方向の拡大率を増やす。
	if (g_pad[0].IsPress(enButtonRight)) {
		m_scale.x += 0.01f;
	}
	//左ボタンがおされたら、UnityちゃんのX軸方向の拡大率を減らす。
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_scale.x -= 0.01f;
	}
	//上ボタンが押されたら、UnityちゃんのY軸方向の拡大率を増やす。
	if (g_pad[0].IsPress(enButtonUp)) {
		m_scale.y += 0.01f;
	}
	//下ボタンがおされたら、UnityちゃんのY軸方向の拡大率を減らす。
	if (g_pad[0].IsPress(enButtonLeft)) {
		m_scale.y -= 0.01f;
	}

	//左スティックの入力でUnityちゃんを動かす。
	m_position.x += g_pad[0].GetLStickXF() * 2.0f;
	m_position.y += g_pad[0].GetLStickYF() * 2.0f;
	//右スティックの入力でUnityちゃんを回す。
	CQuaternion qAdd;
	qAdd.SetRotationDeg(CVector3::AxisY(), g_pad[0].GetRStickXF() * 2.0f);
	m_rotation.Multiply(qAdd);	//Y軸周りの回転を加算。

	qAdd.SetRotationDeg(CVector3::AxisX(), g_pad[0].GetRStickYF() * 2.0f);
	m_rotation.Multiply(qAdd);	//X軸周りの回転を加算。


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