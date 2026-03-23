
void FUN_0082f8a7(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)FUN_008334a2(param_1,param_2,0x10);
  iVar1 = *(int *)(param_1 + 0x20);
  if (puVar2[2] != 6) {
    FUN_0082dfec(param_1,param_2,&DAT_0086ee78);
  }
  for (puVar3 = *(undefined4 **)(param_1 + 8); param_2 < puVar3; puVar3 = puVar3 + -4) {
    *puVar3 = puVar3[-4];
    puVar3[1] = puVar3[-3];
    puVar3[2] = puVar3[-2];
  }
  if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x11) {
    FUN_0082f194(param_1,1);
  }
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 0x10;
  param_2 = (undefined4 *)((int)param_2 + (*(int *)(param_1 + 0x20) - iVar1));
  *param_2 = *puVar2;
  param_2[1] = puVar2[1];
  param_2[2] = puVar2[2];
  return;
}

