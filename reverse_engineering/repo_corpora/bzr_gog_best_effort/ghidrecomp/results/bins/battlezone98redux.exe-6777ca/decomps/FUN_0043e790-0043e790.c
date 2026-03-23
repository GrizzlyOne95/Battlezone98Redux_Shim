
size_t FUN_0043e790(void *param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  undefined4 local_c;
  
  uVar1 = *(int *)(param_4 + 0x18) - *(int *)(param_4 + 0x2f0);
  local_c = param_2 * param_3;
  if (uVar1 < (uint)(param_2 * param_3)) {
    local_c = uVar1;
  }
  memcpy(param_1,(void *)(*(int *)(param_4 + 0x14) + *(int *)(param_4 + 0x2f0)),local_c);
  *(uint *)(param_4 + 0x2f0) = *(int *)(param_4 + 0x2f0) + local_c;
  return local_c;
}

