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

		Shader(Device<API>& device, std::string_view path);

		~Shader();

		NONCOPYABLE(Shader);

		Impl& getInternalImpl();

	private:
		using APIDevice = APITrait<API>::Device;

		APIDevice& mAPIDevice;
		Impl mImpl;
	};
}

#include "../src/Shader.inl"

#endif
