
void FUN_0043d580(int param_1)

{
  undefined4 uVar1;
  int local_c;
  int local_8;
  
  local_c = DAT_00915640;
  local_8 = DAT_00915640;
  while (local_8 != 0) {
    if (*(int *)(local_8 + 0x10) == param_1) {
      if (local_8 == DAT_00915640) {
        FUN_0043d1d0("cmike.wav",param_1,2);
        local_c = DAT_00915640;
      }
      else {
        uVar1 = FUN_0043d540(local_8);
        *(undefined4 *)(local_c + 0x20) = uVar1;
      }
      if (local_c == 0) {
        local_8 = 0;
      }
      else {
        local_8 = *(int *)(local_c + 0x20);
      }
    }
    else {
      local_c = local_8;
      local_8 = *(int *)(local_8 + 0x20);
    }
  }
  return;
}

