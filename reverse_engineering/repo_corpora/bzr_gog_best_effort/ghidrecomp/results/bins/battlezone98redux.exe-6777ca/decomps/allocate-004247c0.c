
/* Library Function - Multiple Matches With Same Base Name
    public: char * __thiscall std::allocator<char>::allocate(unsigned int)
    public: unsigned short * __thiscall std::allocator<unsigned short>::allocate(unsigned int)
    public: class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __thiscall std::allocator<class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned
   char> > >::allocate(unsigned int)
    public: class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState *> > > * __thiscall std::allocator<class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState *> > > >::allocate(unsigned int)
     5 names - too many to list
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __thiscall allocate(undefined4 param_1,undefined4 param_2)

{
  FUN_00428050(param_2,0,param_1);
  return;
}

