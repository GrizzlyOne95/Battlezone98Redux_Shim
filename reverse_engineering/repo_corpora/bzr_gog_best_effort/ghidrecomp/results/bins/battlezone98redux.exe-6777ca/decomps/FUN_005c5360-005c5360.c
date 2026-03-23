
void __fastcall FUN_005c5360(int param_1)

{
  if (*(int *)(param_1 + 0x58) != 0) {
    if (*(undefined4 **)(param_1 + 0x58) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x58))(1);
    }
    *(undefined4 *)(param_1 + 0x58) = 0;
  }
  return;
}

