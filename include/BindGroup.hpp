/*****************************************************************//**
 * @file   BindGroup.hpp
 * @brief  BindGroupクラスのヘッダファイル
 *
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#ifndef HENCE_BINDGROUP_HPP_
#define HENCE_BINDGROUP_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"
#include "Utility/Result.hpp"


#include "Device.hpp"
#include "Buffer.hpp"
#include "Image.hpp"
#include "BindLayout.hpp"

namespace Hence
{
	/**
	 * @brief シェーダ内で参照するVRAMリソースの紐づけを示す
	 * @tparam API バックエンドに使用するAPI型(API.hpp内で定義されている)
	 */
	template<typename API>
	class BindGroup
	{
	public:
		// 内部実装型(一般にユーザが使用する必要はない)
		using Impl = APITrait<API>::BindGroupImpl;

		BindGroup() noexcept;

		/**
		 * @brief  コンストラクタ
		 *
		 * @param device 基とするデバイス
		 * @param shader このシェーダのレイアウトから紐づけるリソース型を決定する
		 */
		BindGroup(Device<API>& device, BindLayout<API>& layout) noexcept;

		/**
		 * @brief  デストラクタ
		 *
		 */
		~BindGroup() noexcept;

		// コピー不可
		NONCOPYABLE(BindGroup)

		/**
		 * @brief  バッファを指定したスロットに紐づける
		 *
		 * @param slot スロット(シェーダ内のbindの値)
		 * @param buffer 紐づけるバッファ
		 * @return 結果
		 */
		void bind(std::uint8_t set, std::uint8_t binding, Buffer<API>& buffer) noexcept;

		/**
		 * @brief  画像データを指定したスロットに紐づける
		 *
		 * @param slot スロット(シェーダ内のbindの値)
		 * @param image 紐づける画像データ
		 * @return 結果
		 */
		void bind(std::uint8_t set, std::uint8_t binding, Image<API>& image) noexcept;

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
		//APIDevice* mAPIDevice;
		//! 内部実装
		std::optional<Impl> mImpl;
	};
}

#include "../src/BindGroup.inl"

#endif
