
int FUN_00830353(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_1 + 0x24);
  cVar1 = *(char *)(iVar2 + 4);
  *(byte *)(iVar2 + 5) = *(byte *)(iVar2 + 5) | 4;
  if (cVar1 == '\x05') {
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(iVar2 + 0x18);
    iVar3 = FUN_0083085a(param_1,iVar2);
    if (iVar3 != 0) {
      *(byte *)(iVar2 + 5) = *(byte *)(iVar2 + 5) & 0xfb;
    }
    iVar2 = (*(int *)(iVar2 + 0x1c) + (1 << (*(byte *)(iVar2 + 7) & 0x1f)) * 2 + 2) * 0x10;
  }
  else if (cVar1 == '\x06') {
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(iVar2 + 8);
    FUN_00830650(param_1,iVar2);
    if (*(char *)(iVar2 + 6) == '\0') {
      iVar2 = (uint)*(byte *)(iVar2 + 7) * 4 + 0x14;
    }
    else {
      iVar2 = (uint)*(byte *)(iVar2 + 7) * 0x10 + 0x18;
    }
  }
  else if (cVar1 == '\b') {
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(iVar2 + 0x6c);
    *(undefined4 *)(iVar2 + 0x6c) = *(undefined4 *)(param_1 + 0x28);
    *(int *)(param_1 + 0x28) = iVar2;
    *(byte *)(iVar2 + 5) = *(byte *)(iVar2 + 5) & 0xfb;
    FUN_00830791(param_1,iVar2);
    iVar2 = (*(int *)(iVar2 + 0x30) + 5) * 0x18 + *(int *)(iVar2 + 0x2c) * 0x10;
  }
  else if (cVar1 == '\t') {
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(iVar2 + 0x44);
    FUN_008306e5(param_1,iVar2);
    iVar2 = (*(int *)(iVar2 + 0x38) * 3 + *(int *)(iVar2 + 0x28) * 4 + *(int *)(iVar2 + 0x34) +
             *(int *)(iVar2 + 0x30) + *(int *)(iVar2 + 0x2c) + *(int *)(iVar2 + 0x24)) * 4 + 0x4c;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

