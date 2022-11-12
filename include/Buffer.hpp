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

namespace Hense
{
    // �O���錾
    template<typename API>
    class Device;

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
         *
         * @param device ��Ƃ���f�o�C�X
         * @param impl ��������
         */
        Buffer(Device<API>& device, Impl& impl);

        /** 
         * @brief  �f�X�g���N�^
         *  
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
        using APIDevice = APITrait<API>::Device;

        //! �f�o�C�X�̓�������
        APIDevice& mAPIDevice;
        //! ��������
        Impl mImpl;
    };
}

#endif
