
/* Library Function - Multiple Matches With Same Base Name
    protected: void __thiscall std::_Ptr_base<struct _EXCEPTION_RECORD const >::_Decref(void)
    public: void __thiscall std::_Ptr_base<struct
   Concurrency::details::_Task_completion_event_impl<unsigned char> >::_Decref(void)
    public: void __thiscall std::_Ptr_base<struct
   Concurrency::details::_Task_completion_event_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState *> > >::_Decref(void)
    public: void __thiscall std::_Ptr_base<struct Concurrency::details::_Task_impl<unsigned char>
   >::_Decref(void)
     9 names - too many to list
   
   Libraries: Visual Studio 2010, Visual Studio 2012, Visual Studio 2019 */

void __fastcall Decref(int param_1)

{
  if (*(int *)(param_1 + 4) != 0) {
    Decwref();
  }
  return;
}

