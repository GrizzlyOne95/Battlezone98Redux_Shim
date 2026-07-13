
void __thiscall FUN_006c9000(undefined4 *param_1,undefined4 param_2)

{
  FUN_006dc700(&param_2,0);
  if (param_1[1] == 0) {
    param_1[1] = param_2;
    *param_1 = param_2;
  }
  else {
    FUN_006dc700(param_1 + 1,param_2);
    param_1[1] = param_2;
  }
  return;
}

