/*****************************************************************//**
 * @file   VulkanCommand.hpp
 * @brief  VulkanCommandクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   April 2023
 *********************************************************************/
#ifndef HENCE_API_VULKAN_VULKANCOMMAND_HPP_
#define HENCE_API_VULKAN_VULKANCOMMAND_HPP_

#include "../../Utility/Result.hpp"
#include "../../Utility/ArrayProxy.hpp"

#include "../../Info/ClearValue.hpp"
#include "../../Info/ImageLayout.hpp"

#include <vulkan/vulkan.hpp>

#include <variant>
#include <optional>

namespace Hence
{
    class VulkanDevice;
    class VulkanRenderPass;
    class VulkanGraphicsPipeline;
    class VulkanComputePipeline;
    class VulkanRaytracingPipeline;
    class VulkanBuffer;
    class VulkanImage;
    class VulkanBindGroup;
    class VulkanSemaphore;

	class VulkanCommand
	{
    public:

        /**
         * @brief  コンストラクタ
         */
        VulkanCommand(VulkanDevice* pVulkanDevice) noexcept;

        /**
         * @brief  デストラクタ
         */
        ~VulkanCommand() noexcept;

        VulkanCommand(VulkanCommand&& other) noexcept;

        VulkanCommand& operator=(VulkanCommand&& other) noexcept;

        /**
         * @brief コマンド書き込み開始
         *
         * @param renderpass 描画を行うRenderPass
         */
        Result begin() noexcept;

        /**
         * @brief RenderPass開始
         *
         */
        Result beginRenderPass(VulkanRenderPass& renderpass, const std::uint32_t frameBufferIndex, ArrayProxy<ColorClearValue> ccvs, const std::optional<DepthClearValue>& dcv) noexcept;

        /**
         * @brief  RenderPass終了
         */
        Result endRenderPass() noexcept;

        /**
         * @brief コマンド書き込み終了
         *
         */
        Result end() noexcept;

        /**
         * @brief 使用する描画パイプラインをセットする
         *
         * @param pipeline 使用する描画パイプライン
         */
        Result setGraphicsPipeline(VulkanGraphicsPipeline& pipeline) noexcept;

        /**
         * @brief 使用するコンピュートパイプラインをセットする
         *
         * @param pipeline 使用するコンピュートパイプライン
         */
        Result setComputePipeline(VulkanComputePipeline& pipeline) noexcept;

        /**
         * @brief 使用するレイトレースパイプラインをセットする
         *
         * @param pipeline 使用するレイトレースパイプライン
         */
        Result setRaytracingPipeline(VulkanRaytracingPipeline& pipeline) noexcept;

        /**
         * @brief  使用するシェーダリソースのバインドグループをセットする
         *
         * @param space 割り当てるspace(HLSL)
         * @param bindGroup 使用するバインドグループ
         */
        Result setBindGroup(VulkanBindGroup& bindGroup) noexcept;

        /**
         * @brief  頂点バッファをセットする
         *
         * @return 結果
         */
        Result setVertexBuffer(VulkanBuffer& vertexBuffer) noexcept;

        /**
         * @brief  インデックスバッファをセットする
         */
        Result setIndexBuffer(VulkanBuffer& indexBuffer) noexcept;

        /**
         * @brief 描画を行う
         *
         */
        Result render(const std::uint32_t vertexCount, const std::uint32_t instanceCount, const std::uint32_t firstVertex, const std::uint32_t firstInstance) noexcept;

        Result renderIndexed(const std::uint32_t indexCount, const std::uint32_t instanceCount, const std::uint32_t firstIndex, const std::uint32_t vertexOffset, const std::uint32_t firstInstance) noexcept;

        Result dispatch(const std::uint32_t groupCountX, const std::uint32_t groupCountY, const std::uint32_t groupCountZ) noexcept;

        Result barrier(VulkanImage& image, const ImageLayout old, const ImageLayout dst) noexcept;

        Result execute(VulkanSemaphore& waitSemaphore, VulkanSemaphore& signalSemaphore) noexcept;

    private:

        struct NowPipelineData
        {
            VkPipelineLayout layout;
            VkPipelineBindPoint bindPoint;
        };

        VulkanDevice* mpDevice;
        std::optional<NowPipelineData> mNowPipelineData;

        VkCommandBuffer mCommandBuffer;
        VkFence mFence;

        //std::vector<VkSemaphore> mSemaphores;
	};
}

#endif