
void __fastcall FUN_007b6900(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00434160();
  if ((iVar1 != 5) && (*(int *)(DAT_0094672c + 0x4c) != *(int *)(param_1 + 0x164))) {
    *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(DAT_0094672c + 0x4c);
    FUN_00764790();
    FUN_007681d0();
    FUN_00434420();
    FUN_00434440();
    FUN_004b68c0();
  }
  FUN_00820b90();
  FUN_007c79a0();
  return;
}

