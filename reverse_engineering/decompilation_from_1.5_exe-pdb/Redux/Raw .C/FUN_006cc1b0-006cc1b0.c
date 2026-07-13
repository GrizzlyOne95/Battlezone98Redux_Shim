
undefined4 __thiscall FUN_006cc1b0(allocator<char> *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 extraout_ECX;
  undefined1 **ppuVar2;
  undefined4 uVar3;
  undefined1 *puStack_14;
  undefined1 local_5;
  
  puStack_14 = &local_5;
  uVar1 = FUN_006d0a70();
  ppuVar2 = &puStack_14;
  uVar3 = extraout_ECX;
  FUN_006d1160(uVar1);
  std::allocator<char>::allocator<char>(param_1);
  FUN_006dcd90(ppuVar2,param_3,uVar3);
  FUN_006d0c50();
  return param_2;
}

