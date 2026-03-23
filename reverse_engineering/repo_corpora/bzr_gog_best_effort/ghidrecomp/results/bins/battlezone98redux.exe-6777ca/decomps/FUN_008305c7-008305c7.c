
undefined4 * FUN_008305c7(int param_1,undefined4 *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar2 = *(int *)(param_1 + 0x10);
  bVar1 = *(byte *)(iVar2 + 0x14);
  while ((puVar3 = (undefined4 *)*param_2, puVar3 != (undefined4 *)0x0 && (param_3 != 0))) {
    if (*(char *)(puVar3 + 1) == '\b') {
      FUN_008305c7(param_1,puVar3 + 0x1a,0xfffffffd);
    }
    if ((byte)((bVar1 ^ 3) & (*(byte *)((int)puVar3 + 5) ^ 3)) == 0) {
      *param_2 = *puVar3;
      if (puVar3 == *(undefined4 **)(iVar2 + 0x1c)) {
        *(undefined4 *)(iVar2 + 0x1c) = *puVar3;
      }
      FUN_0082ff43(param_1,puVar3);
      param_3 = param_3 + -1;
    }
    else {
      *(byte *)((int)puVar3 + 5) = *(byte *)(iVar2 + 0x14) & 3 | *(byte *)((int)puVar3 + 5) & 0xf8;
      param_2 = puVar3;
      param_3 = param_3 + -1;
    }
  }
  return param_2;
}

