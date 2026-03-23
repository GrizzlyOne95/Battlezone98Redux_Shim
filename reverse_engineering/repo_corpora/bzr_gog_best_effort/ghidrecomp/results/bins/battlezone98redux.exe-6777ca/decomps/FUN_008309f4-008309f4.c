
undefined4 * FUN_008309f4(int param_1,void *param_2,uint param_3)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar3 = (param_3 >> 5) + 1;
  uVar4 = param_3;
  for (uVar5 = param_3; uVar3 <= uVar5; uVar5 = uVar5 - uVar3) {
    uVar4 = uVar4 ^ (uint)*(byte *)((int)param_2 + (uVar5 - 1)) + uVar4 * 0x20 + (uVar4 >> 2);
  }
  puVar2 = *(undefined4 **)
            (**(int **)(param_1 + 0x10) + ((*(int **)(param_1 + 0x10))[2] - 1U & uVar4) * 4);
  while( true ) {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = (undefined4 *)FUN_00830bc0(param_1,param_2,param_3,uVar4);
      return puVar2;
    }
    if ((puVar2[3] == param_3) && (iVar1 = memcmp(param_2,puVar2 + 4,param_3), iVar1 == 0)) break;
    puVar2 = (undefined4 *)*puVar2;
  }
  if ((~*(byte *)(*(int *)(param_1 + 0x10) + 0x14) & *(byte *)((int)puVar2 + 5) & 3) == 0) {
    return puVar2;
  }
  *(byte *)((int)puVar2 + 5) = *(byte *)((int)puVar2 + 5) ^ 3;
  return puVar2;
}

