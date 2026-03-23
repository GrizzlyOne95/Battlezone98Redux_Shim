
int __thiscall FUN_00418c30(int param_1,int param_2)

{
  undefined4 local_c;
  
  local_c = param_2 - *(int *)(param_1 + 0x34);
  if (*(int *)(param_1 + 0x38) < local_c) {
    local_c = *(int *)(param_1 + 0x38);
  }
  else if (local_c < -*(int *)(param_1 + 0x38)) {
    local_c = -*(int *)(param_1 + 0x38);
  }
  return local_c;
}

