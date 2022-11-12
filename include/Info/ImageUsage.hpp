/*****************************************************************//**
 * @file   ImageUsage.hpp
 * @brief  ImageUsageクラス及びその表現に関する列挙型・中間型を定義するヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_INFO_IMAGEUSAGE_HPP_
#define HENCE_INFO_IMAGEUSAGE_HPP_

#include <cstdint>
#include <utility>
#include <type_traits>

namespace Hence
{
	/**
	 * @brief  画像リソースの使用方法を示すビットフラグ
	 */
	enum class ImageUsageBit : std::int32_t
	{
		// 転送元
		TransferSRC = 0x00000001,
		// 転送先
		TransferDST = 0x00000002,
		// シェーダリソース
		Sampled = 0x00000004,
		// 任意のタイミングでのRWを許可
		Storage = 0x00000008,
		// カラーターゲットとしての描画先
		ColorAttachment = 0x00000010,
		// デプスステンシルターゲットとしての描画先
		DepthStencilAttachment = 0x00000020,
		//// 
		//TransientAttachment = 0x00000040,
		//// 
		//InputAttachment = 0x00000080,
	};

	/**
	 * @brief  ImageUsageBitのビット和による複合用途の表現用クラス(直接使用することはない)
	 */
	struct ImageUsageFlag
	{
		/**
		 * @brief  論理和用演算子オーバーロード
		 */
		ImageUsageFlag operator| (UsageFlag other) const noexcept;

		/**
		 * @brief  論理和用演算子オーバーロード(UsageBit版)
		 */
		ImageUsageFlag operator|(UsageBit bit) const noexcept;

		const std::int32_t result{};
	};

	/**
	 * @brief  ImageUsageBit同士の演算子オーバーロード
	 */
	extern ImageUsageFlag operator|(ImageUsageBit L, ImageUsageBit R) noexcept;

	/**
	 * @brief  ImageUsageFlag用UsageBitsとの演算子オーバーロード
	 */
	extern ImageUsageFlag operator|(ImageUsageBit L, ImageUsageFlag R) noexcept;

	/**
	 * @brief  UsageFlagおよびUsageBitをまとめて取り扱う型(直接構築する必要はない)
	 */
	struct ImageUsage
	{
		/**
		 * @brief  ImageUsageBitから構築するコンストラクタ
		 * @param bit ImageUsageBit型の値
		 */
		ImageUsage(ImageUsageBit bit) noexcept;

		/**
		 * @brief  ImageUsageFlagから構築するコンストラクタ
		 * @param flag ImageUsageFlag型の値
		 */
		ImageUsage(ImageUsageFlag flag) noexcept;

		/**
		 * @brief  代入演算子オーバーロード(ImageUsageBit型)
		 * @param bit ImageUsageBit型の値
		 */
		ImageUsageFlag operator=(ImageUsageBit bit) noexcept;

		/**
		 * @brief  代入演算子オーバーロード(ImageUsageFlag型)
		 * @param flag ImageUsageFlag型の値
		 */
		ImageUsageFlag operator=(ImageUsageFlag flag) noexcept;

		//! 最終的なUsage情報
		const std::int32_t usage{};
	};
}

#endif
