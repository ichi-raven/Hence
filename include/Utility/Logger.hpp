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
        static void info(const std::string_view format, Args&& ... args)
        {
            /* �����t�H�[�}�b�g���ăV���O���g���C���X�^���X��Information���O�o�͌Ăяo�� */
            Logger::getInstance().logInfo(std::format(format, std::forward<Args>(args) ...));
        }


        /**
         * @brief  warning���o�͂���
         * @tparam Args �t�H�[�}�b�g�^
         * @param format ����
         * @param args �������͂ɑ΂���ϒ�����
         */
        template<typename ... Args>
        static void warn(const std::string_view format, Args&& ... args)
        {
            /* �����t�H�[�}�b�g���ăV���O���g���C���X�^���X��Warning���O�o�͌Ăяo�� */
            Logger::getInstance().logWarn(std::format(format, std::forward<Args>(args) ...));
        }


        /**
         * @brief  error���o�͂���
         * @tparam Args �t�H�[�}�b�g�^
         * @param format ����
         * @param args �������͂ɑ΂���ϒ�����
         */
        template<typename ... Args>
        static void error(const std::string_view format, Args&& ... args)
        {
            /* �����t�H�[�}�b�g���ăV���O���g���C���X�^���X��Error���O�o�͌Ăяo�� */
            Logger::getInstance().logError(std::format(format, std::forward<Args>(args) ...));
        }


    private:
        /* Information���O�o�� */
        inline void logInfo(const std::string_view message);
        /* Warning���O�o�� */
        inline void logWarn(const std::string_view message);
        /* Error���O�o�� */
        inline void logError(const std::string_view message);

    private:
        std::mutex mMutex;
        std::ofstream mFStream;
    };
}

#endif
