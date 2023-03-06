/*****************************************************************//**
 * @file   Buffer.hpp
 * @brief  Buffer�N���X�̃w�b�_�t�@�C��
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

#include <optional>

namespace Hence
{
    // �O���錾
    template<typename API>
    class Device;

    // �O���錾
    template<typename API>
    class VRAMAllocator;

    /**
     * @brief  �o�b�t�@(VRAM��̃f�[�^�̈�)��\���N���X
     * @tparam API �o�b�N�G���h�Ɏg�p����API�^(API.hpp���Œ�`����Ă���)
     */
    template<typename API>
    class Buffer
    {
    public:
        // ���������^(��ʂɃ��[�U���g�p����K�v�͂Ȃ�)
        using Impl = APITrait<API>::BufferImpl;

        /**
         * @brief  �R���X�g���N�^
         * @param VRAMAllocator ���̃o�b�t�@�̊��蓖�Ăɗp����VRAMAllocator
         */
        Buffer(VRAMAllocator<API>& VRAMAllocator, const BufferInfo& bufferInfo) noexcept;

        /** 
         * @brief  �f�X�g���N�^
         */
        ~Buffer() noexcept;

        // �R�s�[�s��
        NONCOPYABLE(Buffer)

        Buffer(Buffer&& other) noexcept;

        Buffer& operator=(Buffer&& other) noexcept;

        Impl& getInternalImpl() noexcept;

        /**
         * @brief �o�b�t�@�Ƀf�[�^����������(�X�e�[�W���O�y�уR�}���h���s�R�X�g��������)
         * @tparam DataType �������ރf�[�^�̌^
         * @param data �������ރf�[�^��ArrayProxy(�z��/array/vector/initializer_list)
         */
        template <typename DataType>
        Result writeData(const ArrayProxy<DataType> data);

    private:
        using APIVRAMAllocator = APITrait<API>::VRAMAllocatorImpl;

        APIVRAMAllocator& mAPIVRAMAllocator;

        //! ��������
        std::optional<Impl> mImpl;
    };
}

#include "../src/Buffer.inl"

#endif
