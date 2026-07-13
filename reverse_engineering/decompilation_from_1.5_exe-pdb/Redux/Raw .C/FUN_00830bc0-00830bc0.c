
undefined4 * FUN_00830bc0(int param_1,void *param_2,size_t param_3,uint param_4)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  if (0xffffffed < param_3 + 1) {
    FUN_008388ab(param_1);
  }
  puVar4 = (undefined4 *)FUN_00838869(param_1,0,0,param_3 + 0x11);
  puVar4[3] = param_3;
  puVar4[2] = param_4;
  bVar1 = *(byte *)(*(int *)(param_1 + 0x10) + 0x14);
  *(undefined1 *)(puVar4 + 1) = 4;
  *(byte *)((int)puVar4 + 5) = bVar1 & 3;
  *(undefined1 *)((int)puVar4 + 6) = 0;
  memcpy(puVar4 + 4,param_2,param_3);
  *(undefined1 *)((int)puVar4 + param_3 + 0x10) = 0;
  piVar2 = *(int **)(param_1 + 0x10);
  param_4 = param_4 & piVar2[2] - 1U;
  *puVar4 = *(undefined4 *)(*piVar2 + param_4 * 4);
  *(undefined4 **)(*piVar2 + param_4 * 4) = puVar4;
  piVar2[1] = piVar2[1] + 1;
  uVar3 = piVar2[2];
  if ((uVar3 < (uint)piVar2[1]) && ((int)uVar3 < 0x3fffffff)) {
    FUN_00830af4(param_1,uVar3 * 2);
  }
  return puVar4;
}

