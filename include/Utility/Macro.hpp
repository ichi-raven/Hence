#ifndef HENCE_MACRO_HPP_
#define HENCE_MACRO_HPP_

#define NONCOPYABLE(TypeName)\
    TypeName(TypeName& other) = delete;\
    TypeName& operator=(TypeName& other) = delete;

#endif
