/*****************************************************************//**
 * @file   VulkanRenderPass.cpp
 * @brief  VulkanRenderPassƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   March 2023
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanRenderPass.hpp"
#include "../../../include/API/Vulkan/VulkanDevice.hpp"
#include "../../../include/API/Vulkan/VulkanWindow.hpp"

#include "../../../include/API/Vulkan/Utility/Macro.hpp"

#include "../../../include/Utility/Logger.hpp"

namespace Hence
{
    VulkanRenderPass::VulkanRenderPass(VulkanDevice& device, VulkanWindow& window) noexcept
        : mDevice(device)
    {
        auto& depthStencilTarget = window.getDepthBuffer();

        createRenderPass(window.getVkSwapchainImages(), depthStencilTarget.getVkImage(), window.getVkFormat(), depthStencilTarget.getVkFormat());
        VkExtent3D extent3D
        {
            window.getVkSwapchainExtent().width,
            window.getVkSwapchainExtent().height,
            1,
        };

        createFrameBuffer(window.getVkSwapchainImageViews(), extent3D);
    }


    VulkanRenderPass::~VulkanRenderPass()
    {
        const auto vkDevice = mDevice.getDevice();

        for (auto& fb : mFrameBuffers)
        {
            vkDestroyFramebuffer(vkDevice, fb, nullptr);
        }

        vkDestroyRenderPass(vkDevice, mRenderPass, nullptr);
    }

    inline Result VulkanRenderPass::createRenderPass(const std::vector<VkImage>& colorTargets, VkImage depthTarget, VkFormat colorFormat, VkFormat depthFormat) noexcept
    {
        std::vector<VkAttachmentDescription> adVec;
        std::vector<VkAttachmentReference> arVec;

        const auto size = colorTargets.size();
        
        {
            for (size_t i = 0; i < size; ++i)
            {
                auto& ad = adVec.emplace_back(VkAttachmentDescription{});
                auto& ar = arVec.emplace_back(VkAttachmentReference{});

                //if (!rpo.mExtent)
                //    rpo.mExtent = io.extent;

                //if (loadPrevFrame)
                //{
                //    ad.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
                //    ad.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

                //    switch (io.currentLayout)
                //    {
                //    case VK_IMAGE_LAYOUT_UNDEFINED:
                //    case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
                //        ad.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
                //        break;
                //    case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
                //        ad.initialLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
                //        break;
                //    default:
                //        std::cerr << "invalid initial image layout!\n";
                //        return Result::eFailure;
                //        break;
                //    }
                //}
                //else
                //{
                    ad.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
                    ad.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
                    ad.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
                //}

                ad.format = colorFormat;
                ad.samples = VK_SAMPLE_COUNT_1_BIT;
                ad.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
                ar.attachment = static_cast<std::uint32_t>(i);
                ar.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            }
        }

        VkSubpassDescription subpassDesc{};
        subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpassDesc.colorAttachmentCount = static_cast<uint32_t>(arVec.size());
        subpassDesc.pColorAttachments = arVec.data();

        VkAttachmentReference depthAr;
        auto&& depthAd = adVec.emplace_back();
        //auto& depthBuffer = mImageMap[depthTarget];

        //if (loadPrevFrame)
        //{
        //    depthAd.loadOp = VK_ATTACHMENT_LOAD_OP_LOAD;
        //    depthAd.initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        //}
        //else
        //{
            depthAd.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
            depthAd.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        //}

        depthAd.format = depthFormat;
        depthAd.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAd.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        depthAd.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        depthAr.attachment = static_cast<std::uint32_t>(size);  // attach to last index
        depthAr.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        subpassDesc.pDepthStencilAttachment = &depthAr;

        VkRenderPassCreateInfo ci{};

        ci.attachmentCount = static_cast<uint32_t>(adVec.size());
        ci.pAttachments = adVec.data();
        ci.subpassCount = 1;
        ci.pSubpasses = &subpassDesc;

        if (VK_FAILED(res, vkCreateRenderPass(mDevice.getDevice(), &ci, nullptr, &mRenderPass)))
        {
            Logger::error("failed to create renderpass! (native result : {})", static_cast<std::int32_t>(res));
            return Result(res);
        }
    

        return Result();
    }

    inline Result VulkanRenderPass::createFrameBuffer(const std::vector<VkImageView>& ctViews, const VkExtent3D& extent) noexcept
    {
        VkFramebufferCreateInfo fbci{};
        fbci.sType              = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        fbci.renderPass         = mRenderPass;
        fbci.width              = extent.width;
        fbci.height             = extent.height;
        fbci.layers             = 1;
        fbci.attachmentCount    = static_cast<uint32_t>(ctViews.size());
        fbci.pAttachments       = ctViews.data();

        mFrameBuffers.emplace_back();

        if (VK_FAILED(res, vkCreateFramebuffer(mDevice.getDevice(), &fbci, nullptr, &mFrameBuffers.back())))
        {
            Logger::error("failed to create framebuffer! (native result : {})", static_cast<std::int32_t>(res));
            return Result(res);
        }

        return Result();
    }

}
