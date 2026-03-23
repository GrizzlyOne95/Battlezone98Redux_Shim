
int __fastcall FUN_00575ff0(int param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 100;
  for (local_8 = *(uint *)(param_1 + 0x1b0) & 0x3ff; local_8 != 0; local_8 = local_8 >> 1) {
    if ((local_8 & 1) != 0) {
      local_c = local_c + -10;
    }
  }
  return local_c;
}

