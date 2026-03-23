
void __fastcall FUN_004db780(int param_1)

{
  undefined4 uVar1;
  
  if ((*(int *)(param_1 + 0x17c) != 0) && (*(int *)(param_1 + 0x178) != -1)) {
    FUN_005e0f50(*(undefined4 *)(param_1 + 0x178),0);
  }
  *(undefined4 *)(param_1 + 0x17c) = 0;
  *(undefined4 *)(param_1 + 0x174) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x178) = 0xffffffff;
  uVar1 = FUN_00462380();
  FUN_004a0710(uVar1);
  return;
}

