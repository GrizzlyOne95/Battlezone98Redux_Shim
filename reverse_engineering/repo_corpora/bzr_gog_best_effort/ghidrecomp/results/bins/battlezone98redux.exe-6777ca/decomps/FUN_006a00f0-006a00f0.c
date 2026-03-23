
void FUN_006a00f0(ushort param_1,char param_2)

{
  bool bVar1;
  int iVar2;
  ushort *local_8;
  
  bVar1 = false;
  if (DAT_00920c9a != '\0') {
    if (*(char *)(DAT_02ceb7e8 + (uint)param_1 * 0x9c) == '\x01') {
      iVar2 = FUN_006a0670(param_1);
      for (local_8 = *(ushort **)(iVar2 + 4); local_8 != (ushort *)0x0;
          local_8 = *(ushort **)(local_8 + 2)) {
        iVar2 = *(int *)((uint)*local_8 * 0x9c + DAT_02ceb7e8 + 0x1c + param_2 * 4) + -1;
        *(int *)((uint)*local_8 * 0x9c + DAT_02ceb7e8 + 0x1c + param_2 * 4) = iVar2;
        if (iVar2 == 0) {
          bVar1 = true;
        }
      }
    }
    iVar2 = *(int *)((uint)param_1 * 0x9c + DAT_02ceb7e8 + 0x1c + param_2 * 4) + -1;
    *(int *)((uint)param_1 * 0x9c + DAT_02ceb7e8 + 0x1c + param_2 * 4) = iVar2;
    if (iVar2 == 0) {
      bVar1 = true;
    }
    if (bVar1) {
      FUN_0069feb0(param_2);
    }
  }
  return;
}

