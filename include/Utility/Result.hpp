/*****************************************************************//**
 * @file   Result.hpp
 * @brief  Resultクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#ifndef HENCE_UTILITY_RESULT_HPP_
#define HENCE_UTILITY_RESULT_HPP_

#include <cstdint>

namespace Hence
{
	/**
	 * @brief  実行結果を表す型
	 */
	struct Result
	{
		/**
		 * @brief  デフォルトコンストラクタ，成功扱い
		 */
		Result() noexcept;

		/**
		 * @brief  エラーIDコンストラクタ，失敗扱い
		 * @param nativeError APIのエラーID(自前のエラーなら0)
		 */
		Result(const std::int32_t nativeError) noexcept;

		/**
		 * @brief  bool型変換オーバーロード
		 */
		explicit operator bool() const  noexcept;

		/**
		 * @brief  論理否定演算子オーバーロード
		 */
		bool operator!() const noexcept;

		Result operator=(Result other) noexcept;

		//! 成功したかどうか
		const bool	succeeded;
		//! ネイティブAPIのエラーID，成功した場合もしくはAPIによるエラーでない場合は0
		const std::int32_t	nativeResult;
	};
}


#endif