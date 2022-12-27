/*****************************************************************//**
 * @file   VRAMAllocator.hpp
 * @brief  VRAMAllocatorクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_VRAMALLOCATOR_HPP_
#define HENCE_VRAMALLOCATOR_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"
#include "Info/BufferInfo.hpp"
#include "Info/ImageInfo.hpp"

namespace Hence
{
	// 前方宣言
	template<typename API>
	class Device;

	// 前方宣言
	template<typename API>
	class Buffer;

	// 前方宣言
	template<typename API>
	class Image;

	/**
	 * @brief  VRAMリソースの割り当てを管理するクラス
	 * @tparam API バックエンドに使用するAPI型(API.hpp内で定義されている)
	 */
	template<typename API>
	//requires VRAMAllocatorConcept<APITrait<API>::VRAMAllocatorImpl>
	class VRAMAllocator
	{
	public:
		using Impl = APITrait<API>::VRAMAllocatorImpl;

		/**
		 * @brief  コンストラクタ
		 * @param device 基とするデバイス
		 */
		VRAMAllocator(Device<API>& device) noexcept;

		/**
		 * @brief  デストラクタ
		 */
		~VRAMAllocator() noexcept;

		// コピー不可
		NONCOPYABLE(VRAMAllocator);

		Impl& getInternalImpl();

		///**
		// * @brief  バッファの割り当てを行う
		// * @param bci 割り当てるバッファの情報
		// */
		//Buffer<API>& allocate(const BufferInfo& bci) noexcept;

		///**
		// * @brief  画像データの割り当てを行う
		// * @param ici 割り当てる画像データの情報
		// */
		//Image<API>& allocate(const ImageInfo& ici) noexcept;

		///**
		// * @brief  バッファを解放する
		// * @param buffer 解放するバッファ
		// */
		//void deallocate(Buffer<API>& buffer) noexcept;

		///**
		// * @brief  画像データを解放する
		// * @param image 解放する画像データ
		// */
		//void deallocate(Image<API>& image) noexcept;

	private:
		using APIDevice = APITrait<API>::Device;

		//! デバイスの内部実装
		APIDevice& mAPIDevice;
		//! 内部実装
		Impl mImpl;
	};

}

#include "../src/VRAMAllocator.inl"

#endif
