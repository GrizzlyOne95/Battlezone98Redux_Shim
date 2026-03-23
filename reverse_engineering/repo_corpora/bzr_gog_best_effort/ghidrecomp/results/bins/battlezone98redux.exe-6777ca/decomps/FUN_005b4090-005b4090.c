
void __fastcall FUN_005b4090(int *param_1)

{
  switch(param_1[6]) {
  case 1:
  case 2:
  case 3:
  case 6:
    (**(code **)(*param_1 + 0x28))();
    break;
  case 4:
    param_1[4] = 0;
    if ((undefined4 *)param_1[0xb] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0xb])(1);
    }
    param_1[0xb] = 0;
    break;
  case 5:
  case 8:
    if ((undefined4 *)param_1[0xb] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0xb])(1);
    }
    param_1[0xb] = 0;
    break;
  case 7:
    if (param_1[0xb] != 0) {
      if ((undefined4 *)param_1[0xb] != (undefined4 *)0x0) {
        (*(code *)**(undefined4 **)param_1[0xb])(1);
      }
      param_1[0xb] = 0;
    }
  }
  FUN_004dbc00();
  return;
}

