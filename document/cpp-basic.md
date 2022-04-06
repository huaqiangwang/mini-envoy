# CPP Rules

## scoped & unscoped enumeration

- How to define and name it, more flexible than C standard
- Namespace and enumeration
- Type and static cast. Create an enumeration type mixed with several pre-defined types
- is_enum, is_scoped_enum, to_underlying, underlying_type

## std::function

Class template std::function is a general-purpose polymorphic function wrapper.
Instances of std::function can store, copy, and invoke any CopyConstructible Callable
target -- functions, lambda expressions, bind expressions, or other function objects,
as well as pointers to member functions and pointers to data members.
The stored callable object is called the target of std::function.
If a std::function contains no target, it is called empty. Invoking the target of an empty
std::function results in std::bad_function_call exception being thrown.
std::function satisfies the requirements of *CopyConstructible?* and *CopyAssignable?*.

## define a template function & class and create an instance of one of them

## define: compiling text replacement
'#define PURE = 0'

## 