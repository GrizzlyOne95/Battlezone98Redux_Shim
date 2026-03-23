
undefined4 __thiscall FUN_004306d0(int param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar1 = FUN_004307f0(param_2);
  if (uVar1 == 0xffffffff) {
    uVar4 = 0xffffff00;
  }
  else {
    while( true ) {
      uVar2 = FUN_004170c0();
      if (uVar1 <= uVar2) break;
      iVar3 = FUN_004170c0();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (param_1 + 4),iVar3 << 1);
    }
    uVar4 = FUN_004170c0();
    uVar5 = FUN_00430770(uVar4);
    uVar4 = FUN_00430830(param_2,uVar5,uVar4);
  }
  return uVar4;
}

