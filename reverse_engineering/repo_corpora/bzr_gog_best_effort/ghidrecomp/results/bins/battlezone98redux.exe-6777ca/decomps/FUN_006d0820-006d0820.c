
void __thiscall FUN_006d0820(int param_1,uint param_2)

{
  if (param_2 == 0) {
    FUN_006d0870(0xffffffff);
  }
  else {
    FUN_006d1110(param_1);
    *(uint *)(param_1 + 8) = param_2 & *(uint *)(param_1 + 4) | *(uint *)(param_1 + 8);
    FUN_006d1140();
  }
  return;
}

