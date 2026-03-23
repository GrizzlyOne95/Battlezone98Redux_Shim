
/* Library Function - Multiple Matches With Same Base Name
    public: void __thiscall std::_String_alloc<0,struct std::_String_base_types<char,class
   std::allocator<char> > >::_Alloc_proxy(void)
    public: void __thiscall std::_String_alloc<0,struct std::_String_base_types<unsigned short,class
   std::allocator<unsigned short> > >::_Alloc_proxy(void)
    public: void __thiscall std::_String_alloc<0,struct std::_String_base_types<wchar_t,class
   std::allocator<wchar_t> > >::_Alloc_proxy(void)
    public: void __thiscall std::_Vector_alloc<0,struct std::_Vec_base_types<class
   std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> >,class
   std::allocator<class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > > >
   >::_Alloc_proxy(void)
     5 names - too many to list
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void Alloc_proxy(void)

{
  undefined4 uVar1;
  QuickBitSet local_14 [8];
  undefined4 *local_c;
  
  FUN_00417460();
  uVar1 = allocate(1);
  *local_c = uVar1;
  uVar1 = Concurrency::details::QuickBitSet::QuickBitSet(local_14);
  construct<>(*local_c,uVar1);
  *(undefined4 **)*local_c = local_c;
  return;
}

