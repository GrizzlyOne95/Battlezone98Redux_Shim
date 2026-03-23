
void __fastcall FUN_005941f0(char *param_1)

{
  if ((param_1[0x38] == '\0') && (*param_1 != '\0')) {
    FUN_004d9630(param_1);
    if (DAT_02a13cc0 != 0) {
      *(undefined4 *)(DAT_02a13cc0 + 0x18) = *(undefined4 *)(param_1 + 0x30);
    }
    (**(code **)(*(int *)(DAT_02a13cc4 + 0x18) + 8))(*(undefined4 *)(param_1 + 0x34));
  }
  return;
}

