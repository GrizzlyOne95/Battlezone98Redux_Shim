
void FUN_004d92f0(int param_1,int param_2,int param_3,undefined4 *param_4)

{
  char cVar1;
  undefined4 *puVar2;
  int local_8;
  
  while (local_8 = (param_2 + -1) / 2, param_3 < param_2) {
    cVar1 = FUN_004d4090(*(undefined4 *)(param_1 + local_8 * 4),*param_4);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_00417780(param_1 + local_8 * 4);
    *(undefined4 *)(param_1 + param_2 * 4) = *puVar2;
    param_2 = local_8;
  }
  puVar2 = (undefined4 *)FUN_00417780(param_4);
  *(undefined4 *)(param_1 + param_2 * 4) = *puVar2;
  return;
}

