
bool FUN_0080fc10(undefined4 param_1,undefined4 param_2,undefined1 *param_3)

{
  char cVar1;
  undefined4 extraout_var;
  
  std::allocator<char>::allocator<char>((allocator<char> *)&stack0xfffffffb);
  cVar1 = FUN_008109d0(param_1,param_2,&stack0xfffffffb,extraout_var);
  if (cVar1 != '\0') {
    std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
              (&stack0xfffffffb,*param_3);
  }
  return cVar1 != '\0';
}

