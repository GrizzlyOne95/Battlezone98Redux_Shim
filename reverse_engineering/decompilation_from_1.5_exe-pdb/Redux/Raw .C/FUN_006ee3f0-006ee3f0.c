
undefined4 __thiscall FUN_006ee3f0(allocator<char> *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 extraout_ECX;
  undefined4 uVar2;
  
  uVar1 = std::allocator<char>::allocator<char>(param_1);
  uVar2 = extraout_ECX;
  FUN_006d1160(&stack0x00000008);
  FUN_006f3ac0(uVar2,uVar1);
  return param_2;
}

