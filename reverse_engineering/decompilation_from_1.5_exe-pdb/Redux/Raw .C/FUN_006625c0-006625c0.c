
undefined4
FUN_006625c0(undefined4 param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  undefined4 uVar5;
  
  uVar1 = FUN_004170c0();
  iVar2 = FUN_0056f820();
  iVar3 = FUN_004170c0();
  if ((uint)(iVar2 - iVar3) < uVar1) {
    iVar2 = FUN_0056f820();
    iVar3 = FUN_004170c0();
    uVar1 = FUN_004170c0();
    if (uVar1 <= (uint)(iVar2 - iVar3)) {
      uVar5 = FUN_00662670(0,param_2);
      uVar5 = FUN_00417780(uVar5);
      basic_string<>(uVar5);
      return param_1;
    }
  }
  pbVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                     (param_2,param_3);
  uVar5 = FUN_00417780(pbVar4);
  basic_string<>(uVar5);
  return param_1;
}

