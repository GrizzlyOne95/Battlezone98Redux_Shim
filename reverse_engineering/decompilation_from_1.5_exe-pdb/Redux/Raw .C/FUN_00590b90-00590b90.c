
void FUN_00590b90(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    if ((param_1[4] & 4) != 0) {
      param_1[4] = param_1[4] & 0xfffffffb;
      FUN_0058f490();
    }
    if (param_1 != (undefined4 *)0x0) {
      (**(code **)*param_1)(1);
    }
  }
  return;
}

