
void __fastcall FUN_005fbff0(int param_1)

{
  if (*(int *)(param_1 + 0x38) != 0) {
    if (*(undefined4 **)(param_1 + 0x38) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x38))(1);
    }
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  return;
}

