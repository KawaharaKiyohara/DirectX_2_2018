#include "stdafx.h"
#include "SkinModel.h"
#include "Stopwatch.h"
#include <Psapi.h>      // Psapi.Lib


/// ///////////////////////////////////////////////////////////////////
// グローバル変数。
///////////////////////////////////////////////////////////////////
HWND			g_hWnd = NULL;				//ウィンドウハンドル。
GraphicsEngine* g_graphicsEngine = NULL;	//グラフィックスエンジン。



CMatrix g_viewMatrix = CMatrix::Identity();		//ビュー行列。
CMatrix g_projMatrix = CMatrix::Identity();		//プロジェクション行列。

const int NUM_UNITY_CHAN = 1;						//ユニティちゃんの数。
SkinModel g_unityChanModel[NUM_UNITY_CHAN];	//


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
// 毎フレーム呼ばれるゲームの描画処理。
///////////////////////////////////////////////////////////////////
void Render()
{
	
	g_graphicsEngine->BegineRender();
	///////////////////////////////////////////
	CVector3 pos;
	pos.x = 475.0f;
	pos.y = 150.0f;
	CQuaternion qRot;
	qRot.SetRotationDeg(CVector3::AxisX(), -90.0f);
	for (int i = 0; i < NUM_UNITY_CHAN; i++) {
		if (i % 20 == 0 && i != 0 ) {
			pos.x = 475.0f;
			pos.y -= 80.0f;
		}
		g_unityChanModel[i].UpdateWorldMatrix(pos, qRot, CVector3::One());
		pos.x -= 50.0f;
		g_unityChanModel[i].Draw( g_viewMatrix, g_projMatrix );
	}
	//ここまでモデル表示に関係するプログラム。
	///////////////////////////////////////////
	g_graphicsEngine->EndRender();
}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	::AllocConsole();               // コマンドプロンプトが表示される
	freopen("CON", "r", stdin);     // 標準入力の割り当て
	freopen("CON", "w", stdout);    // 標準出力の割り当て

	DWORD dwProcessID = GetCurrentProcessId();

	//ウィンドウの初期化。
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);


	//DirectXの初期化。
	g_graphicsEngine = new GraphicsEngine();
	g_graphicsEngine->Init(g_hWnd);
	
	//カメラ行列を作成。
	g_viewMatrix.MakeLookAt(
		{ 0.0f, 0.0f, 500.0f },		//視点。
		{ 0.0f, 0.0f, 0.0f },		//注視点。
		{ 0.0f, 1.0f, 0.0f }		//上方向。
	);
	//プロジェクション行列を作成。
	g_projMatrix.MakeProjectionMatrix(
		CMath::DegToRad(60.0f),				//画角。
		FRAME_BUFFER_W/FRAME_BUFFER_H ,		//アスペクト比。
		1.0f,								//近平面。
		1000.0f								//遠平面。
	);
	/////////////////////////////////////////////////////////
	//モデルを初期化
	//時間計測
	Stopwatch sw;
	sw.Start();
	for (int i = 0; i < NUM_UNITY_CHAN; i++) {
		g_unityChanModel[i].Init(L"Assets/modelData/unityChan.cmo");
	}
	sw.Stop();

	printf("初期化時間　=　%f ミリ秒\n", sw.GetElapsedMillisecond());

	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc = { 0 };

	if ((hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID)) != NULL) {
		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
			printf("現在のメモリ使用量　=　%lu MB\n", pmc.WorkingSetSize / 1024 / 1024);
		}

		CloseHandle(hProcess);
	}

	
	
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
			//描画処理。
			Render();
		}
	}
	::FreeConsole();
}