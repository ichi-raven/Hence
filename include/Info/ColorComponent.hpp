/*****************************************************************//**
 * @file   ColorComponent.hpp
 * @brief  ColorComponentクラスのヘッダファイルクラス及びその表現に関する列挙型・中間型を定義するヘッダファイル
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/
#ifndef HENCE_INFO_COLORCOMPONENT_HPP_
#define HENCE_INFO_COLORCOMPONENT_HPP_

#include <cstdint>
#include <utility>
#include <type_traits>

namespace Hence
{
	/**
	 * @brief  使用する色チャネルを示すビットフラグ
	 */
	enum class ColorComponentBit : std::int32_t
	{
		R = 0x00000001,
		G = 0x00000002,
		B = 0x00000004,
		A = 0x00000008,
	};

	/**
	 * @brief  ColorComponentBitのビット和による複合用途の表現用クラス(直接使用することはない)
	 */
	struct ColorComponentFlag
	{
		ColorComponentFlag(const std::int32_t res);

		/**
		 * @brief  論理和用演算子オーバーロード
		 */
		ColorComponentFlag operator| (ColorComponentFlag other) const noexcept;

		/**
		 * @brief  論理和用演算子オーバーロード(UsageBit版)
		 */
		ColorComponentFlag operator|(ColorComponentBit bit) const noexcept;

		const std::int32_t result{};
	};

	/**
	 * @brief  ColorComponentBit同士の演算子オーバーロード
	 */
	extern ColorComponentFlag operator|(ColorComponentBit L, ColorComponentBit R) noexcept;

	/**
	 * @brief  ColorComponentFlag用UsageBitsとの演算子オーバーロード
	 */
	extern ColorComponentFlag operator|(ColorComponentBit L, ColorComponentFlag R) noexcept;

	/**
	 * @brief  UsageFlagおよびUsageBitをまとめて取り扱う型(直接構築する必要はない)
	 */
	struct ColorComponent
	{
		/**
		 * @brief  ColorComponentBitから構築するコンストラクタ
		 * @param bit ColorComponentBit型の値
		 */
		ColorComponent(ColorComponentBit bit) noexcept;

		/**
		 * @brief  ColorComponentFlagから構築するコンストラクタ
		 * @param flag ColorComponentFlag型の値
		 */
		ColorComponent(ColorComponentFlag flag) noexcept;

		/**
		 * @brief  代入演算子オーバーロード(ColorComponentBit型)
		 * @param bit ColorComponentBit型の値
		 */
		ColorComponentFlag operator=(ColorComponentBit bit) noexcept;

		/**
		 * @brief  代入演算子オーバーロード(ColorComponentFlag型)
		 * @param flag ColorComponentFlag型の値
		 */
		ColorComponentFlag operator=(ColorComponentFlag flag) noexcept;

		/**
		 * @brief  そのusageを含んでいるか判定する
		 * @param  check 含んでいるか判定するColorComponentBit
		 * @return 含んでいればtrue
		 */
		bool contains(ColorComponentBit checkBit) const noexcept;

		//! 最終的な値
		std::int32_t bitFlag{};
	};
}

#endif
