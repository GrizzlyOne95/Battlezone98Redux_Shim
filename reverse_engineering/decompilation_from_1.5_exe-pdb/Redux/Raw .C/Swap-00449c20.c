
/* Library Function - Multiple Matches With Same Base Name
    protected: void __thiscall std::_Ptr_base<struct _EXCEPTION_RECORD const >::_Swap(class
   std::_Ptr_base<struct _EXCEPTION_RECORD const > &)
    protected: void __thiscall std::_Ptr_base<class __ExceptionPtr>::_Swap(class
   std::_Ptr_base<class __ExceptionPtr> &)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

void __thiscall Swap(int param_1,int param_2)

{
  swap<>(param_1,param_2);
  swap<>(param_1 + 4,param_2 + 4);
  return;
}

