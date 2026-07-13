
undefined4 __thiscall
FUN_007f2dd0(undefined3 param_1,allocator<char> *param_2,char param_3,char param_4,char param_5)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  if ((param_4 != '\0') || ((param_3 != '\0' && (param_5 != '\0')))) {
    uVar2 = CONCAT13(0x2d,param_1);
    puVar1 = &stack0xfffffffb;
    std::allocator<char>::allocator<char>(param_2);
    FUN_007f0750(puVar1);
    FUN_007efea0(uVar2);
  }
  return 1;
}

