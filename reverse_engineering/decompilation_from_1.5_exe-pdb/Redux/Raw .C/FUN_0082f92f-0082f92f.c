
void FUN_0082f92f(int param_1,uint param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  
  iVar2 = *(int *)(param_1 + 0x68);
  iVar3 = *(int *)(param_1 + 0x10);
  while ((iVar2 != 0 && (puVar4 = *(undefined4 **)(param_1 + 0x68), param_2 <= (uint)puVar4[2]))) {
    *(undefined4 *)(param_1 + 0x68) = *puVar4;
    if ((~*(byte *)(iVar3 + 0x14) & *(byte *)((int)puVar4 + 5) & 3) == 0) {
      piVar1 = puVar4 + 4;
      *(int *)(puVar4[5] + 0x10) = *piVar1;
      *(undefined4 *)(*piVar1 + 0x14) = puVar4[5];
      piVar5 = (int *)puVar4[2];
      *piVar1 = *piVar5;
      puVar4[5] = piVar5[1];
      puVar4[6] = piVar5[2];
      puVar4[2] = piVar1;
      FUN_0083012f(param_1,puVar4);
    }
    else {
      FUN_0082fae9();
    }
    iVar2 = *(int *)(param_1 + 0x68);
  }
  return;
}

