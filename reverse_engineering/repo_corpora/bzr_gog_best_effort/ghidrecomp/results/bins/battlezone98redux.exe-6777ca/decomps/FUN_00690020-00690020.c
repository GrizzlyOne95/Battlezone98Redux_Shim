
void FUN_00690020(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int local_10;
  int local_c;
  
  iVar1 = *(int *)(DAT_00920f04 + param_1 * 4);
  if (iVar1 != 0) {
    if (param_3 == 0) {
      if (param_2 != 0) {
        iVar2 = *(int *)(param_2 + 0x1c);
        if ((iVar2 < 2) || ((3 < iVar2 && (iVar2 != 7)))) {
          local_c = 0;
          local_10 = 0;
        }
        else {
          local_c = *(int *)(param_2 + 0x24);
          local_10 = *(int *)(param_2 + 0x20);
        }
      }
    }
    else {
      local_c = *(int *)(param_3 + 0x34);
      local_10 = *(int *)(param_3 + 0x40);
    }
    *(int *)(iVar1 + 0xb8) = *(int *)(iVar1 + 0xb8) - local_c;
    if (local_c != 0) {
      if (local_10 == 0) {
        FUN_00692ba0(param_1,local_c);
      }
      else {
        *(int *)(iVar1 + 0xbc) = *(int *)(iVar1 + 0xbc) + local_c;
        *(int *)(iVar1 + 0xbc + local_10 * 4) = *(int *)(iVar1 + 0xbc + local_10 * 4) + local_c;
      }
    }
  }
  return;
}

