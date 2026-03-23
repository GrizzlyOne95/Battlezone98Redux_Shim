
void FUN_004973f0(int param_1,int param_2,int param_3,undefined4 param_4,undefined1 param_5)

{
  int iVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int local_8;
  
  iVar1 = param_2;
  while (local_8 = param_2 * 2 + 2, local_8 < param_3) {
    cVar2 = FUN_00497100(param_1 + local_8 * 8,param_1 + -8 + local_8 * 8);
    if (cVar2 != '\0') {
      local_8 = param_2 * 2 + 1;
    }
    puVar3 = (undefined4 *)FUN_00417780(param_1 + local_8 * 8);
    uVar4 = puVar3[1];
    *(undefined4 *)(param_1 + param_2 * 8) = *puVar3;
    *(undefined4 *)(param_1 + 4 + param_2 * 8) = uVar4;
    param_2 = local_8;
  }
  if (local_8 == param_3) {
    puVar3 = (undefined4 *)FUN_00417780(param_1 + -8 + param_3 * 8);
    uVar4 = puVar3[1];
    *(undefined4 *)(param_1 + param_2 * 8) = *puVar3;
    *(undefined4 *)(param_1 + 4 + param_2 * 8) = uVar4;
    param_2 = param_3 + -1;
  }
  uVar4 = FUN_00417780(param_4,param_5);
  FUN_00497560(param_1,param_2,iVar1,uVar4);
  return;
}

