/*****************************************************************//**
 * @file   Usage.hpp
 * @brief  Usageクラス及びその表現に関する列挙型・中間型を定義するヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_USAGE_HPP_
#define HENCE_USAGE_HPP_

#include <cstdint>
#include <utility>

namespace Hence
{
	/**
	 * @brief  リソースの使用方法を示すビットフラグ
	 */
	enum class UsageBit : std::int32_t
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
	 * @brief  UsageBitのビット和による複合用途の表現用クラス(直接使用することはない)
	 */
	struct UsageFlag
	{
		UsageFlag operator| (UsageFlag other) const noexcept;

		UsageFlag operator|(UsageBit bit) const noexcept;

		const std::int32_t result{};
	};

	/**
	 * @brief  UsageBit同士の演算子オーバーロード
	 */
	extern UsageFlag operator|(UsageBit L, UsageBit R) noexcept;

	/**
	 * @brief  UsageFlag用UsageBitsとの演算子オーバーロード
	 */
	extern UsageFlag operator|(UsageBit L, UsageFlag R) noexcept;

	/**
	 * @brief  UsageFlagおよびUsageBitをまとめて取り扱う型(直接構築する必要はない)
	 */
	struct Usage
	{
		/**
		 * @brief  UsageBitから構築するコンストラクタ
		 * @param bit UsageBit型の値
		 */
		Usage(UsageBit bit) noexcept;

		/**
		 * @brief  UsageFlagから構築するコンストラクタ
		 * @param flag UsageFlag型の値
		 */
		Usage(UsageFlag flag) noexcept;

		//! 最終的なUsage情報
		const std::int32_t usage{};
	};
}

#endif
