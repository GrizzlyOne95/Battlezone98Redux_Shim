
undefined4 __thiscall FUN_0081c0d0(int param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  uint local_1c;
  byte *local_10;
  byte *local_c;
  
  iVar2 = FUN_0081c250(param_2);
  if (iVar2 < 0) {
    uVar3 = 0;
  }
  else {
    local_10 = &DAT_00874be8;
    local_c = (byte *)(param_1 + 4 + iVar2 * 0x204);
    do {
      bVar1 = *local_c;
      bVar4 = bVar1 < *local_10;
      if (bVar1 != *local_10) {
LAB_0081c14a:
        local_1c = -(uint)bVar4 | 1;
        goto LAB_0081c152;
      }
      if (bVar1 == 0) break;
      bVar1 = local_c[1];
      bVar4 = bVar1 < local_10[1];
      if (bVar1 != local_10[1]) goto LAB_0081c14a;
      local_c = local_c + 2;
      local_10 = local_10 + 2;
    } while (bVar1 != 0);
    local_1c = 0;
LAB_0081c152:
    if (local_1c == 0) {
      uVar3 = 0;
    }
    else {
      FUN_0061f1c0(param_2,param_1 + 4 + iVar2 * 0x204);
      uVar3 = 1;
    }
  }
  return uVar3;
}

