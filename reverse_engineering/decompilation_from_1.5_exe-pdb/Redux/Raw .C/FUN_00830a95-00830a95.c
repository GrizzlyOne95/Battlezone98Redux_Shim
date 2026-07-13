
undefined4 * FUN_00830a95(int param_1,uint param_2,undefined4 param_3)

{
  byte bVar1;
  undefined4 *puVar2;
  
  if (0xffffffe5 < param_2) {
    FUN_008388ab(param_1);
  }
  puVar2 = (undefined4 *)FUN_00838869(param_1,0,0,param_2 + 0x18);
  bVar1 = *(byte *)(*(int *)(param_1 + 0x10) + 0x14);
  puVar2[4] = param_2;
  puVar2[2] = 0;
  *(byte *)((int)puVar2 + 5) = bVar1 & 3;
  *(undefined1 *)(puVar2 + 1) = 7;
  puVar2[3] = param_3;
  *puVar2 = **(undefined4 **)(*(int *)(param_1 + 0x10) + 0x70);
  **(undefined4 **)(*(int *)(param_1 + 0x10) + 0x70) = puVar2;
  return puVar2;
}

