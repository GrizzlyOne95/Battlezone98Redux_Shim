
void FUN_006ba7b0(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  undefined4 local_c;
  uint local_8;
  
  local_c = param_4;
  for (local_8 = 0; local_8 < param_3; local_8 = local_8 + 1) {
    *(byte *)(param_2 + local_8) =
         *(byte *)(param_1 + local_8) ^ *(byte *)((int)&local_c + local_8 % 4);
  }
  FUN_006ba750(param_4,param_3 % 4);
  return;
}

