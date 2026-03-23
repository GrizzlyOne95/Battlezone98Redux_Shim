
/* Library Function - Multiple Matches With Same Base Name
    public: unsigned int __thiscall std::_Wrap_alloc<class std::allocator<char>
   >::max_size(void)const 
    public: unsigned int __thiscall std::_Wrap_alloc<class std::allocator<unsigned short>
   >::max_size(void)const 
    public: unsigned int __thiscall std::_Wrap_alloc<class std::allocator<wchar_t>
   >::max_size(void)const 
   
   Libraries: Visual Studio 2012 Debug, Visual Studio 2012 Release */

void __fastcall max_size(allocator<char> *param_1)

{
  std::allocator_traits<class_std::allocator<char>_>::max_size(param_1);
  return;
}

