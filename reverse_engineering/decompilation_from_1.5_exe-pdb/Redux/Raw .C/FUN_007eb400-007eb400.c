
int __thiscall FUN_007eb400(int param_1,undefined4 *param_2)

{
  undefined4 extraout_ECX;
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = param_1;
  FUN_006e1cb0(&stack0x0000000c);
  uVar1 = extraout_ECX;
  FUN_006e1cb0(&stack0x00000008);
  FUN_007eb590(uVar1,iVar2);
  *(undefined4 *)(param_1 + 8) = *param_2;
  *(undefined4 *)(param_1 + 0xc) = param_2[1];
  *(undefined4 *)(param_1 + 0x10) = param_2[2];
  return param_1;
}

