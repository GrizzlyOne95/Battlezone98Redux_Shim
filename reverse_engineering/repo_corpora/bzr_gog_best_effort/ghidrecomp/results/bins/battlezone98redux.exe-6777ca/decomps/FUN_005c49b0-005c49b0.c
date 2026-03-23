
void __fastcall FUN_005c49b0(int param_1)

{
  switch(*(undefined4 *)(param_1 + 0x1c)) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 6:
  case 7:
    if (*(undefined4 **)(param_1 + 0x58) != (undefined4 *)0x0) {
      (**(code **)**(undefined4 **)(param_1 + 0x58))(1);
    }
    *(undefined4 *)(param_1 + 0x58) = 0;
    break;
  case 5:
    FUN_005c5360();
    break;
  case 8:
    if (*(int *)(param_1 + 0x58) != 0) {
      if (*(undefined4 **)(param_1 + 0x58) != (undefined4 *)0x0) {
        (**(code **)**(undefined4 **)(param_1 + 0x58))(1);
      }
      *(undefined4 *)(param_1 + 0x58) = 0;
    }
  }
  FUN_004dbc00();
  return;
}

