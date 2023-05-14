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
#include "Utility/Result.hpp"
#include "Info/WindowInfo.hpp"

namespace Hence
{
	template<typename API>
	class Semaphore;

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

		Window() noexcept;

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
		 * @brief 利用可能なフレームバッファのインデックスを返す(このフレームバッファを使う)
		 *  
		 * @return 次のフレームバッファのインデックス
		 */
		std::uint32_t acquireNextImage(Semaphore<API>& signalSemaphore) noexcept;

		/**
		 * @brief  描画が完了したフレームバッファをウィンドウに表示する
		 * @param frameBufferIndex 描画対象としたフレームバッファのインデックス(acquireNextImageで取得できるもの)
		 * @param waitSemaphore そのフレームバッファに描画を行っているコマンドの終了を通知するセマフォ(描画処理が終わっていないのに表示はできない)
		 * @return 表示に成功したかどうか
		*/
		Result present(const std::uint32_t frameBufferIndex, Semaphore<API>& waitSemaphore) noexcept;

		/**
		 * @brief  内部実装取得
		 * @warning 一般にユーザが使用する必要はない
		 *
		 * @return APIごとの内部実装
		 */
		Impl& getInternalImpl() noexcept;

	private:
		//using APIDevice = APITrait<API>::Device;

		//! デバイスの内部実装
		//APIDevice& mAPIDevice;
		//! 内部実装
		std::optional<Impl> mImpl;
	};
}

#include "../src/Window.inl"

#endif