#ifdef HENCE_UTILITY_ARRAYPROXY_HPP_

#include <cstdint>
#include <array>
#include <vector>
#include <list>
#include <cassert>

namespace Hence
{
	template <typename T>
	constexpr ArrayProxy::ArrayProxy() noexcept
		: mCount(0)
		, mPtr(nullptr)
	{}

	template <typename T>
	constexpr ArrayProxy(std::nullptr_t) noexcept
		: mCount(0)
		, mPtr(nullptr)
	{}

	template <typename T>
	ArrayProxy(T const& value) noexcept
		: mCount(1)
		, mPtr(&value)
	{}
	
	template <typename T>
	ArrayProxy(std::uint32_t count, T const* ptr) noexcept
		: mCount(count)
		, mPtr(ptr)
	{}

	template <typename T, std::size_t C>
	ArrayProxy(T const (&ptr)[C]) noexcept
		: mCount(C)
		, mPtr(ptr)
	{}

	template <typename T>
	ArrayProxy(std::initializer_list<T> const& list) noexcept
		: mCount(static_cast<std::uint32_t>(list.size()))
		, mPtr(list.begin())
	{}

	template <typename T, typename B = T, typename std::enable_if<std::is_const<B>::value, int>::type = 0>
	ArrayProxy(std::initializer_list<typename std::remove_const<T>::type> const& list) noexcept
		: mCount(static_cast<std::uint32_t>(list.size()))
		, mPtr(list.begin())
	{
	}

	// Any type with a .data() return type implicitly convertible to T*, and a .size() return type implicitly
	// convertible to size_t. The const version can capture temporaries, with lifetime ending at end of statement.
	template <typename T, typename V,
		typename std::enable_if<
		std::is_convertible<decltype(std::declval<V>().data()), T*>::value&&
		std::is_convertible<decltype(std::declval<V>().size()), std::size_t>::value>::type* = nullptr>
	ArrayProxy(V const& v) noexcept
		: mCount(static_cast<std::uint32_t>(v.size()))
		, mPtr(v.data())
	{}

	template <typename T>
	const T* begin() const noexcept
	{
		return mPtr;
	}

	template <typename T>
	const T* end() const noexcept
	{
		return mPtr + mCount;
	}

	template <typename T>
	const T& front() const noexcept
	{
		assert(mCount && mPtr);
		return *mPtr;
	}

	template <typename T>
	const T& back() const noexcept
	{
		assert(mCount && mPtr);
		return *(mPtr + mCount - 1);
	}

	template <typename T>
	bool empty() const noexcept
	{
		return (mCount == 0);
	}

	template <typename T>
	std::uint32_t size() const noexcept
	{
		return mCount;
	}

	template <typename T>
	T const* data() const noexcept
	{
		return mPtr;
	}
}

#endif