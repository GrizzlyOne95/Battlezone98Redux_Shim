
/* Library Function - Multiple Matches With Same Base Name
    private: virtual void __thiscall std::_Ref_count<class __ExceptionPtr>::_Delete_this(void)
    private: virtual void __thiscall std::_Ref_count_obj<struct
   Concurrency::details::_ExceptionHolder>::_Delete_this(void)
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __fastcall Delete_this(int *param_1)

{
  if (param_1 != (int *)0x0) {
    (**(code **)(*param_1 + 8))(1);
  }
  return;
}

