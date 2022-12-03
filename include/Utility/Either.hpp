/*****************************************************************//**
 * @file   Either.hpp
 * @brief  Eitherクラス
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_UTILITY_EITHER_HPP_
#define HENCE_UTILITY_EITHER_HPP_

#include <variant>

namespace Hence
{
	template<typename SuccessType, typename FailureType>
	class Either
	{
	public:
		using Value = std::variant<SuccessType, FailureType>;

		Either(const SuccessType& success) noexcept;
		Either(const FailureType& failure) noexcept;

		~Either() noexcept;

	    /**
		 *@brief  bool型変換オーバーロード
		 */
		explicit operator bool() const noexcept;

		/**
		 * @brief  論理否定演算子オーバーロード
		 */
		bool operator!() const noexcept;

		const SuccessType& get() const noexcept;

		const FailureType& failed() const noexcept;

	private:

		const Value mValue;

	};
}

#include "../../src/Utility/Either.inl"

#endif
