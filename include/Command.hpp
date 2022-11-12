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

#include <cstdint>

namespace Hence
{
    // 前方宣言
    template<typename API>
    class Device;

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

        /** 
         * @brief コンストラクタ
         *  
         * @param device 基とするデバイス
         */
        Command(Device<API>& device);

        /** 
         * @brief デストラクタ
         *  
         */
        ~Command();

        NONCOPYABLE(Command)

        /** 
         * @brief コマンド書き込み開始
         *  
         * @param renderpass 描画を行うRenderPass
         */
        Result begin(RenderPass& renderpass);

        /** 
         * @brief コンピュートモードでコマンド書き込み開始
         *  
         */
        Result beginCompute();

        /** 
         * @brief コマンド書き込み終了
         *  
         */
        Result end();

        /** 
         * @brief 使用する描画パイプラインをセットする
         *  
         * @param pipeline 使用する描画パイプライン
         */
        Result setGraphicsPipeline(const GraphicsPipeline<API>& pipeline);

        /**
         * @brief 使用するコンピュートパイプラインをセットする
         *
         * @param pipeline 使用するコンピュートパイプライン
         */
        Result setComputePipeline(const ComputePipeline<API>& pipeline);

        /** 
         * @brief 使用するレイトレースパイプラインをセットする
         *  
         * @param pipeline 使用するレイトレースパイプライン
         */
        Result setRaytracingPipeline(const RaytracingPipeline<API>& pipeline);

        /** 
         * @brief  使用するシェーダリソースのバインドグループをセットする
         *  
         * @param space 割り当てるspace(HLSL)
         * @param bindGroup 使用するバインドグループ
         */
        Result setBindGroup(const BindGroup<API>& bindGroup, const std::uint8_t space = 0);

        /** 
         * @brief 描画を行う
         *  
         */
        Result render();

        Result renderIndexed();

        Result execute();

        const Impl& getInternalImpl() const;

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mDevice;
        Impl mImpl;
    };
}

#endif
