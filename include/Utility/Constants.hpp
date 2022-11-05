/*****************************************************************//**
 * @file   Constants.hpp
 * @brief  ���C�u�����̏��������萔�̒�`
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#include <cstdint>

namespace Hence
{
	//! �G���W����(API���ɂ��n����Ă���)
	constexpr auto kEngineName = "Hence Graphics Library";

	//! �o�[�W����({variant, major, minor, patch})
	constexpr std::uint8_t kVersion[4] = { 0, 0, 1, 0 };
}
