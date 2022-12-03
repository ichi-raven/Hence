/*****************************************************************//**
 * @file   HelperFunctions.hpp
 * @brief  Vulkan�p�w���p�֐��̐錾�w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   December 2022
 *********************************************************************/

#include <vulkan/vulkan.hpp>

#include "../../../Utility/Result.hpp"

namespace Hence
{
	Result setImageMemoryBarrier(VkCommandBuffer command, VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout, VkImageAspectFlags aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT) noexcept;
}
