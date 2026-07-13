
undefined * FUN_008334a2(int param_1,int *param_2,int param_3)

{
  undefined *puVar1;
  int iVar2;
  
  iVar2 = param_2[2];
  if ((iVar2 == 5) || (iVar2 == 7)) {
    iVar2 = *(int *)(*param_2 + 8);
  }
  else {
    iVar2 = *(int *)(*(int *)(param_1 + 0x10) + 0x98 + iVar2 * 4);
  }
  if (iVar2 == 0) {
    puVar1 = &DAT_0086ed18;
  }
  else {
    puVar1 = (undefined *)
             FUN_00830f2e(iVar2,*(undefined4 *)(*(int *)(param_1 + 0x10) + 0xbc + param_3 * 4));
  }
  return puVar1;
}

