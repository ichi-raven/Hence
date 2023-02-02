/*****************************************************************//**
 * @file   VulkanBindLayout.cpp
 * @brief  VulkanBindLayouotƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   January 2023
 *********************************************************************/

#include "../../../include/API/Vulkan/VulkanBindLayout.hpp"

namespace Hence
{
	VulkanBindLayout::VulkanBindLayout(const VulkanShader& shader) noexcept
	{
        uint32_t ubcount = 0;
        uint32_t ctcount = 0;
        {  // DescriptorSetLayout

            std::vector<std::vector<VkDescriptorSetLayoutBinding>> allBindings;
            allBindings.reserve(8);
            {  // HACK
                uint32_t nowSet = UINT32_MAX;
                for (const auto& [sb, srt] : layoutTable)
                {
                    if (sb.first != nowSet)
                    {
                        allBindings.emplace_back();
                        nowSet = sb.first;
                    }

                    auto&& b = allBindings.back().emplace_back();
                    b.binding = sb.second;
                    b.descriptorCount = 1;
                    switch (srt)
                    {
                    case Shader::ShaderResourceType::eUniformBuffer:
                        b.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                        ++ubcount;
                        break;

                    case Shader::ShaderResourceType::eCombinedTexture:
                        b.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                        ++ctcount;
                        break;

                    case Shader::ShaderResourceType::eSampler:
                        assert(!"not supported");
                        break;
                    }

                    b.pImmutableSamplers = nullptr;
                    b.stageFlags = VK_SHADER_STAGE_ALL;
                }
            }

            VkDescriptorSetLayoutCreateInfo descLayoutci{};
            descLayoutci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
            for (auto& bindings : allBindings)
            {
                descLayoutci.bindingCount = static_cast<uint32_t>(bindings.size());
                descLayoutci.pBindings = bindings.data();

                {
                    VkDescriptorSetLayout descriptorSetLayout;
                    result = checkVkResult(vkCreateDescriptorSetLayout(
                        mDevice, &descLayoutci, nullptr, &descriptorSetLayout));
                    if (result != Result::eSuccess)
                    {
                        std::cerr << "failed to create descriptor set layout\n";
                        return result;
                    }

                    gpo.mDescriptorSetLayouts.emplace_back(descriptorSetLayout);
                    gpo.mSetSizes.emplace_back(bindings.size());
                }
            }
	}

	VulkanBindLayout::VulkanBindLayout(const ArrayProxy<uint8_t> bufferBinding, const ArrayProxy<uint8_t> imageBinding, const ArrayProxy<uint8_t> samplerBinding) noexcept
	{

	}

	VkDescriptorSetLayout VulkanBindLayout::getDescriptorSetLayout() noexcept
	{

	}

}
