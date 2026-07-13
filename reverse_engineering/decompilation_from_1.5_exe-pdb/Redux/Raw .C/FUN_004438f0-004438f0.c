
void FUN_004438f0(int *param_1)

{
  switch(*(undefined4 *)(*param_1 + 0x84)) {
  case 1:
  case 3:
  case 4:
    FUN_00443c40(param_1);
    break;
  case 2:
  case 6:
  case 8:
  case 10:
    if (param_1[9] == 1) {
      free((void *)param_1[10]);
      param_1[10] = 0;
    }
    param_1[9] = 3;
    DAT_0260c92c = 0x3000;
    FUN_00443a80(*param_1,&DAT_008fe1e0);
    break;
  case 5:
  case 7:
  case 0xf:
    if (param_1[9] == 1) {
      free((void *)param_1[10]);
      param_1[10] = 0;
    }
    param_1[9] = 3;
    DAT_0260c92c = 0x2000;
    FUN_00443a80(*param_1,&DAT_008fe1e0);
  }
  return;
}

