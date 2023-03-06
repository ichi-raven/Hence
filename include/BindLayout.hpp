/*****************************************************************//**
 * @file   BindLayout.hpp
 * @brief  BindLayout�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   December 2022
 *********************************************************************/
#ifndef HENCE_BINDLAYOUT_HPP_
#define HENCE_BINDLAYOUT_HPP_

#include "API.hpp"

namespace Hence
{
	template<typename API>
	class Shader;

	template<typename API>
	class BindLayout
	{
	public:
		using Impl = APITrait<API>::BindLayoutImpl;

		template<typename... ShaderType>
		BindLayout(Device<API>& device, ShaderType&... shaders);

		~BindLayout();

		// �������񂨂��Ƃ�
		//BindLayout(const std::map<std::pair<uint8_t, uint8_t>, ResourceType>& bindingLayoutTable);

		NONCOPYABLE(BindLayout)

		Impl& getInternalImpl() noexcept;

	private:
		using APIDevice = APITrait<API>::Device;

		//! �f�o�C�X�̓�������
		APIDevice& mAPIDevice;
		//! ��������
		Impl mImpl;


	};
}

#include "../src/BindLayout.inl"

#endif
