/*****************************************************************//**
 * @file   Logger.hpp
 * @brief  Logger�N���X�̃w�b�_�t�@�C��
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_UTILITY_LOG_HPP_
#define HENCE_UTILITY_LOG_HPP_

#include "Macro.hpp"

#include <string>
#include <string_view>
#include <fstream>
#include <mutex>
#include <format>

namespace Hence
{
    /**
     * @brief  ���O�̏o�͂��Ǘ�����N���X
     */
    class Logger
    {
    private:
        /**
         * @brief  �R���X�g���N�^
         * @detail �V���O���g��
         */
        Logger();

        /**
         * @brief  �f�X�g���N�^
         * @detail �V���O���g��
         */
        ~Logger();

        /**
         * @brief  �C���X�^���X�擾���\�b�h
         * @detail �V���O���g��
         */
        static Logger& getInstance() noexcept;

    public:

        // �R�s�[�s��
        NONCOPYABLE(Logger)
        // ���[�u�s��
        NONMOVABLE(Logger)

        /**
         * @brief  information���o�͂���
         * @tparam Args �t�H�[�}�b�g�^
         * @param format ����
         * @param args �������͂ɑ΂���ϒ�����
         */
        template<typename ... Args>
        static void info(const char* format, Args&& ... args)
        {
            /* �����t�H�[�}�b�g���ăV���O���g���C���X�^���X��Info���O�o�͌Ăяo�� */
            Logger::getInstance().logInfo(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
        }


        /**
         * @brief  warning���o�͂���
         * @tparam Args �t�H�[�}�b�g�^
         * @param format ����
         * @param args �������͂ɑ΂���ϒ�����
         */
        template<typename ... Args>
        static void warn(const char* format, Args&& ... args)
        {
            /* �����t�H�[�}�b�g���ăV���O���g���C���X�^���X��Warn���O�o�͌Ăяo�� */
            Logger::getInstance().logWarn(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
        }


        /**
         * @brief  error���o�͂���
         * @tparam Args �t�H�[�}�b�g�^
         * @param format ����
         * @param args �������͂ɑ΂���ϒ�����
         */
        template<typename ... Args>
        static void error(const char* format, Args&& ... args)
        {
            /* �����t�H�[�}�b�g���ăV���O���g���C���X�^���X��Error���O�o�͌Ăяo�� */
            Logger::getInstance().logError(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
        }


    private:
        /**
         * @brief  info���o�͂���������\�b�h
         */
        inline void logInfo(const std::string&& message);
        /* Warning���O�o�� */
        inline void logWarn(const std::string&& message);
        /* Error���O�o�� */
        inline void logError(const std::string&& message);

    private:
        //! �X���b�h�Z�[�t�p
        std::mutex mMutex;
        //! �o�͐�
        std::ofstream mFStream;
    };
}

#endif
