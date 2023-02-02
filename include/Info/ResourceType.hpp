/*****************************************************************//**
 * @file   ResourceType.hpp
 * @brief  ResourceType�񋓌^�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   February 2023
 *********************************************************************/
#ifndef HENCE_INCLUDE_INFO_RESOURCETYPE_HPP_
#define HENCE_INCLUDE_INFO_RESOURCETYPE_HPP_

namespace Hence
{
	enum class ResourceType
	{
		UniformBuffer,
		Image,
		Texture = Image,
		Sampler,
		CombinedImageSampler,
	};
}

#endif