/*****************************************************************//**
 * @file   Macro.hpp
 * @brief  Vulkan�����p�}�N����`�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_API_VULKAN_UTILITY_MACRO_HPP_
#define HENCE_API_VULKAN_UTILITY_MACRO_HPP_

#define VK_FAILED(resultVar, func) const auto resultVar = func; resultVar != VK_SUCCESS


#endif