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
#include "Utility/ArrayProxy.hpp"

namespace Hence
{
	template<typename API>
	class Shader;

	template<typename API>
	class BindLayout
	{
	public:
		using Impl = APITrait<API>::BindLayoutImpl;

		BindLayout(const Shader<API>& shader);

		BindLayout(ArrayProxy<uint8_t> bufferBinding, ArrayProxy<uint8_t> imageBinding, ArrayProxy<uint8_t> samplerBinding);

		NONCOPYABLE(BindLayout);

		Impl& getInternalImpl();

	private:
		using APIDevice = APITrait<API>::Device;

		//! �f�o�C�X�̓�������
		APIDevice& mAPIDevice;
		//! ��������
		Impl mImpl;


	};
}

#endif
