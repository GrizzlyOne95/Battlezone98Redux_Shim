
/* Library Function - Multiple Matches With Same Base Name
    public: struct std::_Wrap_alloc<class std::allocator<char> > __thiscall std::_Wrap_alloc<class
   std::allocator<char> >::select_on_container_copy_construction(void)const 
    public: struct std::_Wrap_alloc<class std::allocator<unsigned short> > __thiscall
   std::_Wrap_alloc<class std::allocator<unsigned short>
   >::select_on_container_copy_construction(void)const 
    public: struct std::_Wrap_alloc<class std::allocator<wchar_t> > __thiscall
   std::_Wrap_alloc<class std::allocator<wchar_t>
   >::select_on_container_copy_construction(void)const 
   
   Library: Visual Studio 2012 Release */

undefined4 __thiscall select_on_container_copy_construction(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 local_5;
  
  uVar1 = select_on_container_copy_construction(&local_5,param_1);
  FUN_00423c20(uVar1);
  return param_2;
}

