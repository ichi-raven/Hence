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
        Buffer(VRAMAllocator<API>& VRAMAllocator);

        /** 
         * @brief  �f�X�g���N�^
         */
        ~Buffer();

        // �R�s�[�s��
        NONCOPYABLE(Buffer)

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
        Impl mImpl;
    };
}

#endif
