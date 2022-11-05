/*****************************************************************//**
 * @file   Buffer.hpp
 * @brief  Bufferクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_BUFFER_HPP_
#define HENCE_BUFFER_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

namespace Hense
{
    // 前方宣言
    template<typename API>
    class Device;

    // destructできない構造が必要
    /**
     * @brief  バッファ(VRAM上のデータ領域)を表すクラス
     * @tparam API バックエンドに使用するAPI型(API.hpp内で定義されている)
     */
    template<typename API>
    class Buffer
    {
    public:
        // 内部実装型(一般にユーザが使用する必要はない)
        using Impl = APITrait<API>::BufferImpl;

        /**
         * @brief  コンストラクタ
         *
         * @param device 基とするデバイス
         * @param impl 内部実装
         */
        Buffer(Device<API>& device, Impl& impl);

        /** 
         * @brief  デストラクタ
         *  
         */
        ~Buffer();

        // コピー不可
        NONCOPYABLE(Buffer)

        /**
         * @brief バッファにデータを書き込む(ステージング及びコマンド実行コストがかかる)
         * @tparam DataType 書き込むデータの**各要素**の型
         * @param data 書き込むデータのArrayProxy(配列/array/vector/initializer_list)
         */
        template <typename DataType>
        void writeData(const ArrayProxy<DataType> data);

    private:
        using APIDevice = APITrait<API>::Device;

        APIDevice& mDevice;
        Impl mImpl;
    };
}

#endif
