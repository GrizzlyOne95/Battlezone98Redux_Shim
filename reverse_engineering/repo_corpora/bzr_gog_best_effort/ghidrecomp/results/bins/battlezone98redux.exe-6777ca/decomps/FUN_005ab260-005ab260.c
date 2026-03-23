
bool __thiscall FUN_005ab260(int param_1,float param_2)

{
  if (param_2 < *(float *)(param_1 + 0x6c)) {
    *(float *)(param_1 + 0x6c) = param_2;
  }
  return *(float *)(param_1 + 0x6c) + 10.0 < param_2;
}

