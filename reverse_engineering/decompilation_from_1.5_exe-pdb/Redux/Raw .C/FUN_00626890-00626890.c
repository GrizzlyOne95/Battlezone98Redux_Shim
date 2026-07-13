
bool FUN_00626890(int param_1,int param_2)

{
  bool local_8;
  
  local_8 = *(float *)(param_2 + 0x50) <= *(float *)(param_1 + 0x50) &&
            *(float *)(param_1 + 0x50) != *(float *)(param_2 + 0x50);
  return local_8;
}

