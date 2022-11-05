/*****************************************************************//**
 * @file   Constants.hpp
 * @brief  ライブラリの情報を示す定数の定義
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include <cstdint>

namespace Hence
{
	//! エンジン名(API等にも渡されている)
	constexpr auto kEngineName = "Hence Graphics Library";

	//! バージョン({variant, major, minor, patch})
	constexpr std::uint8_t kVersion[4] = { 0, 0, 1, 0 };
}
