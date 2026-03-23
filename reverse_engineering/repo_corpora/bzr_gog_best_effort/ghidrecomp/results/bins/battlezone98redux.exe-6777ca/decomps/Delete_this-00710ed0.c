
/* Library Function - Multiple Matches With Same Base Name
    private: virtual void __thiscall std::_Func_impl<struct std::_Callable_obj<class
   <lambda_3360e8f09260526cc68b047d56218705>,0>,class std::allocator<class
   std::_Func_class<void,unsigned int const &,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil> >,void,unsigned int const &,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil>::_Delete_this(bool)
    private: virtual void __thiscall std::_Func_impl<struct std::_Callable_obj<class
   <lambda_399686a4a5619bf4b18c998976ba8b81>,0>,class std::allocator<class
   std::_Func_class<void,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil> >,void,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil>::_Delete_this(bool)
    private: virtual void __thiscall std::_Func_impl<struct std::_Callable_obj<class
   <lambda_9ab38a79c03e1e04423ad6818173354b>,0>,class std::allocator<class
   std::_Func_class<void,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil> >,void,struct std::_Nil,struct std::_Nil,struct
   std::_Nil,struct std::_Nil,struct std::_Nil,struct std::_Nil,struct
   std::_Nil>::_Delete_this(bool)
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __thiscall Delete_this(int param_1,char param_2)

{
  allocator<>(param_1 + 0x10);
  destroy<>(param_1);
  if (param_2 != '\0') {
    FUN_00417180(param_1,1);
  }
  return;
}

