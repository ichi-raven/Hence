/*****************************************************************//**
 * @file   ShaderStage.hpp
 * @brief  ShaderStage列挙型のヘッダファイル
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/
#ifndef HENCE_INCLUDE_INFO_SHADERSTAGE_HPP
#define HENCE_INCLUDE_INFO_SHADERSTAGE_HPP

namespace Hence
{
    enum class ShaderStage
    {
        Vertex                  = 0x00000001,
        TessellationControl     = 0x00000002,
        TessellationEvaluation  = 0x00000004,
        Geometry                = 0x00000008,
        Fragment                = 0x00000010,
        Pixel                   = Fragment,
        Compute                 = 0x00000020,
        ALL_GRAPHICS            = 0x0000001F,
        ALL                     = 0x7FFFFFFF,
        // Provided by VK_KHR_ray_tracing_pipeline
        RayGen_KHR              = 0x00000100,
        // Provided by VK_KHR_ray_tracing_pipeline
        AnyHit_KHR             = 0x00000200,
        // Provided by VK_KHR_ray_tracing_pipeline
        ClosestHit_KHR         = 0x00000400,
        // Provided by VK_KHR_ray_tracing_pipeline
        Miss_KHR                = 0x00000800,
        // Provided by VK_KHR_ray_tracing_pipeline
        Intersection_KHR        = 0x00001000,
        // Provided by VK_KHR_ray_tracing_pipeline
        Callable_KHR            = 0x00002000,
        // Provided by VK_EXT_mesh_shader
        Task_EXT                = 0x00000040,
        // Provided by VK_EXT_mesh_shader
        Mesh_EXT                = 0x00000080,
        //// Provided by VK_HUAWEI_subpass_shading
        //SUBPASS_SHADING_HUAWEI  = 0x00004000,
        //// Provided by VK_HUAWEI_cluster_culling_shader
        //CLUSTER_CULLING_HUAWEI  = 0x00080000,
        //// Provided by VK_NV_ray_tracing
        //RAYGEN_NV               = RAYGEN_KHR,
        //// Provided by VK_NV_ray_tracing
        //ANY_HIT_NV              = ANY_HIT_KHR,
        //// Provided by VK_NV_ray_tracing
        //CLOSEST_HIT_NV          = CLOSEST_HIT_KHR,
        //// Provided by VK_NV_ray_tracing
        //MISS_NV                 = MISS_KHR,
        //// Provided by VK_NV_ray_tracing
        //INTERSECTION_NV         = INTERSECTION_KHR,
        //// Provided by VK_NV_ray_tracing
        //CALLABLE_NV             = CALLABLE_KHR,
        //// Provided by VK_NV_mesh_shader
        //TASK_NV                 = TASK_EXT,
        //// Provided by VK_NV_mesh_shader
        //MESH_NV                 = MESH_EXT,
	};
}

#endif
