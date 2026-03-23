
/* Library Function - Single Match
    protected: void __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::_DebugHeapAllocator<char> >::_Eos(unsigned int)
   
   Library: Visual Studio 2003 Debug */

void __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>::_Eos
          (basic_string<char,struct_std::char_traits<char>,class_std::_DebugHeapAllocator<char>_>
           *this,uint param_1)

{
  char *pcVar1;
  undefined1 *puVar2;
  undefined1 local_5;
  
  local_5 = 0;
  *(uint *)(this + 0x10) = param_1;
  puVar2 = &local_5;
  pcVar1 = _String_val<struct_std::_Simple_types<char>_>::_Myptr
                     ((_String_val<struct_std::_Simple_types<char>_> *)this);
  FUN_00416350(pcVar1 + param_1,puVar2);
  return;
}

