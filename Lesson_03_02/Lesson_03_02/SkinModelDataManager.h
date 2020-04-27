#pragma once
#include <map>

/*!
*@brief	スキンモデルデータマネージャー。。
*/
class SkinModelDataManager
{
public:
	/*!
	*@brief	モデルをロード。
	*@param[in]	filePath	ファイルパス。
	*/
	DirectX::Model* Load(const wchar_t* filePath);
	/*!
	*@brief	モデルデータを全開放。
	*/
	void Release();
private:
	//ファイルパスをキー、DirectXModelのインスタンスを値とするマップ。
	//辞書みたいなものです。
	map< wstring, DirectX::ModelPtr > m_directXModelMap;
};

//g_skinModelDataManagerのextern宣言。
//extern宣言は実態ではないので注意！
//コンパイラにどこかにあるから使ってねと教えるもの。
extern SkinModelDataManager g_skinModelDataManager;

