
void FUN_00593b40(int param_1,int param_2,int param_3,undefined4 param_4,code *param_5)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int local_8;
  
  iVar4 = param_2;
  while (local_8 = param_2 * 2 + 2, local_8 < param_3) {
    cVar1 = (*param_5)(*(undefined4 *)(param_1 + local_8 * 4),
                       *(undefined4 *)(param_1 + -4 + local_8 * 4));
    if (cVar1 != '\0') {
      local_8 = param_2 * 2 + 1;
    }
    puVar2 = (undefined4 *)FUN_00417780(param_1 + local_8 * 4);
    *(undefined4 *)(param_1 + param_2 * 4) = *puVar2;
    param_2 = local_8;
  }
  if (local_8 == param_3) {
    puVar2 = (undefined4 *)FUN_00417780(param_1 + -4 + param_3 * 4,iVar4);
    *(undefined4 *)(param_1 + param_2 * 4) = *puVar2;
    param_2 = param_3 + -1;
  }
  uVar3 = FUN_00417780(param_4,param_5);
  FUN_00593cb0(param_1,param_2,iVar4,uVar3);
  return;
}

