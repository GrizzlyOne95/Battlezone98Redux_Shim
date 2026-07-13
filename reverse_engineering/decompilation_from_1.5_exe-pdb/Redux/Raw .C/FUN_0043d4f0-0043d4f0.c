
void FUN_0043d4f0(int param_1)

{
  undefined4 local_8;
  
  local_8 = DAT_00915640;
  if ((DAT_00915640 != 0) && (param_1 != 0)) {
    local_8 = *(int *)(DAT_00915640 + 0x20);
  }
  for (; local_8 != 0; local_8 = FUN_0043d540(local_8)) {
  }
  DAT_00915640 = 0;
  return;
}

