
void __fastcall FUN_0041a350(int param_1)

{
  int iVar1;
  uint uVar2;
  undefined8 uVar3;
  
  if (*(char *)(param_1 + 4) != '\0') {
    if (*(char *)(param_1 + 0x7c) == '\0') {
      uVar3 = FUN_00822ea0();
      uVar2 = (uint)((ulonglong)uVar3 >> 0x20);
      if ((*(uint *)(param_1 + 0x84) <= uVar2) &&
         ((uVar2 != *(uint *)(param_1 + 0x84) || (*(uint *)(param_1 + 0x80) < (uint)uVar3)))) {
        *(undefined1 *)(param_1 + 0x7c) = 1;
      }
    }
    iVar1 = DAT_02cecee0 / 0x19;
    uVar2 = FUN_00822d90();
    *(int *)(param_1 + 0x58) = (int)(-iVar1 * (uVar2 % 500)) / 500;
  }
  return;
}

