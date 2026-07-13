
void FUN_00497560(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  int local_8;
  
  while (local_8 = (param_2 + -1) / 2, param_3 < param_2) {
    cVar2 = FUN_00497100(param_1 + local_8 * 8,param_4);
    if (cVar2 == '\0') break;
    puVar3 = (undefined4 *)FUN_00417780(param_1 + local_8 * 8);
    uVar1 = puVar3[1];
    *(undefined4 *)(param_1 + param_2 * 8) = *puVar3;
    *(undefined4 *)(param_1 + 4 + param_2 * 8) = uVar1;
    param_2 = local_8;
  }
  puVar3 = (undefined4 *)FUN_00417780(param_4);
  uVar1 = puVar3[1];
  *(undefined4 *)(param_1 + param_2 * 8) = *puVar3;
  *(undefined4 *)(param_1 + 4 + param_2 * 8) = uVar1;
  return;
}

