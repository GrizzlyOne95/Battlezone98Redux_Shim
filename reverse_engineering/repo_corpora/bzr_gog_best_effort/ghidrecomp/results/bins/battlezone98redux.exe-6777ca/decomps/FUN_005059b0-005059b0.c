
void FUN_005059b0(int *param_1,undefined4 param_2)

{
  undefined4 local_8;
  
  local_8 = (int)*(char *)(*param_1 + -1) & 0x1f;
  if (local_8 == 0x1f) {
    local_8 = (uint)*(char *)*param_1;
    *param_1 = *param_1 + 1;
  }
  FUN_0082cd08(param_2,*param_1,local_8);
  *param_1 = *param_1 + local_8;
  return;
}

