#ifndef HENCE_SHADER_HPP_
#define HENCE_SHADER_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hence
{
	template<typename API>
	class Device;

	template<typename API>
	class Shader
	{
	public:
		using Impl = APITrait<API>::ShaderImpl;

		Shader(Device<API>& device);
		~Shader();

		NONCOPYABLE(Shader)


	private:
		using APIDevice = APITrait<API>::Device;

		APIDevice& mAPIDevice;
		Impl mImpl;
	};
}

#endif
