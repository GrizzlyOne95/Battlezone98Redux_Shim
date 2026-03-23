
void __fastcall FUN_005ef5f0(int param_1)

{
  if (*(int *)(param_1 + 0x34) != 0) {
    if (*(undefined4 **)(param_1 + 0x34) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x34))(1);
    }
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  return;
}

