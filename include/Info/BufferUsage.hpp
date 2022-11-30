/*****************************************************************//**
 * @file   BufferUsage.hpp
 * @brief  BufferUsageクラス及びその表現に関する列挙型・中間型を定義するヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_INFO_BUFFERUSAGE_HPP_
#define HENCE_INFO_BUFFERUSAGE_HPP_

#include <cstdint>
#include <utility>
#include <type_traits>

namespace Hence
{
	/**
	 * @brief  画像リソースの使用方法を示すビットフラグ
	 */
	enum class BufferUsageBit : std::int32_t
	{
		Uniform = 0x00000010,
		Index	= 0x00000040,
		Vertex	= 0x00000080,
	};

	/**
	 * @brief  BufferUsageBitのビット和による複合用途の表現用クラス(直接使用することはない)
	 */
	struct BufferUsageFlag
	{
		BufferUsageFlag(const std::int32_t res);

		/**
		 * @brief  論理和用演算子オーバーロード
		 */
		BufferUsageFlag operator| (BufferUsageFlag other) const noexcept;

		/**
		 * @brief  論理和用演算子オーバーロード(UsageBit版)
		 */
		BufferUsageFlag operator|(BufferUsageBit bit) const noexcept;

		const std::int32_t result{};
	};

	/**
	 * @brief  BufferUsageBit同士の演算子オーバーロード
	 */
	extern BufferUsageFlag operator|(BufferUsageBit L, BufferUsageBit R) noexcept;

	/**
	 * @brief  BufferUsageFlag用UsageBitsとの演算子オーバーロード
	 */
	extern BufferUsageFlag operator|(BufferUsageBit L, BufferUsageFlag R) noexcept;

	/**
	 * @brief  UsageFlagおよびUsageBitをまとめて取り扱う型(直接構築する必要はない)
	 */
	struct BufferUsage
	{
		/**
		 * @brief  BufferUsageBitから構築するコンストラクタ
		 * @param bit BufferUsageBit型の値
		 */
		BufferUsage(BufferUsageBit bit) noexcept;

		/**
		 * @brief  BufferUsageFlagから構築するコンストラクタ
		 * @param flag BufferUsageFlag型の値
		 */
		BufferUsage(BufferUsageFlag flag) noexcept;

		/**
		 * @brief  代入演算子オーバーロード(BufferUsageBit型)
		 * @param bit BufferUsageBit型の値
		 */
		BufferUsageFlag operator=(BufferUsageBit bit) noexcept;

		/**
		 * @brief  代入演算子オーバーロード(BufferUsageFlag型)
		 * @param flag BufferUsageFlag型の値
		 */
		BufferUsageFlag operator=(BufferUsageFlag flag) noexcept;

		/**
		 * @brief  そのusageを含んでいるか判定する
		 * @param  checkUsage 含んでいるか判定するBufferUsageBit
		 * @return 含んでいればtrue
		 */
		bool contains(BufferUsageBit checkUsageBit) const noexcept;

		//! 最終的なUsage情報
		std::int32_t usage{};
	};
}

#endif
