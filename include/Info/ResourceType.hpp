/*****************************************************************//**
 * @file   ResourceType.hpp
 * @brief  ResourceType列挙型のヘッダファイル
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/
#ifndef HENCE_INCLUDE_INFO_RESOURCETYPE_HPP_
#define HENCE_INCLUDE_INFO_RESOURCETYPE_HPP_

#include <cstdint>


namespace Hence
{
    enum class ResourceType : std::int32_t
	{
        Sampler = 0,
        CombinedImageSampler = 1,
        SampledImage = 2,
        StorageImage = 3,
        UniformTexelBuffer = 4,
        StorageTexelBuffer = 5,
        UniformBuffer = 6,
        StorageBuffer = 7,
        UniformBufferDynamic = 8,
        StorageBufferDynamic = 9,
        InputAttachment = 10,
        // Provided by VK_VERSION_1_3
        InlineUniformBlock = 1000138000,
        // Provided by VK_KHR_acceleration_structure
        AccelerationStructure = 1000150000,
        // Provided by VK_NV_ray_tracing
        AccelerationStructureNV = 1000165000,
        // Provided by VK_QCOM_image_processing
        //SAMPLE_WEIGHT_IMAGE_QCOM = 1000440000,
        //// Provided by VK_QCOM_image_processing
        //BLOCK_MATCH_IMAGE_QCOM = 1000440001,
        //// Provided by VK_EXT_mutable_descriptor_type
        //MUTABLE_EXT = 1000351000,
        //// Provided by VK_EXT_inline_uniform_block
        //INLINE_UNIFORM_BLOCK_EXT = INLINE_UNIFORM_BLOCK,
        //// Provided by VK_VALVE_mutable_descriptor_type
        //MUTABLE_VALVE = MUTABLE_EXT,
	};
}

#endif