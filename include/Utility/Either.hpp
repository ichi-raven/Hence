/*****************************************************************//**
 * @file   Either.hpp
 * @brief  Either�N���X
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

		Either(const SuccessType& success) noexcept;
		Either(const FailureType& failure) noexcept;

	    /**
		 *@brief  bool�^�ϊ��I�[�o�[���[�h
		 */
		explicit operator bool() const  noexcept;

		/**
		 * @brief  �_���ے艉�Z�q�I�[�o�[���[�h
		 */
		bool operator!() const noexcept;

		const SuccessType& get() const noexcept;

		const FailureType& failed() const noexcept;

	private:
		using Value = std::variant<SuccessType, FailureType>;

		Value mValue;
		bool mSucceeded;
	};
}

#include "../../src/Utility/Either.inl"

#endif