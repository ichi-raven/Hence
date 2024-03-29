/*****************************************************************//**
 * @file   VulkanRenderPass.cpp
 * @brief  VulkanRenderPassクラスの実装
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
    VulkanRenderPass::VulkanRenderPass(VulkanDevice* pVulkanDevice, VulkanWindow& window) noexcept
        : mpDevice(pVulkanDevice)
        , mExtent(
            {
                window.getVkSwapchainExtent().width,
                window.getVkSwapchainExtent().height,
                1,
            })
    {
        assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");

        auto& depthStencilTarget = window.getDepthBuffer();

        createRenderPass(1, window.getVkFormat(), depthStencilTarget.getVkFormat(), VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

        std::vector<VkImageView> views(window.getVkSwapchainImageViews());
        
        createFrameBufferEach(views, depthStencilTarget.getVkImageView());
    }


    VulkanRenderPass::~VulkanRenderPass()
    {
        const auto vkDevice = mpDevice->getDevice();

        for (auto& fb : mFrameBuffers)
        {
            vkDestroyFramebuffer(vkDevice, fb, nullptr);
        }

        vkDestroyRenderPass(vkDevice, mRenderPass, nullptr);
    }

    Result VulkanRenderPass::createRenderPass(const std::size_t colorTargetNum, VkFormat colorFormat, std::optional<VkFormat> depthFormat, VkImageLayout finalLayout) noexcept
    {
        std::vector<VkAttachmentDescription> adVec;
        std::vector<VkAttachmentReference> arVec;
        VkAttachmentReference depthAr{};
        
        adVec.reserve(colorTargetNum);
        arVec.reserve(colorTargetNum);

        {
            for (std::size_t i = 0; i < colorTargetNum; ++i)
            {
                auto& ad = adVec.emplace_back();
                auto& ar = arVec.emplace_back();

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
                //ad.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
                ad.finalLayout = finalLayout;

                ar.attachment = static_cast<std::uint32_t>(i);
                ar.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            }
        }
         
        VkSubpassDescription subpassDesc{};
        subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpassDesc.colorAttachmentCount = static_cast<uint32_t>(arVec.size());
        subpassDesc.pColorAttachments = arVec.data();

        if (depthFormat)
        {
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

            depthAd.format = *depthFormat;
            depthAd.samples = VK_SAMPLE_COUNT_1_BIT;
            depthAd.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
            depthAd.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
            depthAr.attachment = static_cast<std::uint32_t>(colorTargetNum);  // attach to last index
            depthAr.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

            subpassDesc.pDepthStencilAttachment = &depthAr;
        }

        VkRenderPassCreateInfo ci
        {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            .pNext = nullptr,
            .attachmentCount = static_cast<std::uint32_t>(adVec.size()),
            .pAttachments = adVec.data(),
            .subpassCount = 1,
            .pSubpasses = &subpassDesc,
        };

        if (VK_FAILED(res, vkCreateRenderPass(mpDevice->getDevice(), &ci, nullptr, &mRenderPass)))
        {
            Logger::error("failed to create renderpass! (native result : {})", static_cast<std::int32_t>(res));
            return Result(res);
        }
    

        return Result();
    }

    Result VulkanRenderPass::createFrameBufferEach(const std::vector<VkImageView>& views, VkImageView depthView) noexcept
    {
        VkFramebufferCreateInfo fbci{};
        fbci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        fbci.renderPass = mRenderPass;
        fbci.width = mExtent.width;
        fbci.height = mExtent.height;
        fbci.layers = 1;
        if (depthView == VK_NULL_HANDLE)
        {
            fbci.attachmentCount = 1u;
        }
        else
        {
            fbci.attachmentCount = 2u;
        }

        mFrameBuffers.reserve(views.size());

        for (const auto& view : views)
        {
            mFrameBuffers.emplace_back();
            
            VkImageView views[] = { view, depthView };

            if (depthView == VK_NULL_HANDLE)
            {
                fbci.pAttachments = &view;
            }
            else
            {
                fbci.pAttachments = views;
            }

            if (VK_FAILED(res, vkCreateFramebuffer(mpDevice->getDevice(), &fbci, nullptr, &mFrameBuffers.back())))
            {
                Logger::error("failed to create framebuffer! (native result : {})", static_cast<std::int32_t>(res));
                return Result(static_cast<std::int32_t>(res));
            }
        }

        return Result();
    }

    Result VulkanRenderPass::createFrameBufferSumUp(const std::vector<VkImageView>& views) noexcept
    {
        VkFramebufferCreateInfo fbci{};
        fbci.sType              = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        fbci.renderPass         = mRenderPass;
        fbci.width              = mExtent.width;
        fbci.height             = mExtent.height;
        fbci.layers             = 1;
        fbci.attachmentCount    = static_cast<uint32_t>(views.size());
        fbci.pAttachments       = views.data();

        mFrameBuffers.emplace_back();

        if (VK_FAILED(res, vkCreateFramebuffer(mpDevice->getDevice(), &fbci, nullptr, &mFrameBuffers.back())))
        {
            Logger::error("failed to create framebuffer! (native result : {})", static_cast<std::int32_t>(res));
            return Result(static_cast<std::int32_t>(res));
        }

        return Result();
    }

    VkRenderPass VulkanRenderPass::getVkRenderPass() noexcept
    {
        return mRenderPass;
    }

    const std::vector<VkFramebuffer>& VulkanRenderPass::getVkFrameBuffers() noexcept
    {
        return mFrameBuffers;
    }

    const VkExtent3D& VulkanRenderPass::getVkExtent3D() const noexcept
    {
        return mExtent;
    }
}
