
void FUN_0043b040(undefined4 *param_1,undefined4 *param_2)

{
  if ((param_2 != (undefined4 *)0x0) || (param_1 != (undefined4 *)0x0)) {
    *param_2 = *param_1;
    if (param_1[1] == -1) {
      param_2[1] = 0x32;
    }
    else {
      param_2[1] = param_1[1];
    }
    if (param_1[2] == -1) {
      param_2[2] = 4;
    }
    else {
      param_2[2] = param_1[2];
    }
    if (param_1[3] == -1) {
      param_2[3] = 0;
    }
    else {
      param_2[3] = param_1[3];
    }
    if (param_1[5] == -1) {
      param_2[5] = 0;
    }
    else {
      param_2[5] = param_1[5];
    }
    if (param_1[4] == -1) {
      param_2[4] = 100;
    }
    else {
      param_2[4] = param_1[4];
    }
  }
  return;
}

