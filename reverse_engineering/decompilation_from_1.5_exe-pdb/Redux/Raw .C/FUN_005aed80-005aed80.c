
bool __fastcall FUN_005aed80(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  
  bVar3 = *(int *)(param_1 + 0x300) != 0;
  if (bVar3) {
    FUN_004723b0(0xffffffff);
    uVar1 = FUN_004e1b90(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(param_1 + 0x300));
    uVar2 = FUN_004e1c10(*(undefined4 *)(param_1 + 0x174),*(undefined4 *)(param_1 + 0x300));
    FUN_005e1010(uVar1);
    FUN_005e11b0(uVar2);
    *(undefined4 *)(param_1 + 0x300) = 0;
  }
  return bVar3;
}

