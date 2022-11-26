/*****************************************************************//**
 * @file   Macro.hpp
 * @brief  �J���������p�}�N���̒�`(��ʓI�Ȃ��̂Ɍ���)
 * 
 * @author ichi-raven
 * @date   November 2022
 *********************************************************************/
#ifndef HENCE_MACRO_HPP_
#define HENCE_MACRO_HPP_

// �N���X�̃R�s�[�s��`
#define NONCOPYABLE(TypeName)\
    TypeName(const TypeName& other) = delete;\
    TypeName& operator=(TypeName& other) = delete;

// �N���X�̃��[�u�s��`
#define NONMOVABLE(TypeName)\
    TypeName(const TypeName&& other) = delete;\
    TypeName&& operator=(TypeName&& other) = delete;

#endif
