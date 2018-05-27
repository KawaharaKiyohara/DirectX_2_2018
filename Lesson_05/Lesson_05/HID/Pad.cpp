/*!
 *@brief	パッド。
 */
#include "stdafx.h"
#include "HID/Pad.h"
#include <limits.h>

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // 入力の遊びとなる範囲。
Pad g_pad[Pad::CONNECT_PAD_MAX];		//g_padの定義。

Pad::Pad() 
{
	memset(&m_state, 0, sizeof(m_state));
	memset(m_trigger, 0, sizeof(m_trigger));
	memset(m_press, 0, sizeof(m_press));
}
Pad::~Pad()
{
}
/*!
*@brief	ボタンの入力情報を更新。
*/
void Pad::UpdateButtonInput()
{
	//XInputState.Gamepad.wButtonsに入力されたパッドの情報がビットパターンとして入っている。
	//XINPUT_GAMEPAD_???には、対応するボタンのビットの位置に1が入っている。
	//例えば、Aボタンは１３ビット目、Bボタンは１４ビット目に１が立つ場合、
	//AとB両方が押されていたら、wButtonsには下記のような値になっている。
	//0011 0000 0000 0000
	//定数、XINPUT_GAMEPAD_Aは 0001 0000 0000 0000という値が入っているので、
	//wButtonsとXINPUT_GAMEPAD_Aの論理積(&)を取ると、下記のような結果となる。
	//   0011 0000 0000 0000(wButtons)
	// & 0001 0000 0000 0000(XINPUT_GAMEPAD_A)
	// = 0001 0000 0000 0000(wButtons & XINPUT_GAMEPAD_A の結果)
	//このように、ビットパターンと論理積を取った時に、0出ない場合はそのパッドが入力されていると判断することができる。

	//Aボタンが押されているか判定。
	if ( ( m_state.xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_A ) != 0 ) {
		if (m_press[enButtonA] == 0) {
			//1フレーム前は押されていないので、トリガー入力のフラグを立てる。
			m_trigger[enButtonA] = 1;
		}
		else {
			//1フレーム前にも押されているので、トリガー入力は終わり。
			m_trigger[enButtonA] = 0;
		}
		//押されているフラグを立てる。
		m_press[enButtonA] = 1;

	}
	else {
		//押されていない。
		m_trigger[enButtonA] = 0;
		m_press[enButtonA] = 0;
	}

	//実習 1 残りのボタンも入力をとれるようにしてみよう。
	//残りのボタンのXINPUT_GAMEPAD_？？？は下記です。
	// 十字キーの上ボタン			　	XINPUT_GAMEPAD_DPAD_UP
	// 十字キーの下ボタン			　	XINPUT_GAMEPAD_DPAD_DOWN
	// 十字キーの右ボタン				XINPUT_GAMEPAD_DPAD_RIGHT
	// 十字キーの左ボタン				XINPUT_GAMEPAD_DPAD_LEFT
	// Bボタン							XINPUT_GAMEPAD_B
	// Yボタン							XINPUT_GAMEPAD_Y
	// Xボタン							XINPUT_GAMEPAD_X
	// Backボタン						XINPUT_GAMEPAD_BACK
	// Startボタン						XINPUT_GAMEPAD_START
	// RB1ボタン						XINPUT_GAMEPAD_RIGHT_SHOULDER
	// RB3ボタン(Rスティック押し込み)	XINPUT_GAMEPAD_RIGHT_THUMB
	// LB1ボタン						XINPUT_GAMEPAD_LEFT_SHOULDER
	// LB3ボタン(L私ティック押し込み)	XINPUT_GAMEPAD_LEFT_THUMB


	//左トリガー(LB2ボタン)の入力判定。
	if (m_state.xInputState.Gamepad.bLeftTrigger != 0) {
		m_trigger[enButtonLB2] = 1 ^ m_press[enButtonLB2];
		m_press[enButtonLB2] = 1;
	}
	else {
		m_trigger[enButtonLB2] = 0;
		m_press[enButtonLB2] = 0;
	}
	//右トリガー(RB2ボタン)の入力判定。
	if (m_state.xInputState.Gamepad.bRightTrigger != 0) {
		m_trigger[enButtonRB2] = 1 ^ m_press[enButtonRB2];
		m_press[enButtonRB2] = 1;
	}
	else {
		m_trigger[enButtonRB2] = 0;
		m_press[enButtonRB2] = 0;
	}
}
/*!
*@brief	アナログスティックの入力情報を更新。
*/
void Pad::UpdateAnalogStickInput()
{
	//xInputState.Gamepad.sThumbLX、sThumbLYにLスティックのX方向のとY方向の入力情報がsigned short(-32,768 ～ 32,767)の範囲で入っている。
	//この値がINPUT_DEADZONE以下の場合は、入力されていないとする。スティックの遊びです。
	//これがないとちょっと触れただけでキャラが動いてしまって、イライラすることとなります。
	if ((m_state.xInputState.Gamepad.sThumbLX < INPUT_DEADZONE &&
		m_state.xInputState.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
		(m_state.xInputState.Gamepad.sThumbLY < INPUT_DEADZONE &&
			m_state.xInputState.Gamepad.sThumbLY > -INPUT_DEADZONE))
	{
		//何も入力されていないとする。
		m_state.xInputState.Gamepad.sThumbLX = 0;
		m_state.xInputState.Gamepad.sThumbLY = 0;
		m_lStickX = 0.0f;
		m_lStickY = 0.0f;
	}
	else {
		//左スティックの入力量を-32,768 ～ 32,767から-1.0～1.0に変換する。
		//なぜ変換するかというと、その方がゲームを作りやすいから。
		if (m_state.xInputState.Gamepad.sThumbLX > 0) {
			//SHRT_MAXはlimits.hに定義されている定数で、32767という値が入っています。
			m_lStickX = static_cast<float>(m_state.xInputState.Gamepad.sThumbLX) / SHRT_MAX;
		}
		else {
			//SHRT_MINはlimits.hに定義されている定数で、-32768という値が入っています。
			m_lStickX = static_cast<float>(m_state.xInputState.Gamepad.sThumbLX) / -SHRT_MIN;
		}
		if (m_state.xInputState.Gamepad.sThumbLY > 0) {
			m_lStickY = static_cast<float>(m_state.xInputState.Gamepad.sThumbLY) / SHRT_MAX;
		}
		else {
			m_lStickY = static_cast<float>(m_state.xInputState.Gamepad.sThumbLY) / -SHRT_MIN;
		}
	}

	//実習２　左スティックの入力の取得の仕方を参考にして、右スティックも入力をとれるようにしてみよう。
}
/*!
*@brief	パッドの入力を更新。
*/
void Pad::Update()
{
	//XInputGetState関数を使って、ゲームパッドの入力状況を取得する。
	DWORD result = XInputGetState(m_padNo, &m_state.xInputState);
	if (result != ERROR_SUCCESS) {
		//ゲームパッドが接続されていない。
		return;
	}
	//接続されている。
	m_state.bConnected = true;

	//ボタンの入力情報を更新。
	UpdateButtonInput();
	
	//アナログスティックの入力情報を更新。
	UpdateAnalogStickInput();
}

