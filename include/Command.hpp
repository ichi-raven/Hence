/*****************************************************************//**
 * @file   Command.hpp
 * @brief  Commandクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_COMMAND_HPP_
#define HENCE_COMMAND_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"
#include "Utility/ArrayProxy.hpp"

#include "Info/ClearValue.hpp"
#include "Info/ImageLayout.hpp"

#include <cstdint>

namespace Hence
{
    // 前方宣言
    template<typename API>
    class Device;

    // 前方宣言
    template<typename API>
    class Semaphore;

    // 前方宣言
    template<typename API>
    class GraphicsPipeline;

    // 前方宣言
    template<typename API>
    class ComputePipeline;

    // 前方宣言
    template<typename API>
    class RaytracingPipeline;

    // 前方宣言
    template<typename API>
    class BindGroup;

    template<typename API>
    class RenderPass;

    /**
     * @brief  GPUに送信するコマンドを表すクラス
     * @tparam API バックエンドに使用するAPI型(API.hpp内で定義されている)
     */
    template<typename API>
    class Command
    {
    public:
        // 内部実装型(一般にユーザが使用する必要はない)
        using Impl = APITrait<API>::CommandImpl;

        Command() noexcept;

        /** 
         * @brief コンストラクタ
         *  
         * @param device 基とするデバイス
         */
        Command(Device<API>& device) noexcept;

        /** 
         * @brief デストラクタ
         *  
         */
        ~Command() noexcept;

        NONCOPYABLE(Command);

        Command(Command<API>&& src) noexcept;
        Command<API>& operator=(Command<API>&& src) noexcept;


        /** 
         * @brief コマンド書き込み開始
         *  
         * @param renderpass 描画を行うRenderPass
         */
        Result begin(RenderPass<API>& renderpass, const uint32_t frameBufferIndex, ArrayProxy<ColorClearValue> ccvs, const DepthClearValue& dcv) noexcept;

        /** 
         * @brief コンピュートモードでコマンド書き込み開始
         *  
         */
        Result beginCompute() noexcept;

        /** 
         * @brief コマンド書き込み終了
         *  
         */
        Result end() noexcept;

        /** 
         * @brief 使用する描画パイプラインをセットする
         *  
         * @param pipeline 使用する描画パイプライン
         */
        Result setGraphicsPipeline(GraphicsPipeline<API>& pipeline) noexcept;

        /**
         * @brief 使用するコンピュートパイプラインをセットする
         *
         * @param pipeline 使用するコンピュートパイプライン
         */
        Result setComputePipeline(ComputePipeline<API>& pipeline) noexcept;

        /** 
         * @brief 使用するレイトレースパイプラインをセットする
         *  
         * @param pipeline 使用するレイトレースパイプライン
         */
        Result setRaytracingPipeline(RaytracingPipeline<API>& pipeline) noexcept;

        /** 
         * @brief  使用するシェーダリソースのバインドグループをセットする
         *  
         * @param space 割り当てるspace(HLSL)
         * @param bindGroup 使用するバインドグループ
         */
        Result setBindGroup(BindGroup<API>& bindGroup) noexcept;

        /** 
         * @brief  頂点バッファをセットする
         *  
         * @return 結果
         */
        Result setVertexBuffer(Buffer<API>& vertexBuffer) noexcept;

        /**
         * @brief  インデックスバッファをセットする
         */
        Result setIndexBuffer(Buffer<API>& indexBuffer) noexcept;

        /** 
         * @brief 描画を行う
         *  
         */
        Result render(const std::uint32_t vertexCount, const std::uint32_t instanceCount, const std::uint32_t firstVertex, const std::uint32_t firstInstance) noexcept;

        Result renderIndexed(const std::uint32_t indexCount, const std::uint32_t instanceCount, const std::uint32_t firstIndex, const std::uint32_t vertexOffset, const std::uint32_t firstInstance) noexcept;

        Result barrier(Image<API>& image, ImageLayout from, ImageLayout to) noexcept;

        Result execute(Semaphore<API>& waitSemaphore, Semaphore<API>& signalSemaphore) noexcept;

        Impl& getInternalImpl() noexcept;

    private:
        //using APIDevice = APITrait<API>::Device;

        //APIDevice& mAPIDevice;
        std::optional<Impl> mImpl;
    };
}

#include "../src/Command.inl"

#endif
