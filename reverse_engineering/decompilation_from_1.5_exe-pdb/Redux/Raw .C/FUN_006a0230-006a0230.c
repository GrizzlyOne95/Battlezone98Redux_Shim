
uint FUN_006a0230(ushort param_1,undefined4 param_2,ushort param_3)

{
  uint uVar1;
  ushort *puVar2;
  ushort *local_8;
  
  if (param_1 == param_3) {
    uVar1 = CONCAT31((uint3)(byte)(param_1 >> 8),1);
  }
  else if (*(int *)(DAT_02ceb7e8 + 0x18 + (uint)param_1 * 0x9c) == 0) {
    uVar1 = (uint)param_1 * 0x9c & 0xffffff00;
  }
  else {
    puVar2 = *(ushort **)(DAT_02ceb7e8 + 0x18 + (uint)param_1 * 0x9c);
    for (local_8 = puVar2; local_8 != (ushort *)0x0; local_8 = *(ushort **)(local_8 + 2)) {
      puVar2 = (ushort *)(uint)param_3;
      if ((ushort *)(uint)*local_8 == puVar2) {
        return CONCAT31((uint3)(byte)(param_3 >> 8),1);
      }
    }
    uVar1 = (uint)puVar2 & 0xffffff00;
  }
  return uVar1;
}

