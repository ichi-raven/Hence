#ifndef HENCE_IMAGE_HPP_
#define HENCE_IMAGE_HPP_

#include "API.hpp"
#include "Utility/Macro.hpp"
#include "Utility/ArrayProxy.hpp"

#include <optional>

namespace Hence
{
    template<typename API>
    class Device;

    // destructできない構造が必要
    template<typename API>
    class Image
    {
    public:

        using Impl = APITrait<API>::ImageImpl;

        Image() noexcept;

        Image(VRAMAllocator<API>& VRAMAllocator, const ImageInfo& imageInfo) noexcept;
        
        ~Image() noexcept;

        NONCOPYABLE(Image)

        Impl& getInternalImpl() noexcept;

        /**
         * @brief 画像にデータを書き込む(ステージング及びコマンド実行コストがかかる)
         * @tparam DataType 書き込むデータの型
         * @param data 書き込むデータのArrayProxy(配列/array/vector/initializer_list)
         */
        template <typename DataType>
        Result write(const ArrayProxy<DataType> data) noexcept;

    private:
        using APIVRAMAllocator = APITrait<API>::VRAMAllocatorImpl;

        APIVRAMAllocator* mpAPIVRAMAllocator;
        std::optional<Impl> mImpl;
    };
}

#include "../src/Image.inl"

#endif
