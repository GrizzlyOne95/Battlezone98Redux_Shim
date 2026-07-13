
void __fastcall FUN_005f08c0(int param_1)

{
  if (*(int *)(param_1 + 0x2c8) != 0) {
    FUN_00469900(*(undefined4 *)(param_1 + 0x2cc),*(undefined4 *)(param_1 + 0x2d0),0x43480000,
                 *(undefined4 *)(param_1 + 0x2c8),0);
    *(undefined4 *)(param_1 + 0x2c8) = 0;
  }
  return;
}

