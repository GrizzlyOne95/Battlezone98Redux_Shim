
undefined4 FUN_004183b0(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int local_20;
  uint local_18;
  int local_c;
  
  iVar1 = FUN_00417c70();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = FUN_00417ca0();
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar3 = FUN_00417f90();
      uVar4 = FUN_00417fb0();
      iVar1 = FUN_00417c80();
      local_18 = 0;
      for (local_c = 0; local_c < 5; local_c = local_c + 1) {
        iVar5 = FUN_00417f60(local_c);
        if (iVar5 == 0) {
          local_20 = 0;
        }
        else {
          local_20 = *(int *)(iVar5 + 0xb0);
        }
        if (iVar1 < local_20) {
          local_18 = 1 << ((byte)local_c & 0x1f) | local_18;
        }
      }
      uVar3 = uVar4 & uVar3 & ~local_18;
      uVar2 = CONCAT31((int3)(uVar3 >> 8),uVar3 != 0);
    }
  }
  return uVar2;
}

