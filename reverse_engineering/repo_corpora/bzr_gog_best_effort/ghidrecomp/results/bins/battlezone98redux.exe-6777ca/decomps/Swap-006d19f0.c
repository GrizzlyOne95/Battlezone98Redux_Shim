
/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall std::_Ptr_base<struct Concurrency::details::_Task_impl<unsigned char>
   >::_Swap(class std::_Ptr_base<struct Concurrency::details::_Task_impl<unsigned char> > &)
    public: void __thiscall std::_Ptr_base<struct Concurrency::details::_Task_impl<struct
   std::pair<unsigned char,class Concurrency::details::_CancellationTokenState *> > >::_Swap(class
   std::_Ptr_base<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState *> > > &)
    public: void __thiscall std::_Ptr_base<struct
   Concurrency::details::_ExceptionHolder>::_Swap(class std::_Ptr_base<struct
   Concurrency::details::_ExceptionHolder> &)
    public: void __thiscall std::_Ptr_base<class __ExceptionPtr>::_Swap(class std::_Ptr_base<class
   __ExceptionPtr> &)
     5 names - too many to list
   
   Libraries: Visual Studio 2010 Debug, Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __thiscall Swap(int param_1,int param_2)

{
  swap<>(param_1 + 4,param_2 + 4);
  swap<>(param_1,param_2);
  return;
}

