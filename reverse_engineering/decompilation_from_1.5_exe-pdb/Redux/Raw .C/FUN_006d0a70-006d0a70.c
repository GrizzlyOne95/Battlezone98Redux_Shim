
undefined4 __thiscall FUN_006d0a70(allocator<char> *param_1,undefined4 param_2)

{
  int iVar1;
  allocator<char> *this;
  undefined4 uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_5;
  
  pbVar3 = &local_5;
  iVar1 = std::allocator<char>::allocator<char>(param_1);
  this = (allocator<char> *)
         std::_DebugHeapString::_DebugHeapString((_DebugHeapString *)(iVar1 + 4),pbVar3);
  uVar2 = std::allocator<char>::allocator<char>(this);
  FUN_006d4b00(uVar2);
  return param_2;
}

