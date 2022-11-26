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
#include "Utility/Result.hpp"
#include "Utility/ArrayProxy.hpp"

namespace Hence
{
    // 前方宣言
    template<typename API>
    class Device;

    // 前方宣言
    template<typename API>
    class VRAMAllocator;

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
         * @param VRAMAllocator このバッファの割り当てに用いるVRAMAllocator
         */
        Buffer(VRAMAllocator<API>& VRAMAllocator);

        /** 
         * @brief  デストラクタ
         */
        ~Buffer();

        // コピー不可
        NONCOPYABLE(Buffer)

        /**
         * @brief バッファにデータを書き込む(ステージング及びコマンド実行コストがかかる)
         * @tparam DataType 書き込むデータの型
         * @param data 書き込むデータのArrayProxy(配列/array/vector/initializer_list)
         */
        template <typename DataType>
        Result writeData(const ArrayProxy<DataType> data);

    private:
        using APIVRAMAllocator = APITrait<API>::VRAMAllocatorImpl;

        APIVRAMAllocator& mAPIVRAMAllocator;

        //! 内部実装
        Impl mImpl;
    };
}

#endif
