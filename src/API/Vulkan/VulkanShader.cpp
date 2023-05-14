/*****************************************************************//**
 * @file   VulkanShader.cpp
 * @brief  VulkanShaderƒNƒ‰ƒX‚ÌŽÀ‘•
 * 
 * @author ichi-raven
 * @date   January 2023
 *********************************************************************/
#include "../../../include/API/Vulkan/VulkanShader.hpp"

#include "../../../include/API/Vulkan/VulkanDevice.hpp"

#include "../../../include/API/Vulkan/ThirdParty/spirv_reflect.h"


#include "../../../include/API/Vulkan/Utility/Macro.hpp"
#include "../../../include/API/Vulkan/Utility/HelperFunctions.hpp"

#include "../../../include/Utility/Logger.hpp"

#include "../../../include/Info/ResourceType.hpp"
#include "../../../include/Info/Format.hpp"


#include <fstream>

namespace Hence
{
	VulkanShader::VulkanShader(VulkanDevice* pVulkanDevice, std::string_view path) noexcept
        : mpDevice(pVulkanDevice)
        , mShaderStage(ShaderStage::ALL)
    {
        assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");

        {// load

            std::ifstream infile(path.data(), std::ios::binary);
            assert(infile);

            mFileData.resize(uint32_t(infile.seekg(0, std::ifstream::end).tellg()));
            infile.seekg(0, std::ifstream::beg).read(mFileData.data(), mFileData.size());
        }

        Logger::info("loaded shader : {}", path);

        VkShaderModuleCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        ci.pNext = nullptr;
        ci.pCode = reinterpret_cast<const uint32_t*>(mFileData.data());
        ci.codeSize = mFileData.size();
        
        if (VK_FAILED(res, vkCreateShaderModule(mpDevice->getDevice(), &ci, nullptr, &mShaderModule)))
        {
            Logger::error("failed to create shader module!");
            return;
        }

        loadShaderReflection();
	}

    VulkanShader::~VulkanShader()
    {
        vkDestroyShaderModule(mpDevice->getDevice(), mShaderModule, nullptr);
    }

    Result VulkanShader::loadShaderReflection() noexcept
    {
        //load shader module
        SpvReflectShaderModule module = {};
        SpvReflectResult result = spvReflectCreateShaderModule(sizeof(mFileData[0]) * mFileData.size(), mFileData.data(), &module);
        if (result != SPV_REFLECT_RESULT_SUCCESS)
        {
            Logger::error("failed to create SPIRV-Reflect shader module!");
            return Result(0);
        }

        //Logger::info("stage : {}", stageSV);

        if (!module.entry_point_name)
        {
            Logger::error("missing entry point from shader {}!", module.source_file);
            return Result(0);
        }
        else
        {
            mEntryPoint = std::string(module.entry_point_name);
        }

        // Žæ“¾‚µ‚Ä‚¨‚­
        //mShaderStageCreateInfo.stage = static_cast<VkShaderStageFlagBits>(module.shader_stage);
        mShaderStage = static_cast<ShaderStage>(module.shader_stage);

        /*switch (module.shader_stage)
        {
        case SPV_REFLECT_SHADER_STAGE_VERTEX_BIT:
            std::cout << "VS";
            break;
        case SPV_REFLECT_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
            std::cout << "HS";
            break;
        case SPV_REFLECT_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
            std::cout << "DS";
            break;
        case SPV_REFLECT_SHADER_STAGE_GEOMETRY_BIT:
            std::cout << "GS";
            break;
        case SPV_REFLECT_SHADER_STAGE_FRAGMENT_BIT:
            std::cout << "PS";
            break;
        case SPV_REFLECT_SHADER_STAGE_COMPUTE_BIT:
            std::cout << "CS";
            break;
        default:
            break;
        }
        std::cout << "\n";*/

        //get desecriptor set layout
        {
            std::vector<SpvReflectDescriptorSet*> sets;
            {
                uint32_t count = 0;
                result = spvReflectEnumerateDescriptorSets(&module, &count, NULL);
                assert(result == SPV_REFLECT_RESULT_SUCCESS);

                sets.resize(count);

                result = spvReflectEnumerateDescriptorSets(&module, &count, sets.data());
                assert(result == SPV_REFLECT_RESULT_SUCCESS);
            }

            for (size_t i = 0; i < sets.size(); ++i)
            {
                for (size_t j = 0; j < sets[i]->binding_count; ++j)
                {
                    ResourceType srt = static_cast<ResourceType>(sets[i]->bindings[j]->descriptor_type);
                    mResourceLayoutTable.emplace(std::pair<uint8_t, uint8_t>(sets[i]->set, sets[i]->bindings[j]->binding), srt);

                    //switch (sets[i]->bindings[j]->descriptor_type)
                    //{
                    //case SPV_REFLECT_DESCRIPTOR_TYPE_SAMPLER:
                    //    srt = ResourceType::Sampler;
                    //    break;
                    //case SPV_REFLECT_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
                    //    srt = ResourceType::CombinedImageSampler;
                    //    break;
                    //case SPV_REFLECT_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
                    //    srt = ResourceType::Image;
                    //    break;
                    //    //case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_IMAGE              : ; break;
                    //    //case SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER       : ; break;
                    //    //case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER       : ; break;
                    //case SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
                    //    srt = ResourceType::UniformBuffer;
                    //    break;
                    //    //case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_BUFFER             : ; break;
                    //    //case SPV_REFLECT_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC     : ; break;
                    //    //case SPV_REFLECT_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC     : ; break;
                    //    //case SPV_REFLECT_DESCRIPTOR_TYPE_INPUT_ATTACHMENT           : ; break;
                    //    //case SPV_REFLECT_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR : ; break;
                    //default:
                    //    Logger::error("failed to reflect shader resource!  param : {}", static_cast<int>(sets[i]->bindings[j]->descriptor_type));
                    //    return Result(0);
                    //    break;
                    //}

                }
            }
        }

        {  //“üo—Í•Ï”‚ðŽæ“¾
            static auto lmdComp = [](const SpvReflectInterfaceVariable* l, const SpvReflectInterfaceVariable* r) -> bool
            {
                return l->location < r->location;
            };

            uint32_t count = 0;
            result = spvReflectEnumerateInputVariables(&module, &count, NULL);
            assert(result == SPV_REFLECT_RESULT_SUCCESS);

            std::vector<SpvReflectInterfaceVariable*> inputVars(count);
            mInputVariables.resize(count);
            result = spvReflectEnumerateInputVariables(&module, &count, inputVars.data());
            assert(result == SPV_REFLECT_RESULT_SUCCESS);
            if (!inputVars.empty())
                std::sort(inputVars.begin(), inputVars.end(), lmdComp);

            count = 0;
            result = spvReflectEnumerateOutputVariables(&module, &count, NULL);
            assert(result == SPV_REFLECT_RESULT_SUCCESS);

            std::vector<SpvReflectInterfaceVariable*> outputVars(count);
            mOutputVariables.resize(count);
            result = spvReflectEnumerateOutputVariables(&module, &count, outputVars.data());
            assert(result == SPV_REFLECT_RESULT_SUCCESS);
            if (!outputVars.empty())
                std::sort(outputVars.begin(), outputVars.end(), lmdComp);

            //input
            for (size_t i = 0; i < mInputVariables.size(); ++i)
            {
                auto inputVar = spvReflectGetInputVariableByLocation(&module, inputVars[i]->location, &result);
                if (inputVars[i]->location == UINT32_MAX)
                {
                    assert(result == SPV_REFLECT_RESULT_ERROR_ELEMENT_NOT_FOUND);
                    assert(inputVar == nullptr);
                    mInputVariables.pop_back();
                    continue;
                }
                else
                {
                    assert(result == SPV_REFLECT_RESULT_SUCCESS);
                    assert(inputVars[i] == inputVar);
                }
                (void)inputVar;

                mInputVariables[i] = static_cast<Format>(inputVar->format);
            }

            //output
            for (size_t i = 0; i < mOutputVariables.size(); ++i)
            {
                auto outputVar = spvReflectGetOutputVariableByLocation(&module, outputVars[i]->location, &result);
                if (outputVars[i]->location == UINT32_MAX)
                {
                    assert(result == SPV_REFLECT_RESULT_ERROR_ELEMENT_NOT_FOUND);
                    assert(outputVar == nullptr);
                    mOutputVariables.pop_back();
                    continue;
                }
                else
                {
                    assert(result == SPV_REFLECT_RESULT_SUCCESS);
                    assert(outputVars[i] == outputVar);
                }
                (void)outputVar;

                mOutputVariables[i] = static_cast<Format>(outputVar->format);

            }

            spvReflectDestroyShaderModule(&module);
        }

        return Result();
    }

    //const VkPipelineShaderStageCreateInfo& VulkanShader::getShaderStageCreateInfo() const noexcept
    //{
    //    return mShaderStageCreateInfo;
    //}

    VkShaderModule VulkanShader::getVkShaderModule() noexcept
    {
        return mShaderModule;
    }

    const std::map<std::pair<uint8_t, uint8_t>, ResourceType>& VulkanShader::getResourceLayoutTable() const noexcept
    {
        return mResourceLayoutTable;
    }

    const std::vector<Format>& VulkanShader::getInputVariables() const noexcept
    {
        return mInputVariables;
    }

    const std::vector<Format>& VulkanShader::getOutputVariables() const noexcept
    {
        return mOutputVariables;
    }

    std::string_view VulkanShader::getEntryPoint() const noexcept
    {
        return mEntryPoint;
    }

    ShaderStage VulkanShader::getShaderStage() const noexcept
    {
        return mShaderStage;
    }

}
