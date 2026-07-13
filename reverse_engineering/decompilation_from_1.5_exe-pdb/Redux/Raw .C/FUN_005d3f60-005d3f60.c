
void __fastcall FUN_005d3f60(int param_1)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x23c) == 0) {
    *(undefined4 *)(param_1 + 0x238) = 0xffffffff;
  }
  else {
    uVar1 = FUN_005c5ff0(*(undefined4 *)(param_1 + 0x23c));
    *(undefined4 *)(param_1 + 0x238) = uVar1;
  }
  if (-1 < *(int *)(param_1 + 0x238)) {
    FUN_005c6230(*(undefined4 *)(param_1 + 0x238));
    *(undefined4 *)(param_1 + 0x238) = 0xffffffff;
  }
  FUN_004dce20();
  return;
}

