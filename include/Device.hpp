/*****************************************************************//**
 * @file   Device.hpp
 * @brief  �f�o�C�X�N���X�̃w�b�_�t�@�C��
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
     * @brief  �f�o�C�X�N���X�C�������N�_�Ƃ��ă��C�u�����̊e�@�\���g�p����
     * @tparam API �o�b�N�G���h�Ɏg�p����API�^(API.hpp���Œ�`����Ă���)
     */
    template<typename API>
    class Device
    {
    public:
        using APIDevice = APITrait<API>::Device;

        /** 
         * @brief  �f�t�H���g�R���X�g���N�^
         *  
         */
        Device();

        /** 
         * @brief  �f�X�g���N�^
         *  
         */
        ~Device();

        // �R�s�[�s��
        NONCOPYABLE(Device)

        ///** 
        // * @brief  �����I�ɏ���������
        // *  
        // */
        //void initialize();


        ///** 
        // * @brief  �����I�ɔj������
        // *  
        // */
        //void destroy();

        APIDevice& getInternalAPIDevice();

    private:

        std::optional<APIDevice> mAPIDevice;
    };
}

// �����W�J
#include "../src/Device.inl"

#endif
