/*****************************************************************//**
 * @file   Window.hpp
 * @brief  Windowクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_WINDOW_HPP_
#define HENCE_WINDOW_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"
#include "Info/WindowInfo.hpp"

namespace Hence
{
	/**
	 * @brief  ウィンドウを表す
	 * @tparam API バックエンドに使用するAPI型(API.hpp内で定義されている)
	 */
	template<typename API>
	class Window
	{
	public:
		// 内部実装型(一般にユーザが使用する必要はない)
		using Impl = APITrait<API>::WindowImpl;

		/**
		 * @brief  コンストラクタ
		 *
		 * @param device 基とするデバイス
		 * @param WindowInfo ウィンドウの設定
		 */
		Window(Device<API>& device, const WindowInfo& info) noexcept;

		/**
		 * @brief  デストラクタ
		 */
		~Window() noexcept;

		// コピー不可
		NONCOPYABLE(Window)

		/**
		 * @brief  入力を更新する
		 */
		void updateInput() noexcept;

		/**
		 * @brief  このウィンドウがフォーカスされているか
		 * @return フォーカスされていればtrue
		 */
		bool focused() const noexcept;

		/**
		 * @brief  内部実装取得
		 * @warning 一般にユーザが使用する必要はない
		 *
		 * @return APIごとの内部実装
		 */
		Impl& getInternalImpl() noexcept;

	private:
		using APIDevice = APITrait<API>::Device;

		//! デバイスの内部実装
		APIDevice& mAPIDevice;
		//! 内部実装
		Impl mImpl;
	};
}

#include "../src/Window.inl"

#endif