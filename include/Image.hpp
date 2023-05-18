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

    // destruct�ł��Ȃ��\�����K�v
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
         * @brief �摜�Ƀf�[�^����������(�X�e�[�W���O�y�уR�}���h���s�R�X�g��������)
         * @tparam DataType �������ރf�[�^�̌^
         * @param data �������ރf�[�^��ArrayProxy(�z��/array/vector/initializer_list)
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
