
void FUN_0043b110(int param_1,int param_2)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    if (*(int *)(param_2 + 4) == -1) {
      *(undefined4 *)(param_2 + 4) = 0x32;
    }
    if ((param_1 != param_2) && (*(int *)(param_1 + 4) != -1)) {
      *(int *)(param_2 + 4) = *(int *)(param_2 + 4) + *(int *)(param_1 + 4);
    }
    if (*(int *)(param_1 + 8) == -1) {
      if (*(int *)(param_2 + 8) == -1) {
        *(undefined4 *)(param_2 + 8) = 4;
      }
    }
    else {
      *(undefined4 *)(param_2 + 8) = *(undefined4 *)(param_1 + 8);
    }
    if (*(int *)(param_1 + 0xc) == -1) {
      if (*(int *)(param_2 + 0xc) == -1) {
        *(undefined4 *)(param_2 + 0xc) = 0;
      }
    }
    else {
      *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(param_1 + 0xc);
    }
    if (*(int *)(param_1 + 0x14) == -1) {
      if (*(int *)(param_2 + 0x14) == -1) {
        *(undefined4 *)(param_2 + 0x14) = 0;
      }
    }
    else {
      *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(param_1 + 0x14);
    }
    if (*(int *)(param_1 + 0x10) == -1) {
      if (*(int *)(param_2 + 0x10) == -1) {
        *(undefined4 *)(param_2 + 0x10) = 100;
      }
    }
    else {
      *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_1 + 0x10);
    }
  }
  return;
}

