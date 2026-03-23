
void FUN_0062cb60(int param_1,undefined4 param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x18) = param_2;
    FUN_0062cb60(*(undefined4 *)(param_1 + 0x80),param_2);
    FUN_0062cb60(*(undefined4 *)(param_1 + 0x7c),param_2);
  }
  return;
}

