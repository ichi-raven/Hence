/*****************************************************************//**
 * @file   Macro.hpp
 * @brief  開発効率化用マクロの定義(一般的なものに限る)
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_MACRO_HPP_
#define HENCE_MACRO_HPP_

// クラスのコピー不可定義
#define NONCOPYABLE(TypeName)\
    TypeName(const TypeName& other) = delete;\
    TypeName& operator=(TypeName& other) = delete;

// クラスのムーブ不可定義
#define NONMOVABLE(TypeName)\
    TypeName(const TypeName&& other) = delete;\
    TypeName&& operator=(TypeName&& other) = delete;

#endif
