#include "stdafx.h"
#include "graphics/SkinModel.h"
#include "graphics/Skeleton.h"

//Hands-On 4.20-1 Animation.hとAnimatioinClip.hをインクルードする。
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"

///////////////////////////////////////////////////////////////////
// グローバル変数。
///////////////////////////////////////////////////////////////////
HWND			g_hWnd = NULL;				//ウィンドウハンドル。
GraphicsEngine* g_graphicsEngine = NULL;	//グラフィックスエンジン。

SkinModel g_unityChanModel;									//スキンモデル。
Animation g_unityChanAnimation;								//アニメーション。
AnimationClip g_unityChanAnimationClips[2];					//アニメーションクリップ。
CVector3 g_unityChanPosition = CVector3::Zero();			//Unityちゃんの座標。
CVector3 g_unityChanScale = CVector3::One();				//Unityちゃんの拡大率。
CQuaternion g_unityChanRotation = CQuaternion::Identity();	//Unityちゃんの回転。

CMatrix g_viewMatrix = CMatrix::Identity();	//ビュー行列。
CMatrix g_projMatrix = CMatrix::Identity();	//プロジェクション行列。
CMatrix g_worldMatrix = CMatrix::Identity();	//ワールド行列。

///////////////////////////////////////////////////////////////////
// DirectXの終了処理。
///////////////////////////////////////////////////////////////////
void ReleaseDirectX()
{
	
}
///////////////////////////////////////////////////////////////////
//メッセージプロシージャ。
//hWndがメッセージを送ってきたウィンドウのハンドル。
//msgがメッセージの種類。
//wParamとlParamは引数。今は気にしなくてよい。
///////////////////////////////////////////////////////////////////
LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//送られてきたメッセージで処理を分岐させる。
	switch (msg)
	{
	case WM_DESTROY:
		ReleaseDirectX();
		PostQuitMessage(0);
		break;	
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////
// ウィンドウの初期化。
///////////////////////////////////////////////////////////////////
void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラスのパラメータを設定(単なる構造体の変数の初期化です。)
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),		//構造体のサイズ。
		CS_CLASSDC,				//ウィンドウのスタイル。
								//ここの指定でスクロールバーをつけたりできるが、ゲームでは不要なのでCS_CLASSDCでよい。
		MsgProc,				//メッセージプロシージャ(後述)
		0,						//0でいい。
		0,						//0でいい。
		GetModuleHandle(NULL),	//このクラスのためのウインドウプロシージャがあるインスタンスハンドル。
								//何も気にしなくてよい。
		NULL,					//アイコンのハンドル。アイコンを変えたい場合ここを変更する。とりあえずこれでいい。
		NULL,					//マウスカーソルのハンドル。NULLの場合はデフォルト。
		NULL,					//ウィンドウの背景色。NULLの場合はデフォルト。
		NULL,					//メニュー名。NULLでいい。
		TEXT("Sample_01"),		//ウィンドウクラスに付ける名前。
		NULL					//NULLでいい。
	};
	//ウィンドウクラスの登録。
	RegisterClassEx(&wc);

	// ウィンドウの作成。
	g_hWnd = CreateWindow(
		TEXT("Sample_01"),		//使用するウィンドウクラスの名前。
								//先ほど作成したウィンドウクラスと同じ名前にする。
		TEXT("Sample_01"),		//ウィンドウの名前。ウィンドウクラスの名前と別名でもよい。
		WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル。ゲームでは基本的にWS_OVERLAPPEDWINDOWでいい、
		0,						//ウィンドウの初期X座標。
		0,						//ウィンドウの初期Y座標。
		(UINT)FRAME_BUFFER_W,	//ウィンドウの幅。
		(UINT)FRAME_BUFFER_H,	//ウィンドウの高さ。
		NULL,					//親ウィンドウ。ゲームでは基本的にNULLでいい。
		NULL,					//メニュー。今はNULLでいい。
		hInstance,				//アプリケーションのインスタンス。
		NULL
	);

	ShowWindow(g_hWnd, nCmdShow);

}

///////////////////////////////////////////////////////////////////
// 毎フレーム呼ばれるゲームの更新処理。
///////////////////////////////////////////////////////////////////
void Update()
{
	//ゲームパッドの更新。
	//foreachと型推論を使ってみる。
	for (auto& pad : g_pad) {
		pad.Update();
	}
	//　Aボタンが押されたら走りアニメーションを再生する。
	if ( g_pad[0].IsTrigger(enButtonA) ) {
		//走りアニメーションを再生する。
		g_unityChanAnimation.Play(1);
	}
	//Bボタンが押されたら歩きアニメーションを再生する。
	if ( g_pad[0].IsTrigger(enButtonB) ) {
		//歩きアニメーションを再生する。
		g_unityChanAnimation.Play(0);
	}

	//Xボタンが押されたら走りアニメーションを補間付きで再生する。
	if ( g_pad[0].IsTrigger(enButtonX) ) {
		//走りアニメーションを再生する。
		g_unityChanAnimation.Play(1, 0.3f);
	}
	//Yボタンが押されたら歩きアニメーションを補間付きで再生する。
	if ( g_pad[0].IsTrigger(enButtonY) ) {
		//歩きアニメーションを再生する。
		g_unityChanAnimation.Play(0, 0.3f);
	}
	//上ボタンが押されたら、UnityちゃんのY軸方向の拡大率を増やす。
	if (g_pad[0].IsPress(enButtonUp)) {
		g_unityChanScale.y += 0.01f;
	}
	//下ボタンが押されたら、UnityちゃんのY軸方向の拡大率を減らす。
	if (g_pad[0].IsPress(enButtonDown)) {
		g_unityChanScale.y -= 0.01f;
	}
	//右ボタンが押されたら、UnityちゃんのX軸方向の拡大率を増やす。
	if (g_pad[0].IsPress(enButtonRight)) {
		g_unityChanScale.x += 0.01f;
	}
	//左ボタンがおされたら、UnityちゃんのX軸方向の拡大率を減らす。
	if (g_pad[0].IsPress(enButtonLeft)) {
		g_unityChanScale.x -= 0.01f;
	}
	//上ボタンが押されたら、UnityちゃんのY軸方向の拡大率を増やす。
	if (g_pad[0].IsPress(enButtonUp)) {
		g_unityChanScale.y += 0.01f;
	}
	//下ボタンがおされたら、UnityちゃんのY軸方向の拡大率を減らす。
	if (g_pad[0].IsPress(enButtonLeft)) {
		g_unityChanScale.y -= 0.01f;
	}

	//左スティックの入力でUnityちゃんを動かす。
	g_unityChanPosition.x += g_pad[0].GetLStickXF() * 2.0f;
	g_unityChanPosition.y += g_pad[0].GetLStickYF() * 2.0f;
	//右スティックの入力でUnityちゃんを回す。
	CQuaternion qAdd;
	qAdd.SetRotationDeg(CVector3::AxisY(), g_pad[0].GetRStickXF() * 2.0f);
	g_unityChanRotation.Multiply(qAdd);	//Y軸周りの回転を加算。

	qAdd.SetRotationDeg(CVector3::AxisX(), g_pad[0].GetRStickYF() * 2.0f);
	g_unityChanRotation.Multiply(qAdd);	//X軸周りの回転を加算。


	//ワールド行列の更新。
	g_unityChanModel.UpdateWorldMatrix(g_unityChanPosition, g_unityChanRotation, g_unityChanScale);
	g_unityChanAnimation.Update(1.0f / 30.0f);
}
///////////////////////////////////////////////////////////////////
// 毎フレーム呼ばれるゲームの描画処理。
///////////////////////////////////////////////////////////////////
void Render()
{
	
	g_graphicsEngine->BegineRender();
	///////////////////////////////////////////
	//ここからモデル表示のプログラム。
	//3Dモデルを描画する。
	g_unityChanModel.Draw(g_viewMatrix, g_projMatrix);

	//ここまでモデル表示に関係するプログラム。
	///////////////////////////////////////////
	g_graphicsEngine->EndRender();
	
}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウの初期化。
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	//DirectXの初期化。
	g_graphicsEngine = new GraphicsEngine();
	g_graphicsEngine->Init(g_hWnd);
	
	//ゲームパッドの初期化。
	//最大４つのコントローラーを接続できるようにしましょう。
	g_pad[0].Init(0);
	g_pad[1].Init(1);
	g_pad[2].Init(2);
	g_pad[3].Init(3);

	//カメラ行列を作成。
	g_viewMatrix.MakeLookAt(
		{ 0.0f, 100.0f, 300.0f },	//視点。
		{ 0.0f, 100.0f, 0.0f },		//注視点。
		{ 0.0f, 1.0f, 0.0f }		//上方向。
	);
	//プロジェクション行列を作成。
	g_projMatrix.MakeProjectionMatrix(
		CMath::DegToRad(60.0f),				//画角。
		FRAME_BUFFER_W/FRAME_BUFFER_H ,		//アスペクト比。
		1.0f,								//近平面。
		10000.0f							//遠平面。
	);

	//cmoファイルの読み込み。
	g_unityChanModel.Init(L"Assets/modelData/unityChan.cmo");

	//Hands-On 4.20-3 AnimationClipをロードしてとAnimationの初期化を行う。
	//tkaファイルの読み込み。
	g_unityChanAnimationClips[0].Load(L"Assets/animData/walk.tka");
	g_unityChanAnimationClips[0].SetLoopFlag(true);

	g_unityChanAnimationClips[1].Load(L"Assets/animData/run.tka");
	g_unityChanAnimationClips[1].SetLoopFlag(true);
	//アニメーションの初期化。
	g_unityChanAnimation.Init(
		g_unityChanModel,			//アニメーションを流すスキンモデル。
									//これでアニメーションとスキンモデルが関連付けされる。
		g_unityChanAnimationClips,	//アニメーションクリップの配列。
		2							//アニメーションクリップの数。
	);
	//メッセージ構造体の変数msgを初期化。
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)	//メッセージループ
	{
		//ウィンドウからのメッセージを受け取る。
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//更新処理。
			Update();
			//描画処理。
			Render();
		}
	}
}