
void __thiscall FUN_0083d7b0(int *param_1,uint param_2)

{
  uint uVar1;
  
  if (param_2 <= (uint)(param_1[2] - param_1[1] >> 2)) {
    return;
  }
  if (0x3fffffffU - (param_1[1] - *param_1 >> 2) < param_2) {
                    /* WARNING: Subroutine does not return */
    std::_Xlength_error("vector<T> too long");
  }
  uVar1 = param_1[2] - *param_1 >> 2;
  if (0x3fffffff - (uVar1 >> 1) < uVar1) {
    FUN_0083d730();
    return;
  }
  FUN_0083d730();
  return;
}

