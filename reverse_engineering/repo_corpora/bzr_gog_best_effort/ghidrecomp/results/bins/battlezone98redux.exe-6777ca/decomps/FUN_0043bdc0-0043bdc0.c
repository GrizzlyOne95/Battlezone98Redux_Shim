
void FUN_0043bdc0(int param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  undefined4 *local_24;
  uint local_20;
  byte *local_18;
  byte *local_14;
  int local_c;
  
  for (local_c = FUN_0043bc50(); local_c != 0; local_c = FUN_00439cc0(local_c)) {
    if (local_c != param_1) {
      local_18 = (byte *)(param_1 + 4);
      local_14 = (byte *)(local_c + 4);
      do {
        bVar1 = *local_14;
        bVar5 = bVar1 < *local_18;
        if (bVar1 != *local_18) {
LAB_0043be3e:
          local_20 = -(uint)bVar5 | 1;
          goto LAB_0043be46;
        }
        if (bVar1 == 0) break;
        bVar1 = local_14[1];
        bVar5 = bVar1 < local_18[1];
        if (bVar1 != local_18[1]) goto LAB_0043be3e;
        local_14 = local_14 + 2;
        local_18 = local_18 + 2;
      } while (bVar1 != 0);
      local_20 = 0;
LAB_0043be46:
      if (local_20 == 0) break;
    }
  }
  *(int *)(param_1 + 100) = DAT_0260c2e4;
  iVar4 = DAT_0260c2e4;
  if (DAT_0260c2e4 == -1) {
    FUN_007d6a70("LinkCopy out of copies\n");
  }
  else {
    iVar3 = DAT_0260c2e4 * 4;
    DAT_0260c254 = DAT_0260c254 + -1;
    if (DAT_0260c254 < DAT_0260c928) {
      DAT_0260c928 = DAT_0260c254;
    }
    iVar2 = DAT_0260c2e4 * 4;
    DAT_0260c2e4 = (&DAT_0260c2ec)[DAT_0260c2e4 * 4];
    (&DAT_0260c2f0)[iVar2] = 0;
    (&DAT_0260c2f4)[iVar4 * 4] = param_1;
    if (param_1 == 0) {
      FUN_007d6a70("LinkCopy with NULL go\n");
    }
    if (local_c == 0) {
      (&DAT_0260c2e8)[iVar3] = 0xffffffff;
      (&DAT_0260c2ec)[iVar4 * 4] = 0xffffffff;
    }
    else {
      iVar2 = *(int *)(local_c + 100);
      if ((&DAT_0260c2ec)[iVar2 * 4] == -1) {
        local_24 = (undefined4 *)0x0;
      }
      else {
        local_24 = &DAT_0260c2e8 + (&DAT_0260c2ec)[iVar2 * 4] * 4;
      }
      (&DAT_0260c2ec)[iVar4 * 4] = (&DAT_0260c2ec)[iVar2 * 4];
      (&DAT_0260c2e8)[iVar3] = *(undefined4 *)(local_c + 100);
      (&DAT_0260c2ec)[iVar2 * 4] = *(undefined4 *)(param_1 + 100);
      if (local_24 != (undefined4 *)0x0) {
        *local_24 = *(undefined4 *)(param_1 + 100);
      }
    }
  }
  return;
}

