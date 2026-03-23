
void __fastcall FUN_0078e5f0(int param_1)

{
  FUN_0078c4a0();
  *(undefined4 *)(param_1 + 0x148) = 0;
  FUN_007d21c0(*(undefined4 *)(param_1 + 0x150));
  if (*(undefined4 **)(param_1 + 0x150) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x150))(1);
  }
  *(undefined4 *)(param_1 + 0x150) = 0;
  DAT_008e8c7e = 0;
  return;
}

