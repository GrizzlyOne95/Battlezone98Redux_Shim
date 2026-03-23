
uint __thiscall FUN_0044eea0(int param_1,undefined4 param_2)

{
  undefined4 local_c;
  
  local_c = FUN_0044eef0(param_2);
  local_c = local_c & *(uint *)(param_1 + 0x14);
  if (*(uint *)(param_1 + 0x18) <= local_c) {
    local_c = local_c - ((*(uint *)(param_1 + 0x14) >> 1) + 1);
  }
  return local_c;
}

