/*!
 *@brief	シェーダーのチュートリアル00
 */
#include "stdafx.h"
#include "Camera.h"
#include "Ball.h"
#include "Skelton.h"

//-----------------------------------------------------------------------------
// グローバル変数。
//-----------------------------------------------------------------------------

const int				LIGHT_NUM = 4;
D3DXVECTOR4 			g_diffuseLightDirection[LIGHT_NUM];	//ライトの方向。
D3DXVECTOR4				g_diffuseLightColor[LIGHT_NUM];		//ライトの色。
D3DXVECTOR4				g_ambientLight;						//環境光

Camera camera;				//カメラ。

const int NUM_BALL = 7;
Ball ball[NUM_BALL];	//ボール。
Skelton ballSkelton;	//ボールのスケルトン。

enum EBone {
	eBonePelvis,
	eBoneLeftFoot ,
	eBoneRightFoot ,
	eBoneBody,
	eBoneHead,
	eBoneLeftHand,
	eBoneRightHand,
};
/*!-----------------------------------------------------------------------------
 *@brief	ライトを更新。
 -----------------------------------------------------------------------------*/
void UpdateLight()
{
	g_diffuseLightDirection[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	//ディフューズライト。
	g_diffuseLightColor[0] = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

//環境光。
g_ambientLight = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);
}
//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	//ライトを初期化。
	ZeroMemory(g_diffuseLightDirection, sizeof(g_diffuseLightDirection));
	ZeroMemory(g_diffuseLightColor, sizeof(g_diffuseLightColor));


	//スケルトンを構築。
	//Lesson 1	スケルトンの構築について説明する。
	//骨盤　これがルート
	Bone bone;
	D3DXQuaternionIdentity(&bone.rotation);
	bone.position.x = 0.0f;
	bone.position.y = 0.0f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(-1, &bone);
	//左足
	bone.position.x = -0.5f;
	bone.position.y = -0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(0, &bone);
	//右足。
	bone.position.x = 0.5f;
	bone.position.y = -0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(0, &bone);
	//胴体
	bone.position.x = 0.0f;
	bone.position.y = 0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(0, &bone);
	//頭
	bone.position.x = 0.0f;
	bone.position.y = 1.0f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(3, &bone);
	//左手
	bone.position.x = -0.5f;
	bone.position.y = 0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(3, &bone);
	//右足
	bone.position.x = 0.5f;
	bone.position.y = 0.5f;
	bone.position.z = 0.0f;
	ballSkelton.AddBone(3, &bone);


	//ボールを初期化。
	for (int i = 0; i < NUM_BALL; i++) {
		ball[i].Init(&ballSkelton, i);
	}
	//カメラの初期化。
	camera.Init();

}
//-----------------------------------------------------------------------------
// Name: 描画処理。
//-----------------------------------------------------------------------------
VOID Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();
	//トラを描画。
	for (int i = 0; i < NUM_BALL; i++) {
		ball[i].Render(
			g_pd3dDevice,
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			g_diffuseLightDirection,
			g_diffuseLightColor,
			g_ambientLight,
			LIGHT_NUM
			);
	}

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	更新処理。
 -----------------------------------------------------------------------------*/
void Update()
{
	//ライトの更新。
	UpdateLight();
	//カメラの更新
	camera.Update();
	//Lesson-2 CalcGlobalPoseについて説明する。
	//グローバルポーズの更新
	ballSkelton.CalcGlobalPose();
	
	//Hands-On 1 ボーンを動かす。
	//胴体を動かす
	if (GetAsyncKeyState('W')){
		Bone* bone = ballSkelton.GetBone(eBoneBody);
		bone->localPosition.y += 0.01f;
	}
	if (GetAsyncKeyState('S')) {
		Bone* bone = ballSkelton.GetBone(eBoneBody);
		bone->localPosition.y -= 0.01f;
	}
	//Hands-On 2 ボーンを回す。
	static float angle = 0.0f;
	//骨盤を回す。
	if (GetAsyncKeyState('A')) {
		Bone* bone = ballSkelton.GetBone(eBonePelvis);
		D3DXQuaternionRotationAxis(&bone->localRotation, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), angle);
		angle+=0.01f;
	}
	if (GetAsyncKeyState('D')) {
		Bone* bone = ballSkelton.GetBone(eBonePelvis);
		D3DXQuaternionRotationAxis(&bone->localRotation, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), angle);
		angle -= 0.01f;
	}
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
}
