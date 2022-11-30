#ifdef HENCE_UTILITY_ARRAYPROXY_HPP_

#include <cstdint>
#include <array>
#include <vector>
#include <list>
#include <cassert>

namespace Hence
{
	template <typename T>
	constexpr ArrayProxy<T>::ArrayProxy() noexcept
		: mCount(0)
		, mPtr(nullptr)
	{}

	template <typename T>
	constexpr ArrayProxy<T>::ArrayProxy(std::nullptr_t dummy) noexcept
		: mCount(0)
		, mPtr(nullptr)
	{}

	template <typename T>
	ArrayProxy<T>::ArrayProxy(T const& value) noexcept
		: mCount(1)
		, mPtr(&value)
	{}
	
	template <typename T>
	ArrayProxy<T>::ArrayProxy(std::uint32_t count, T const* ptr) noexcept
		: mCount(count)
		, mPtr(ptr)
	{}

	template<typename T>
	template <std::size_t C>
	ArrayProxy<T>::ArrayProxy(T const (&ptr)[C]) noexcept
		: mCount(C)
		, mPtr(ptr)
	{}

#  if __GNUC__ >= 9
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Winit-list-lifetime"
#  endif

	template <typename T>
	ArrayProxy<T>::ArrayProxy(std::initializer_list<T> const& list) noexcept
		: mCount(static_cast<std::uint32_t>(list.size()))
		, mPtr(list.begin())
	{}

	template<typename T>
	template <typename B, typename std::enable_if<std::is_const<B>::value, int>::type>
	ArrayProxy<T>::ArrayProxy(std::initializer_list<typename std::remove_const<T>::type> const& list) noexcept
		: mCount(static_cast<std::uint32_t>(list.size()))
		, mPtr(list.begin())
	{
	}

#if __GNUC__ >= 9
#    pragma GCC diagnostic pop
#  endif

	// Any type with a .data() return type implicitly convertible to T*, and a .size() return type implicitly
	// convertible to size_t. The const version can capture temporaries, with lifetime ending at end of statement.
	template<typename T>
	template <typename V,
		typename std::enable_if<
		std::is_convertible<decltype(std::declval<V>().data()), T*>::value&&
		std::is_convertible<decltype(std::declval<V>().size()), std::size_t>::value>::type*>
	ArrayProxy<T>::ArrayProxy(V const& v) noexcept
		: mCount(static_cast<std::uint32_t>(v.size()))
		, mPtr(v.data())
	{}

	template <typename T>
	const T* ArrayProxy<T>::begin() const noexcept
	{
		return mPtr;
	}

	template <typename T>
	const T* ArrayProxy<T>::end() const noexcept
	{
		return mPtr + mCount;
	}

	template <typename T>
	const T& ArrayProxy<T>::front() const noexcept
	{
		assert(mCount && mPtr);
		return *mPtr;
	}

	template <typename T>
	const T& ArrayProxy<T>::back() const noexcept
	{
		assert(mCount && mPtr);
		return *(mPtr + mCount - 1);
	}

	template <typename T>
	bool ArrayProxy<T>::empty() const noexcept
	{
		return (mCount == 0);
	}

	template <typename T>
	std::uint32_t ArrayProxy<T>::size() const noexcept
	{
		return mCount;
	}

	template <typename T>
	T const* ArrayProxy<T>::data() const noexcept
	{
		return mPtr;
	}
}

#endif