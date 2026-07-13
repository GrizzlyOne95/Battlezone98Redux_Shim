
void __fastcall FUN_005c3e00(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  FUN_005c3ec0();
  if (*(int *)(param_1 + 0x20) != 9) {
    FUN_005c49b0();
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x20) = 9;
    FUN_005c4490();
  }
  uVar2 = FUN_00473890();
  cVar1 = FUN_005c4140(uVar2);
  if (cVar1 != '\0') {
    FUN_005c49b0();
    uVar2 = FUN_004dbb40();
    FUN_005c4370(uVar2);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x20) = 9;
    FUN_005c4490();
    if (*(int *)(param_1 + 0x20) != 9) {
      return;
    }
  }
  FUN_005c4aa0();
  return;
}

