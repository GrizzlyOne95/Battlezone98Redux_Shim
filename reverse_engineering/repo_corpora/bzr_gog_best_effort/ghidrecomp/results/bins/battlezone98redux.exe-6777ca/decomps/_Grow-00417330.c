
/* Library Function - Single Match
    public: bool __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::_Grow(unsigned int,bool)
   
   Library: Visual Studio 2012 Release */

bool __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Grow
          (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *this,
          uint param_1,bool param_2)

{
  uint uVar1;
  uint local_c;
  
  uVar1 = ::FID_conflict_max_size();
  if (uVar1 < param_1) {
    FUN_00417420();
  }
  if (*(uint *)(this + 0x14) < param_1) {
    FUN_00417510(param_1,*(undefined4 *)(this + 0x10));
  }
  else if ((param_2) && (param_1 < 0x10)) {
    if (param_1 < *(uint *)(this + 0x10)) {
      local_c = param_1;
    }
    else {
      local_c = *(uint *)(this + 0x10);
    }
    FID_conflict__Tidy(1,local_c);
  }
  else if (param_1 == 0) {
    basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
              ((basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
                *)this,0);
  }
  return param_1 != 0;
}

