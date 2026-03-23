
/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall std::_Ptr_base<struct Concurrency::details::_Task_impl<unsigned char>
   >::_Assign_rv(class std::_Ptr_base<struct Concurrency::details::_Task_impl<unsigned char> > &&)
    public: void __thiscall std::_Ptr_base<struct Concurrency::details::_Task_impl<struct
   std::pair<unsigned char,class Concurrency::details::_CancellationTokenState *> >
   >::_Assign_rv(class std::_Ptr_base<struct Concurrency::details::_Task_impl<struct
   std::pair<unsigned char,class Concurrency::details::_CancellationTokenState *> > > &&)
    public: void __thiscall std::_Ptr_base<struct
   Concurrency::details::_ExceptionHolder>::_Assign_rv(class std::_Ptr_base<struct
   Concurrency::details::_ExceptionHolder> &&)
    public: void __thiscall std::_Ptr_base<class __ExceptionPtr>::_Assign_rv(class
   std::_Ptr_base<class __ExceptionPtr> &&)
     5 names - too many to list
   
   Libraries: Visual Studio 2010 Debug, Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __thiscall Assign_rv(int param_1,int param_2)

{
  if (param_1 != param_2) {
    Swap(param_2);
  }
  return;
}

