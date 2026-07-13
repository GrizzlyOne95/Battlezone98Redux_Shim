
uint FUN_006a02b0(ushort param_1,char param_2)

{
  uint uVar1;
  ushort *puVar2;
  ushort *local_8;
  
  if (*(int *)(DAT_02ceb7e8 + (uint)param_1 * 0x4e + param_2 * 2 + 0xe) < 1) {
    if (*(int *)(DAT_02ceb7e8 + (uint)param_1 * 0x4e + 0xc) == 0) {
      uVar1 = 0;
    }
    else {
      puVar2 = DAT_02ceb7e8;
      for (local_8 = *(ushort **)(DAT_02ceb7e8 + (uint)param_1 * 0x4e + 0xc);
          local_8 != (ushort *)0x0; local_8 = *(ushort **)(local_8 + 2)) {
        if (0 < *(int *)(DAT_02ceb7e8 + (uint)*local_8 * 0x4e + param_2 * 2 + 0xe)) {
          return CONCAT31((uint3)(byte)(*local_8 >> 8),1);
        }
        puVar2 = local_8;
      }
      uVar1 = (uint)puVar2 & 0xffffff00;
    }
  }
  else {
    uVar1 = CONCAT31((uint3)(byte)(param_1 >> 8),1);
  }
  return uVar1;
}

