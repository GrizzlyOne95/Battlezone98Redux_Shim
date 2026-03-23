
void FUN_00505b50(int *param_1,undefined4 param_2)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = (int)*(char *)(*param_1 + -1) & 0x1f;
  if (local_c == 0x1f) {
    local_c = (uint)*(char *)*param_1;
    *param_1 = *param_1 + 1;
  }
  FUN_0082c68b(param_2,0,0);
  for (local_8 = 0; local_8 < (int)local_c; local_8 = local_8 + 1) {
    FUN_00506010(param_1,param_2);
    FUN_00506010(param_1,param_2);
    FUN_0082ced4(param_2,0xfffffffd);
  }
  return;
}

