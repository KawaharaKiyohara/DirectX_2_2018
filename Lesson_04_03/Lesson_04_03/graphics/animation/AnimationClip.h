/*!
 *@brief	アニメーションクリップ。
 */

#pragma once


/*!
*@brief	アニメーションクリップのヘッダー。
*/
struct AnimClipHeader {
	std::uint32_t numKey;				//!<キーフレームの数。
	std::uint32_t numAnimationEvent;	//!<アニメーションイベントの数。
};
/*!
*@brief	アニメーションイベント
*@アニメーションイベントは未対応。
* やりたかったら自分で実装するように。
*/
struct AnimationEventData {
	float	invokeTime;					//!<アニメーションイベントが発生する時間(単位:秒)
	std::uint32_t eventNameLength;		//!<イベント名の長さ。
};
/*!
*@brief	キーフレーム。
*/
struct Keyframe {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	CMatrix transform;			//!<トランスフォーム。
};
/*!
*@brief	キーフレーム。
*/
struct KeyframeRow {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	CVector3 transform[4];		//!<トランスフォーム。
};

/*!
*@brief	アニメーションクリップ。
*/
class AnimationClip  {
public:
	/*!
		*@brief	ボーンのフリーズ情報。
		*/
	struct SFreezeBoneInfo {
		int boneNo;		//!<フリーズさせるボーン番号。
		bool freezeX;	//!<X方向の移動をフリーズさせる？
		bool freezeY;	//!<Y方向の移動をフリーズさせる？
		bool freezeZ;	//!<Z方向の移動をフリーズさせる？
	};
	typedef std::vector<Keyframe*>		keyFramePtrList;
	/*!
	* @brief	コンストラクタ
	*/
	AnimationClip() 
	{
	}
	/*!
		*@brief	デストラクタ。
		*/
	~AnimationClip();
	/*!
		*@brief	アニメーションクリップをロード。
		*@param[in]	filePath	ファイルパス。
		*@param[in]	clipName	クリップ名。
		*/
	void Load(const wchar_t* filePath, const wchar_t* cliipName = nullptr);

	/*!
	*@brief	ループする？
	*/
	bool IsLoop() const
	{
		return m_isLoop;
	}
	/*!
	*@brief	ループフラグを設定する。
	*/
	void SetLoopFlag(bool flag)
	{
		m_isLoop = flag;
	}
	/*!
	*@brief
	*/
	const std::vector<keyFramePtrList>& GetKeyFramePtrListArray() const
	{
		return m_keyFramePtrListArray;
	}
	const keyFramePtrList& GetTopBoneKeyFrameList() const
	{
		return *m_topBoneKeyFramList;
	}
	/*!
	*@brief	クリップ名を取得。
	*/
	const wchar_t* GetName() const
	{
		return m_clipName.c_str();
	}
	
	/*!
	*@brief	アニメーションクリップはロード済み？
	*/
	bool IsLoaded() const
	{
		return m_loaded;
	}
private:
	using KeyframePtr = std::unique_ptr<Keyframe>;
	std::wstring m_clipName;	//!<アニメーションクリップの名前。
	bool m_isLoop = false;	//!<ループフラグ。
	std::vector<KeyframePtr>		m_keyframes;				//キーフレーム。
	std::vector<keyFramePtrList>	m_keyFramePtrListArray;		//ボーンごとのキーフレームのリストを管理するための配列。
	keyFramePtrList*				m_topBoneKeyFramList = nullptr;
	bool m_loaded = false;	//アニメーションクリップがロードされている？
};
using AnimationClipPtr = std::unique_ptr<AnimationClip>;
