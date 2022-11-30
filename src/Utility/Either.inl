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
	template<typename S, typename F>
	Either<S, F>::Either(const S& success) noexcept
		: mValue(success)
	{}

	template<typename S, typename F>
	Either<S, F>::Either(const F& failure) noexcept
		: mValue(failure)
	{}

	template<typename S, typename F>
	Either<S, F>::operator bool() const  noexcept
	{
		return mSucceeded;
	}

	template<typename S, typename F>
	bool Either<S, F>::operator!() const noexcept
	{
		return !static_cast<bool>(*this);
	}

	template<typename S, typename F>
	const S& Either<S, F>::get() const noexcept
	{
		assert(std::holds_alternative<S>(mValue) || !"failed! could not get succeeded value!");

		return std::get<S>(mValue);
	}

	template<typename S, typename F>
	const F& Either<S, F>::failed() const noexcept
	{
		assert(std::holds_alternative<F>(mValue) || !"succeeded! could not get failed value!");

		return std::get<F>(mValue);
	}

}

#endif
