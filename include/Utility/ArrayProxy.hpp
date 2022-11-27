/*****************************************************************//**
 * @file   ArrayProxy.hpp
 * @brief  ArrayProxyクラスのヘッダファイル
 *
 *
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_UTILITY_ARRAYPROXY_HPP_
#define HENCE_UTILITY_ARRAYPROXY_HPP_

#include <cstdint>

namespace Hence
{
	/**
	 * @brief  Cスタイルの配列(ポインタ)，std::array, std::vector, std::initializer_listをひとまとめに扱えるクラス
	 * @detail Vulkan-Hppから頂いた
	 * @tparam T 要素型
	 */
	template<typename T>
	class ArrayProxy
	{

	public:
		constexpr ArrayProxy() noexcept;

		constexpr ArrayProxy(std::nullptr_t) noexcept;

		ArrayProxy(T const& value) noexcept;

		ArrayProxy(std::uint32_t count, T const* ptr) noexcept;

		template <std::size_t C>
		ArrayProxy(T const (&ptr)[C]) noexcept;

#  if __GNUC__ >= 9
#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Winit-list-lifetime"
#  endif

		ArrayProxy(std::initializer_list<T> const& list) noexcept;

		template <typename B = T, typename std::enable_if<std::is_const<B>::value, int>::type = 0>
		ArrayProxy(std::initializer_list<typename std::remove_const<T>::type> const& list) noexcept;

#if __GNUC__ >= 9
#    pragma GCC diagnostic pop
#  endif

		// Any type with a .data() return type implicitly convertible to T*, and a .size() return type implicitly
		// convertible to size_t. The const version can capture temporaries, with lifetime ending at end of statement.
		template <typename V,
			typename std::enable_if<
			std::is_convertible<decltype(std::declval<V>().data()), T*>::value&&
			std::is_convertible<decltype(std::declval<V>().size()), std::size_t>::value>::type* = nullptr>
		ArrayProxy(V const& v) noexcept;

		const T* begin() const noexcept;

		const T* end() const noexcept;

		const T& front() const noexcept;

		const T& back() const noexcept;

		bool empty() const noexcept;

		std::uint32_t size() const noexcept;

		T const* data() const noexcept;

	private:
		std::uint32_t  mCount;
		T const* mPtr;
	};

#include "../../src/Utility/ArrayProxy.inl"

}

#endif
