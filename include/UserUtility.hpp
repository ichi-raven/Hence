/*****************************************************************//**
 * @file   UserUtility.hpp
 * @brief  ユーザ用ユーティリティ関数
 *
 * @author ichi-raven
 * @date   May 2023
 *********************************************************************/
#ifndef HENCE_USER_UTILITY_HPP_
#define HENCE_USER_UTILITY_HPP_

#include "Utility/Result.hpp"
#include "Window.hpp"
#include "Command.hpp"
#include "Semaphore.hpp"

#include <cstdint>
#include <array>
#include <functional>


namespace Hence
{
	template<typename API, std::uint32_t kFrameBufferNum>
	Result render
	(
		Window<API>& window,
		std::array<Command<API>, kFrameBufferNum>& commands,
		std::array<Semaphore<API>, kFrameBufferNum>& renderCompletedSemaphores,
		std::array<Semaphore<API>, kFrameBufferNum>& frameBufferReadySemaphores,
		const std::uint32_t frameIndex,
		std::function<Result(Command<API>&, const std::uint32_t)> commandRecordingProc
	)
	{
		assert
		(
			(
				commands.size() == renderCompletedSemaphores.size()
				&&
				commands.size() == frameBufferReadySemaphores.size()
				)
			|| !"invalid commands or semaphores size!"
		);

		const std::uint32_t imageIndex = window.acquireNextImage(frameBufferReadySemaphores[frameIndex]);

		auto& command = commands[frameIndex];

		if (FAILED(res, commandRecordingProc(command, imageIndex)))
		{
			return res;
		}

		if (FAILED(res, command.execute(frameBufferReadySemaphores[frameIndex], renderCompletedSemaphores[frameIndex])))
		{
			return res;
		}

		if (FAILED(res, window.present(imageIndex, renderCompletedSemaphores[frameIndex])))
		{
			return res;
		}

		return Result();
	}
}

#endif