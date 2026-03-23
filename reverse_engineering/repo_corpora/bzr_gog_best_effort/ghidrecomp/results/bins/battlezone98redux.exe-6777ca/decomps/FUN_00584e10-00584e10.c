
void __thiscall
FUN_00584e10(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  int iVar1;
  
  FUN_00583d90(param_2,param_1);
  iVar1 = FUN_00583e30();
  *param_3 = *(undefined4 *)(iVar1 + 0x18);
  param_3[1] = *(undefined4 *)(iVar1 + 0x1c);
  param_3[2] = *(undefined4 *)(iVar1 + 0x20);
  *param_4 = *(undefined4 *)(iVar1 + 8);
  return;
}

