
void FUN_0083012f(int param_1,undefined4 *param_2)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x10);
  *param_2 = *(undefined4 *)(iVar2 + 0x1c);
  *(undefined4 **)(iVar2 + 0x1c) = param_2;
  bVar1 = *(byte *)((int)param_2 + 5);
  if ((bVar1 & 7) == 0) {
    if (*(char *)(iVar2 + 0x15) == '\x01') {
      *(byte *)((int)param_2 + 5) = bVar1 | 4;
      if ((3 < ((int *)param_2[2])[2]) &&
         (iVar2 = *(int *)param_2[2], (*(byte *)(iVar2 + 5) & 3) != 0)) {
        FUN_0083001b(param_1,param_2,iVar2);
      }
    }
    else {
      *(byte *)((int)param_2 + 5) = *(byte *)(iVar2 + 0x14) & 3 | bVar1 & 0xf8;
    }
  }
  return;
}

