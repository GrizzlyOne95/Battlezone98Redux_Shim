
uint __thiscall FUN_005aecb0(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = param_1;
  if (*(int *)(param_1 + 0x300) == 0) {
    iVar2 = FUN_004e1b90(*(undefined4 *)(param_1 + 0x174),param_2);
    iVar3 = FUN_004e1c10(*(undefined4 *)(param_1 + 0x174),param_2);
    uVar4 = FUN_005e10b0();
    if ((iVar2 <= (int)uVar4) && (uVar4 = FUN_005e1220(), iVar3 <= (int)uVar4)) {
      FUN_005e1010(-iVar2);
      FUN_005e11b0(-iVar3);
      *(undefined4 *)(param_1 + 0x300) = param_2;
      uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x300) + 0x54);
      *(undefined4 *)(param_1 + 0x304) = uVar1;
      return CONCAT31((int3)((uint)uVar1 >> 8),1);
    }
  }
  return uVar4 & 0xffffff00;
}

