
undefined4 __thiscall FUN_006d82c0(undefined4 param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int in_stack_ffffffe4;
  
  if (*(char *)(param_2 + 8) == '\0') {
    puVar2 = (undefined4 *)FUN_004fbb60();
    uVar1 = puVar2[1];
    *param_3 = *puVar2;
    param_3[1] = uVar1;
    uVar3 = 0;
  }
  else {
    iVar4 = eof(in_stack_ffffffe4);
    uVar3 = FUN_006df250(param_1,param_2 + 0xc,iVar4);
    *(undefined1 *)(param_2 + 8) = 0;
    puVar2 = (undefined4 *)FUN_004fbb60();
    uVar1 = puVar2[1];
    *param_3 = *puVar2;
    param_3[1] = uVar1;
  }
  return uVar3;
}

