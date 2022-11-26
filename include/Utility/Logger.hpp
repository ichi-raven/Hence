/*****************************************************************//**
 * @file   Logger.hpp
 * @brief  Loggerクラスのヘッダファイル
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
     * @brief  ログの出力を管理するクラス
     */
    class Logger
    {
    private:
        /**
         * @brief  コンストラクタ
         * @detail シングルトン
         */
        Logger();

        /**
         * @brief  デストラクタ
         * @detail シングルトン
         */
        ~Logger();

        /**
         * @brief  インスタンス取得メソッド
         * @detail シングルトン
         */
        static Logger& getInstance() noexcept;

    public:

        // コピー不可
        NONCOPYABLE(Logger)
        // ムーブ不可
        NONMOVABLE(Logger)

        /**
         * @brief  informationを出力する
         * @tparam Args フォーマット型
         * @param format 書式
         * @param args 書式入力に対する可変長引数
         */
        template<typename ... Args>
        static void info(const std::string_view format, Args&& ... args)
        {
            /* 書式フォーマットしてシングルトンインスタンスのInformationログ出力呼び出し */
            Logger::getInstance().logInfo(std::format(format, std::forward<Args>(args) ...));
        }


        /**
         * @brief  warningを出力する
         * @tparam Args フォーマット型
         * @param format 書式
         * @param args 書式入力に対する可変長引数
         */
        template<typename ... Args>
        static void warn(const std::string_view format, Args&& ... args)
        {
            /* 書式フォーマットしてシングルトンインスタンスのWarningログ出力呼び出し */
            Logger::getInstance().logWarn(std::format(format, std::forward<Args>(args) ...));
        }


        /**
         * @brief  errorを出力する
         * @tparam Args フォーマット型
         * @param format 書式
         * @param args 書式入力に対する可変長引数
         */
        template<typename ... Args>
        static void error(const std::string_view format, Args&& ... args)
        {
            /* 書式フォーマットしてシングルトンインスタンスのErrorログ出力呼び出し */
            Logger::getInstance().logError(std::format(format, std::forward<Args>(args) ...));
        }


    private:
        /**
         * @brief  infoを出力する内部メソッド
         */
        inline void logInfo(const std::string_view message);
        /* Warningログ出力 */
        inline void logWarn(const std::string_view message);
        /* Errorログ出力 */
        inline void logError(const std::string_view message);

    private:
        //! スレッドセーフ用
        std::mutex mMutex;
        //! 出力先
        std::ofstream mFStream;
    };

//    class DebugLogger
//    {
//
//        /**
//         * @brief  informationを出力する
//         * @tparam Args フォーマット型
//         * @param format 書式
//         * @param args 書式入力に対する可変長引数
//         */
//        template<typename ... Args>
//        static void info(const std::string_view format, Args&& ... args)
//        {
//#ifndef NDEBUG
//            Logger::info(format, args...);
//#endif
//        }
//
//
//        /**
//         * @brief  warningを出力する
//         * @tparam Args フォーマット型
//         * @param format 書式
//         * @param args 書式入力に対する可変長引数
//         */
//        template<typename ... Args>
//        static void warn(const std::string_view format, Args&& ... args)
//        {
//#ifndef NDEBUG
//            Logger::warn(format, args...);
//#endif
//        }
//
//
//        /**
//         * @brief  errorを出力する
//         * @tparam Args フォーマット型
//         * @param format 書式
//         * @param args 書式入力に対する可変長引数
//         */
//        template<typename ... Args>
//        static void error(const std::string_view format, Args&& ... args)
//        {
//#ifndef NDEBUG
//            Logger::error(format, args...);
//#endif
//        }
//    };
}

#endif
