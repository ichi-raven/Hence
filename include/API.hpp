/*****************************************************************//**
 * @file   API.hpp
 * @brief  APIごとのtrait及び実装分岐を定義する
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/

#ifndef HENCE_API_HPP_
#define HENCE_API_HPP_

#include "API/VulkanImpl.hpp"
#include "API/DirectX12Impl.hpp"

namespace Hence
{
    /**
     * @brief  Vulkan APIを表す型，APIとしてこの型を渡せばVulkan APIをバックエンドとして動作する
     */
    struct Vulkan 
    {
        constexpr static auto APIName = "Vulkan";
    };

    /**
     * @brief  DirectX12を表す型，APIとしてこの型を渡せばDirectX12をバックエンドとして動作する
     */
    struct DirectX12 
    {
        constexpr static auto APIName = "DirectX12";
    };

    /**
     * @brief  APIのtrait，この特殊化を用いてAPIごとの実装分岐を表現する
     */
    template<typename API>
    struct APITrait;

    template<>
    struct APITrait<Vulkan>
    {
        using Device                    = VulkanDevice;
        using WindowImpl                = VulkanWindow;
        using VRAMAllocatorImpl         = VulkanVRAMAllocator;
        using BufferImpl                = VulkanBuffer;
        using ImageImpl                 = VulkanImage;
        using ShaderImpl                = VulkanShader;
        using BindGroupImpl             = VulkanBindGroup;
        using CommandImpl               = VulkanCommand;
        using RenderPassImpl            = VulkanRenderPass;
        using GraphicsPipelineImpl      = VulkanGraphicsPipeline;
        using ComputePipelineImpl       = VulkanComputePipeline;
        using RaytracingPipelineImpl    = VulkanRaytracingPipeline;
    };

    template<>
    struct APITrait<DirectX12>
    {
        using Device                    = DirectX12Device;
        using WindowImpl                = DirectX12Window;
        using VRAMAllocatorImpl         = DirectX12VRAMAllocator;
        using BufferImpl                = DirectX12Buffer;
        using ImageImpl                 = DirectX12Image;
        using ShaderImpl                = DirectX12Shader;
        using BindGroupImpl             = DirectX12BindGroup;
        using CommandImpl               = DirectX12Command;
        using RenderPassImpl            = DirectX12RenderPass;
        using GraphicsPipelineImpl      = DirectX12GraphicsPipeline;
        using ComputePipelineImpl       = DirectX12ComputePipeline;
        using RaytracingPipelineImpl    = DirectX12RaytracingPipeline;
    };
}

#endif
