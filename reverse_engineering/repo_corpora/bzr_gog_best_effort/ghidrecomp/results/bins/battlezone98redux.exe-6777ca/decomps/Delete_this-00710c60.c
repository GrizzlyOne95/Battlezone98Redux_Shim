
/* Library Function - Multiple Matches With Same Base Name
    private: virtual void __thiscall std::_Func_impl<struct std::_Callable_fun<bool
   (__cdecl*const)(enum Concurrency::agent_status const &),0>,class std::allocator<class
   std::_Func_class<bool,enum Concurrency::agent_status const &,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil> >,bool,enum
   Concurrency::agent_status const &,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil>::_Delete_this(bool)
    private: virtual void __thiscall std::_Func_impl<struct std::_Callable_obj<class
   <lambda_22c800ac295261976027df48869e3267>,0>,class std::allocator<class
   std::_Func_class<void,class Concurrency::message<unsigned int> *,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil> >,void,class
   Concurrency::message<unsigned int> *,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil>::_Delete_this(bool)
    private: virtual void __thiscall std::_Func_impl<struct std::_Callable_obj<class
   <lambda_4e87154fcdc8e0d2e24a6503682ed39a>,0>,class std::allocator<class
   std::_Func_class<void,class Concurrency::message<unsigned int> *,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil> >,void,class
   Concurrency::message<unsigned int> *,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil>::_Delete_this(bool)
    private: virtual void __thiscall std::_Func_impl<struct std::_Callable_obj<class
   <lambda_a950f64d47c771b1d34af4af122ee0c4>,0>,class std::allocator<class
   std::_Func_class<void,class Concurrency::message<enum Concurrency::agent_status> *,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil>
   >,void,class Concurrency::message<enum Concurrency::agent_status> *,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil>::_Delete_this(bool)
     8 names - too many to list
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __thiscall Delete_this(int param_1,char param_2)

{
  allocator<>(param_1 + 8);
  destroy<>(param_1);
  if (param_2 != '\0') {
    FUN_00417180(param_1,1);
  }
  return;
}

