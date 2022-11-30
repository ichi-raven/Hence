/*****************************************************************//**
 * @file   Device.hpp
 * @brief  デバイスクラスのヘッダファイル
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_DEVICE_HPP_
#define HENCE_DEVICE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"

#include <optional>

namespace Hence
{
    /**
     * @brief  デバイスクラス，ここを起点としてライブラリの各機能を使用する
     * @tparam API バックエンドに使用するAPI型(API.hpp内で定義されている)
     */
    template<typename API>
    class Device
    {
    public:
        using APIDevice = APITrait<API>::Device;

        /** 
         * @brief  デフォルトコンストラクタ
         *  
         */
        Device();

        /** 
         * @brief  デストラクタ
         *  
         */
        ~Device();

        // コピー不可
        NONCOPYABLE(Device)

        ///** 
        // * @brief  明示的に初期化する
        // *  
        // */
        //void initialize();


        ///** 
        // * @brief  明示的に破棄する
        // *  
        // */
        //void destroy();

        APIDevice& getInternalAPIDevice();

    private:

        std::optional<APIDevice> mAPIDevice;
    };
}

// 実装展開
#include "../src/Device.inl"

#endif
