/*!
 *@brief	�p�b�h�B
 */
#include "stdafx.h"
#include "HID/Pad.h"
#include <limits.h>

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )  // ���̗͂V�тƂȂ�͈́B
Pad g_pad[Pad::CONNECT_PAD_MAX];		//g_pad�̒�`�B

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
*@brief	�{�^���̓��͏����X�V�B
*/
void Pad::UpdateButtonInput()
{
	//XInputState.Gamepad.wButtons�ɓ��͂��ꂽ�p�b�h�̏�񂪃r�b�g�p�^�[���Ƃ��ē����Ă���B
	//XINPUT_GAMEPAD_???�ɂ́A�Ή�����{�^���̃r�b�g�̈ʒu��1�������Ă���B
	//�Ⴆ�΁AA�{�^���͂P�R�r�b�g�ځAB�{�^���͂P�S�r�b�g�ڂɂP�����ꍇ�A
	//A��B������������Ă�����AwButtons�ɂ͉��L�̂悤�Ȓl�ɂȂ��Ă���B
	//0011 0000 0000 0000
	//�萔�AXINPUT_GAMEPAD_A�� 0001 0000 0000 0000�Ƃ����l�������Ă���̂ŁA
	//wButtons��XINPUT_GAMEPAD_A�̘_����(&)�����ƁA���L�̂悤�Ȍ��ʂƂȂ�B
	//   0011 0000 0000 0000(wButtons)
	// & 0001 0000 0000 0000(XINPUT_GAMEPAD_A)
	// = 0001 0000 0000 0000(wButtons & XINPUT_GAMEPAD_A �̌���)
	//���̂悤�ɁA�r�b�g�p�^�[���Ƙ_���ς���������ɁA0�o�Ȃ��ꍇ�͂��̃p�b�h�����͂���Ă���Ɣ��f���邱�Ƃ��ł���B

	//A�{�^����������Ă��邩����B
	if ( ( m_state.xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_A ) != 0 ) {
		if (m_press[enButtonA] == 0) {
			//1�t���[���O�͉�����Ă��Ȃ��̂ŁA�g���K�[���͂̃t���O�𗧂Ă�B
			m_trigger[enButtonA] = 1;
		}
		else {
			//1�t���[���O�ɂ�������Ă���̂ŁA�g���K�[���͂͏I���B
			m_trigger[enButtonA] = 0;
		}
		//������Ă���t���O�𗧂Ă�B
		m_press[enButtonA] = 1;

	}
	else {
		//������Ă��Ȃ��B
		m_trigger[enButtonA] = 0;
		m_press[enButtonA] = 0;
	}

	//���K 1 �c��̃{�^�������͂��Ƃ��悤�ɂ��Ă݂悤�B
	//�c��̃{�^����XINPUT_GAMEPAD_�H�H�H�͉��L�ł��B
	// �\���L�[�̏�{�^��			�@	XINPUT_GAMEPAD_DPAD_UP
	// �\���L�[�̉��{�^��			�@	XINPUT_GAMEPAD_DPAD_DOWN
	// �\���L�[�̉E�{�^��				XINPUT_GAMEPAD_DPAD_RIGHT
	// �\���L�[�̍��{�^��				XINPUT_GAMEPAD_DPAD_LEFT
	// B�{�^��							XINPUT_GAMEPAD_B
	// Y�{�^��							XINPUT_GAMEPAD_Y
	// X�{�^��							XINPUT_GAMEPAD_X
	// Back�{�^��						XINPUT_GAMEPAD_BACK
	// Start�{�^��						XINPUT_GAMEPAD_START
	// RB1�{�^��						XINPUT_GAMEPAD_RIGHT_SHOULDER
	// RB3�{�^��(R�X�e�B�b�N��������)	XINPUT_GAMEPAD_RIGHT_THUMB
	// LB1�{�^��						XINPUT_GAMEPAD_LEFT_SHOULDER
	// LB3�{�^��(L���e�B�b�N��������)	XINPUT_GAMEPAD_LEFT_THUMB


	//���g���K�[(LB2�{�^��)�̓��͔���B
	if (m_state.xInputState.Gamepad.bLeftTrigger != 0) {
		m_trigger[enButtonLB2] = 1 ^ m_press[enButtonLB2];
		m_press[enButtonLB2] = 1;
	}
	else {
		m_trigger[enButtonLB2] = 0;
		m_press[enButtonLB2] = 0;
	}
	//�E�g���K�[(RB2�{�^��)�̓��͔���B
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
*@brief	�A�i���O�X�e�B�b�N�̓��͏����X�V�B
*/
void Pad::UpdateAnalogStickInput()
{
	//xInputState.Gamepad.sThumbLX�AsThumbLY��L�X�e�B�b�N��X�����̂�Y�����̓��͏��signed short(-32,768 �` 32,767)�͈̔͂œ����Ă���B
	//���̒l��INPUT_DEADZONE�ȉ��̏ꍇ�́A���͂���Ă��Ȃ��Ƃ���B�X�e�B�b�N�̗V�тł��B
	//���ꂪ�Ȃ��Ƃ�����ƐG�ꂽ�����ŃL�����������Ă��܂��āA�C���C�����邱�ƂƂȂ�܂��B
	if ((m_state.xInputState.Gamepad.sThumbLX < INPUT_DEADZONE &&
		m_state.xInputState.Gamepad.sThumbLX > -INPUT_DEADZONE) &&
		(m_state.xInputState.Gamepad.sThumbLY < INPUT_DEADZONE &&
			m_state.xInputState.Gamepad.sThumbLY > -INPUT_DEADZONE))
	{
		//�������͂���Ă��Ȃ��Ƃ���B
		m_state.xInputState.Gamepad.sThumbLX = 0;
		m_state.xInputState.Gamepad.sThumbLY = 0;
		m_lStickX = 0.0f;
		m_lStickY = 0.0f;
	}
	else {
		//���X�e�B�b�N�̓��͗ʂ�-32,768 �` 32,767����-1.0�`1.0�ɕϊ�����B
		//�Ȃ��ϊ����邩�Ƃ����ƁA���̕����Q�[�������₷������B
		if (m_state.xInputState.Gamepad.sThumbLX > 0) {
			//SHRT_MAX��limits.h�ɒ�`����Ă���萔�ŁA32767�Ƃ����l�������Ă��܂��B
			m_lStickX = static_cast<float>(m_state.xInputState.Gamepad.sThumbLX) / SHRT_MAX;
		}
		else {
			//SHRT_MIN��limits.h�ɒ�`����Ă���萔�ŁA-32768�Ƃ����l�������Ă��܂��B
			m_lStickX = static_cast<float>(m_state.xInputState.Gamepad.sThumbLX) / -SHRT_MIN;
		}
		if (m_state.xInputState.Gamepad.sThumbLY > 0) {
			m_lStickY = static_cast<float>(m_state.xInputState.Gamepad.sThumbLY) / SHRT_MAX;
		}
		else {
			m_lStickY = static_cast<float>(m_state.xInputState.Gamepad.sThumbLY) / -SHRT_MIN;
		}
	}

	//���K�Q�@���X�e�B�b�N�̓��͂̎擾�̎d�����Q�l�ɂ��āA�E�X�e�B�b�N�����͂��Ƃ��悤�ɂ��Ă݂悤�B
}
/*!
*@brief	�p�b�h�̓��͂��X�V�B
*/
void Pad::Update()
{
	//XInputGetState�֐����g���āA�Q�[���p�b�h�̓��͏󋵂��擾����B
	DWORD result = XInputGetState(m_padNo, &m_state.xInputState);
	if (result != ERROR_SUCCESS) {
		//�Q�[���p�b�h���ڑ�����Ă��Ȃ��B
		return;
	}
	//�ڑ�����Ă���B
	m_state.bConnected = true;

	//�{�^���̓��͏����X�V�B
	UpdateButtonInput();
	
	//�A�i���O�X�e�B�b�N�̓��͏����X�V�B
	UpdateAnalogStickInput();
}

