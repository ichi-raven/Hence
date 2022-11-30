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
        static void info(const char* format, Args&& ... args)
        {
            /* 書式フォーマットしてシングルトンインスタンスのInfoログ出力呼び出し */
            Logger::getInstance().logInfo(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
        }


        /**
         * @brief  warningを出力する
         * @tparam Args フォーマット型
         * @param format 書式
         * @param args 書式入力に対する可変長引数
         */
        template<typename ... Args>
        static void warn(const char* format, Args&& ... args)
        {
            /* 書式フォーマットしてシングルトンインスタンスのWarnログ出力呼び出し */
            Logger::getInstance().logWarn(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
        }


        /**
         * @brief  errorを出力する
         * @tparam Args フォーマット型
         * @param format 書式
         * @param args 書式入力に対する可変長引数
         */
        template<typename ... Args>
        static void error(const char* format, Args&& ... args)
        {
            /* 書式フォーマットしてシングルトンインスタンスのErrorログ出力呼び出し */
            Logger::getInstance().logError(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
        }


    private:
        /**
         * @brief  infoを出力する内部メソッド
         */
        inline void logInfo(const std::string&& message);
        /* Warningログ出力 */
        inline void logWarn(const std::string&& message);
        /* Errorログ出力 */
        inline void logError(const std::string&& message);

    private:
        //! スレッドセーフ用
        std::mutex mMutex;
        //! 出力先
        std::ofstream mFStream;
    };
}

#endif
