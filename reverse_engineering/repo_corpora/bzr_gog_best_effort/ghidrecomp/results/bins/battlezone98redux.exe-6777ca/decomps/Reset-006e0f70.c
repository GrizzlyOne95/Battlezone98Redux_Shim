
/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall std::_Ptr_base<struct Concurrency::details::_Task_impl<unsigned char>
   >::_Reset(struct Concurrency::details::_Task_impl<unsigned char> *,class std::_Ref_count_base *)
    public: void __thiscall std::_Ptr_base<struct
   Concurrency::details::_ExceptionHolder>::_Reset(struct Concurrency::details::_ExceptionHolder
   *,class std::_Ref_count_base *)
    public: void __thiscall std::_Ptr_base<struct
   Concurrency::details::_Task_impl_base>::_Reset(struct Concurrency::details::_Task_impl_base
   *,class std::_Ref_count_base *)
    public: void __thiscall std::_Ptr_base<class __ExceptionPtr>::_Reset(class __ExceptionPtr
   *,class std::_Ref_count_base *)
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __thiscall
Reset(_Ptr_base<class___ExceptionPtr> *param_1,__ExceptionPtr *param_2,_Ref_count_base *param_3)

{
  if (param_3 != (_Ref_count_base *)0x0) {
    std::_Ref_count_base::_Incref(param_3);
  }
  std::tr1::_Ptr_base<class___ExceptionPtr>::_Reset0(param_1,param_2,(_Ref_count_base *)param_3);
  return;
}

