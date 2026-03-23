
void __fastcall FUN_007ba530(int param_1)

{
  if (*(int *)(param_1 + 0x14c) != 0) {
    FUN_007ba270();
  }
  FUN_007d21c0(*(undefined4 *)(param_1 + 0x178));
  FUN_007d21c0(*(undefined4 *)(param_1 + 0x17c));
  FUN_007d21c0(*(undefined4 *)(param_1 + 0x180));
  FUN_007d21c0(*(undefined4 *)(param_1 + 0x184));
  if (*(undefined4 **)(param_1 + 0x178) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x178))(1);
  }
  if (*(undefined4 **)(param_1 + 0x17c) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x17c))(1);
  }
  if (*(undefined4 **)(param_1 + 0x180) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x180))(1);
  }
  if (*(undefined4 **)(param_1 + 0x184) != (undefined4 *)0x0) {
    (**(code **)**(undefined4 **)(param_1 + 0x184))(1);
  }
  *(undefined4 *)(param_1 + 0x178) = 0;
  *(undefined4 *)(param_1 + 0x17c) = 0;
  *(undefined4 *)(param_1 + 0x180) = 0;
  *(undefined4 *)(param_1 + 0x184) = 0;
  if (*(int *)(param_1 + 0x2f4) != -1) {
    FUN_007d2870("mpcron.png");
  }
  *(undefined4 *)(param_1 + 0x2f4) = 0xffffffff;
  return;
}

