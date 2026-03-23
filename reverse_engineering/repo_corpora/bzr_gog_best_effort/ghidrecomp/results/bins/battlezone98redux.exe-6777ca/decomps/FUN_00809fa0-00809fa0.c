
undefined4 __thiscall
FUN_00809fa0(allocator<char> *param_1,
            _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
            *param_2,undefined4 param_3,undefined4 param_4,undefined1 *param_5,undefined1 *param_6)

{
  char cVar1;
  byte *pbVar2;
  undefined4 uVar3;
  uint uVar4;
  
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
            (param_2,param_3,*param_5);
  cVar1 = FID_conflict_operator__(param_3);
  if (cVar1 != '\0') {
    pbVar2 = (byte *)get(param_4);
    uVar4 = (uint)*pbVar2;
    std::allocator<char>::allocator<char>(param_1);
    cVar1 = FUN_0080a740(uVar4,param_4);
    if (cVar1 != '\0') {
      uVar3 = get(*param_6);
      std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(uVar3);
      std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
      operator++(param_2);
      return 1;
    }
  }
  return 0;
}

