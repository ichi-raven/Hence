/*****************************************************************//**
 * @file   VulkanShader.cpp
 * @brief  VulkanShaderクラスの実装
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

#include <glslang/SPIRV/GlslangToSpv.h>
#include <glslang/Include/ResourceLimits.h>

#include <fstream>

namespace Hence
{
    namespace Compiler
    {
        static TBuiltInResource InitResources()
        {
            TBuiltInResource Resources;

            Resources.maxLights = 32;
            Resources.maxClipPlanes = 6;
            Resources.maxTextureUnits = 32;
            Resources.maxTextureCoords = 32;
            Resources.maxVertexAttribs = 64;
            Resources.maxVertexUniformComponents = 4096;
            Resources.maxVaryingFloats = 64;
            Resources.maxVertexTextureImageUnits = 32;
            Resources.maxCombinedTextureImageUnits = 80;
            Resources.maxTextureImageUnits = 32;
            Resources.maxFragmentUniformComponents = 4096;
            Resources.maxDrawBuffers = 32;
            Resources.maxVertexUniformVectors = 128;
            Resources.maxVaryingVectors = 8;
            Resources.maxFragmentUniformVectors = 16;
            Resources.maxVertexOutputVectors = 16;
            Resources.maxFragmentInputVectors = 15;
            Resources.minProgramTexelOffset = -8;
            Resources.maxProgramTexelOffset = 7;
            Resources.maxClipDistances = 8;
            Resources.maxComputeWorkGroupCountX = 65535;
            Resources.maxComputeWorkGroupCountY = 65535;
            Resources.maxComputeWorkGroupCountZ = 65535;
            Resources.maxComputeWorkGroupSizeX = 1024;
            Resources.maxComputeWorkGroupSizeY = 1024;
            Resources.maxComputeWorkGroupSizeZ = 64;
            Resources.maxComputeUniformComponents = 1024;
            Resources.maxComputeTextureImageUnits = 16;
            Resources.maxComputeImageUniforms = 8;
            Resources.maxComputeAtomicCounters = 8;
            Resources.maxComputeAtomicCounterBuffers = 1;
            Resources.maxVaryingComponents = 60;
            Resources.maxVertexOutputComponents = 64;
            Resources.maxGeometryInputComponents = 64;
            Resources.maxGeometryOutputComponents = 128;
            Resources.maxFragmentInputComponents = 128;
            Resources.maxImageUnits = 8;
            Resources.maxCombinedImageUnitsAndFragmentOutputs = 8;
            Resources.maxCombinedShaderOutputResources = 8;
            Resources.maxImageSamples = 0;
            Resources.maxVertexImageUniforms = 0;
            Resources.maxTessControlImageUniforms = 0;
            Resources.maxTessEvaluationImageUniforms = 0;
            Resources.maxGeometryImageUniforms = 0;
            Resources.maxFragmentImageUniforms = 8;
            Resources.maxCombinedImageUniforms = 8;
            Resources.maxGeometryTextureImageUnits = 16;
            Resources.maxGeometryOutputVertices = 256;
            Resources.maxGeometryTotalOutputComponents = 1024;
            Resources.maxGeometryUniformComponents = 1024;
            Resources.maxGeometryVaryingComponents = 64;
            Resources.maxTessControlInputComponents = 128;
            Resources.maxTessControlOutputComponents = 128;
            Resources.maxTessControlTextureImageUnits = 16;
            Resources.maxTessControlUniformComponents = 1024;
            Resources.maxTessControlTotalOutputComponents = 4096;
            Resources.maxTessEvaluationInputComponents = 128;
            Resources.maxTessEvaluationOutputComponents = 128;
            Resources.maxTessEvaluationTextureImageUnits = 16;
            Resources.maxTessEvaluationUniformComponents = 1024;
            Resources.maxTessPatchComponents = 120;
            Resources.maxPatchVertices = 32;
            Resources.maxTessGenLevel = 64;
            Resources.maxViewports = 16;
            Resources.maxVertexAtomicCounters = 0;
            Resources.maxTessControlAtomicCounters = 0;
            Resources.maxTessEvaluationAtomicCounters = 0;
            Resources.maxGeometryAtomicCounters = 0;
            Resources.maxFragmentAtomicCounters = 8;
            Resources.maxCombinedAtomicCounters = 8;
            Resources.maxAtomicCounterBindings = 1;
            Resources.maxVertexAtomicCounterBuffers = 0;
            Resources.maxTessControlAtomicCounterBuffers = 0;
            Resources.maxTessEvaluationAtomicCounterBuffers = 0;
            Resources.maxGeometryAtomicCounterBuffers = 0;
            Resources.maxFragmentAtomicCounterBuffers = 1;
            Resources.maxCombinedAtomicCounterBuffers = 1;
            Resources.maxAtomicCounterBufferSize = 16384;
            Resources.maxTransformFeedbackBuffers = 4;
            Resources.maxTransformFeedbackInterleavedComponents = 64;
            Resources.maxCullDistances = 8;
            Resources.maxCombinedClipAndCullDistances = 8;
            Resources.maxSamples = 4;
            Resources.maxMeshOutputVerticesNV = 256;
            Resources.maxMeshOutputPrimitivesNV = 512;
            Resources.maxMeshWorkGroupSizeX_NV = 32;
            Resources.maxMeshWorkGroupSizeY_NV = 1;
            Resources.maxMeshWorkGroupSizeZ_NV = 1;
            Resources.maxTaskWorkGroupSizeX_NV = 32;
            Resources.maxTaskWorkGroupSizeY_NV = 1;
            Resources.maxTaskWorkGroupSizeZ_NV = 1;
            Resources.maxMeshViewCountNV = 4;

            Resources.limits.nonInductiveForLoops = 1;
            Resources.limits.whileLoops = 1;
            Resources.limits.doWhileLoops = 1;
            Resources.limits.generalUniformIndexing = 1;
            Resources.limits.generalAttributeMatrixVectorIndexing = 1;
            Resources.limits.generalVaryingIndexing = 1;
            Resources.limits.generalSamplerIndexing = 1;
            Resources.limits.generalVariableIndexing = 1;
            Resources.limits.generalConstantMatrixVectorIndexing = 1;
            Resources.limits.generalUniformIndexing = true;

            return Resources;
        }

        std::string readFile(std::string_view path)
        {
            std::ifstream file(path.data());

            if (!file.is_open()) 
            {
                Logger::error("failed to load shader file {}!", path.data());
                return std::string("FAILED TO LOAD");
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }

        EShLanguage translateShaderStage(std::string_view filepath)
        {
            if (filepath.ends_with("vert"))         return EShLangVertex;
            else if (filepath.ends_with("frag"))    return EShLangFragment;
            else if (filepath.ends_with("comp"))    return EShLangCompute;
            else if (filepath.ends_with("rgen"))    return EShLangRayGenNV;
            else if (filepath.ends_with("rmiss"))   return EShLangMissNV;
            else if (filepath.ends_with("rchit"))   return EShLangClosestHitNV;
            else if (filepath.ends_with("rahit"))   return EShLangAnyHitNV;
            else assert(!"Unknown shader stage");

            return static_cast<EShLanguage>(0);//一応(しらん)
        }

        std::vector<unsigned int> compileText(EShLanguage stage,
            const std::string& shaderSource)
        {
            const static auto defaultResource = InitResources();

            glslang::InitializeProcess();

            const char* shaderStrings[1];
            shaderStrings[0] = shaderSource.data();

            glslang::TShader shader(stage);
            // RayTracingを使えるようにバージョン設定
            shader.setEnvTarget(glslang::EShTargetLanguage::EShTargetSpv,
                glslang::EShTargetLanguageVersion::EShTargetSpv_1_5);
            shader.setStrings(shaderStrings, 1);

            EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);
            if (!shader.parse(&defaultResource, 100, false, messages))
            {
                Logger::error("shader {} : \ncompile error! : {}", shaderSource, shader.getInfoLog());
            }

            glslang::TProgram program;
            program.addShader(&shader);

            if (!program.link(messages)) 
            {
                Logger::error("shader {} : \nlink error! : {}", shaderSource, shader.getInfoLog());
            }

            std::vector<std::uint32_t> spvShader;
            glslang::GlslangToSpv(*program.getIntermediate(stage), spvShader);
            glslang::FinalizeProcess();
            return spvShader;
        }

        std::vector<std::uint32_t> compileFile(std::string_view path)
        {
            EShLanguage stage = translateShaderStage(path);
            return compileText(stage, readFile(path));
        }

    } // namespace Compiler

	VulkanShader::VulkanShader(VulkanDevice* pVulkanDevice, std::string_view path) noexcept
        : mpDevice(pVulkanDevice)
        , mShaderStage(ShaderStage::ALL)
    {
        assert(pVulkanDevice != nullptr || !"vulkan device is nullptr!");

        std::vector<std::uint32_t> fileData;

        if (path.ends_with(".spv")) // 末尾がspv
        {// load

            std::ifstream infile(path.data(), std::ios::binary);
            assert(infile);

            fileData.resize(uint32_t(infile.seekg(0, std::ifstream::end).tellg()) / sizeof(std::uint32_t));
            infile.seekg(0, std::ifstream::beg).read(reinterpret_cast<char*>(fileData.data()), fileData.size() * sizeof(fileData[0]));
            
            Logger::info("loaded shader : {}", path);
        }
        else // 末尾がそれ以外
        {
            fileData = Compiler::compileFile(path);
            Logger::info("compiled shader : {}", path);
        }

        VkShaderModuleCreateInfo ci
        {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .pNext = nullptr,
            .codeSize = sizeof(fileData[0]) * fileData.size(),
            .pCode = fileData.data()
        };
        
        if (VK_FAILED(res, vkCreateShaderModule(mpDevice->getDevice(), &ci, nullptr, &mShaderModule)))
        {
            Logger::error("failed to create shader module!");
            return;
        }

        loadShaderReflection(fileData);
	}



    VulkanShader::~VulkanShader()
    {
        vkDestroyShaderModule(mpDevice->getDevice(), mShaderModule, nullptr);
    }

    Result VulkanShader::loadShaderReflection(const std::vector<std::uint32_t>& fileData) noexcept
    {
        //load shader module
        SpvReflectShaderModule module = {};
        SpvReflectResult result = spvReflectCreateShaderModule(sizeof(fileData[0]) * fileData.size(), fileData.data(), &module);
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

        // 取得しておく
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

        {  //入出力変数を取得
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
