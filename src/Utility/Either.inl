/*****************************************************************//**
 * @file   Either.inl
 * @brief  Eitherクラスの実装分離ファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifdef HENCE_UTILITY_EITHER_HPP_

#include <cassert>

namespace Hence
{
	template<typename SuccessType, typename FailureType>
	inline Either<SuccessType, FailureType>::Either(const SuccessType& success) noexcept
		: mValue(success)
	{}

	template<typename SuccessType, typename FailureType>
	inline Either<SuccessType, FailureType>::Either(const FailureType& failure) noexcept
		: mValue(failure)
	{}

	template<typename SuccessType, typename FailureType>
	inline Either<SuccessType, FailureType>::~Either() noexcept
	{}

	template<typename SuccessType, typename FailureType>
	inline Either<SuccessType, FailureType>::operator bool() const  noexcept
	{
		return std::holds_alternative<SuccessType>(mValue);
	}

	template<typename SuccessType, typename FailureType>
	inline bool Either<SuccessType, FailureType>::operator!() const noexcept
	{
		return !static_cast<bool>(*this);
	}

	template<typename SuccessType, typename FailureType>
	const SuccessType& Either<SuccessType, FailureType>::get() const noexcept
	{
		return std::get<0>(mValue);
	}

	template<typename SuccessType, typename FailureType>
	const FailureType& Either<SuccessType, FailureType>::failed() const noexcept
	{
		return std::get<1>(mValue);
	}

}

#endif
