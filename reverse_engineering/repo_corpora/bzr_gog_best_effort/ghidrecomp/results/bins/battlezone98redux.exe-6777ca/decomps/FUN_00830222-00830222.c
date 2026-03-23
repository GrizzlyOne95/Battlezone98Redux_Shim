
void FUN_00830222(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x10);
  iVar3 = *(int *)(iVar1 + 0x54) * 10;
  if (iVar3 == 0) {
    iVar3 = 0x7ffffffe;
  }
  *(int *)(iVar1 + 0x4c) =
       *(int *)(iVar1 + 0x4c) + (*(int *)(iVar1 + 0x44) - *(int *)(iVar1 + 0x40));
  do {
    iVar2 = FUN_008304dc(param_1);
    iVar3 = iVar3 - iVar2;
    if (*(char *)(iVar1 + 0x15) == '\0') goto LAB_0083027e;
  } while (0 < iVar3);
  if (*(char *)(iVar1 + 0x15) == '\0') {
LAB_0083027e:
    iVar3 = (*(uint *)(iVar1 + 0x48) / 100) * *(int *)(iVar1 + 0x50);
  }
  else if (*(uint *)(iVar1 + 0x4c) < 0x400) {
    iVar3 = *(int *)(iVar1 + 0x44) + 0x400;
  }
  else {
    *(uint *)(iVar1 + 0x4c) = *(uint *)(iVar1 + 0x4c) - 0x400;
    iVar3 = *(int *)(iVar1 + 0x44);
  }
  *(int *)(iVar1 + 0x40) = iVar3;
  return;
}

