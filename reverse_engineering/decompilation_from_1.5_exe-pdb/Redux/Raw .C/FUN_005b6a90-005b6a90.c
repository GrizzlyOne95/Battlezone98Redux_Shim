
void __fastcall FUN_005b6a90(int param_1)

{
  if (*(int *)(param_1 + 0x30) != 0) {
    if (*(undefined4 **)(param_1 + 0x30) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x30))(1);
    }
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  return;
}

