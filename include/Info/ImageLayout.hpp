/*****************************************************************//**
 * @file   ImageLayout.hpp
 * @brief  Imageのメモリレイアウト列挙型のヘッダファイル
 * 
 * 
 * @author ichi-raven
 * @date   May 2023
 *********************************************************************/
#ifndef HENCE_INFO_IMAGELAYOUT_HPP_
#define HENCE_INFO_IMAGELAYOUT_HPP_

namespace Hence
{
	enum class ImageLayout
	{
        Undefined = 0,
        General = 1,
        ColorAttachmentOptimal = 2,
        DepthStencilAttachmentOptimal = 3,
        DepthStencilReadOnlyOptimal = 4,
        ShaderReadOnlyOptimal = 5,
        TransferSRCOptimal = 6,
        TransferDSTOptimal = 7,
        Preinitialized = 8,


        // Provided by VK_VERSION_1_1
        DepthReadOnlyStencilAttachmentOptimal = 1000117000,
        // Provided by VK_VERSION_1_1
        DepthAttachmentStencilReadOnlyOptimal = 1000117001,
        // Provided by VK_VERSION_1_2
        DepthAttachmentOptimal = 1000241000,
        // Provided by VK_VERSION_1_2
        DepthReadOnlyOptimal = 1000241001,
        // Provided by VK_VERSION_1_2
        StencilAttachmentOptimal = 1000241002,
        // Provided by VK_VERSION_1_2
        StencilReadOnlyOptimal = 1000241003,
        // Provided by VK_VERSION_1_3
        ReadOnlyOptimal = 1000314000,
        // Provided by VK_VERSION_1_3
        AttachmentOptimal = 1000314001,
        // Provided by VK_KHR_swapchain
        PresentSRCOptimal = 1000001002,
        // Provided by VK_KHR_video_decode_queue
        VideoDecodeDST = 1000024000,
        // Provided by VK_KHR_video_decode_queue
        VideoDecodeSRC = 1000024001,
        // Provided by VK_KHR_video_decode_queue
        VideoDecodeDPB = 1000024002,
        // Provided by VK_KHR_shared_presentable_image
        SharedPresent = 1000111000,
        // Provided by VK_EXT_fragment_density_map
        FragmentDensityMapOptimal = 1000218000,
        // Provided by VK_KHR_fragment_shading_rate
        FragmentShadingRateAttachmentOptimal = 1000164003,
	};
}

#endif
