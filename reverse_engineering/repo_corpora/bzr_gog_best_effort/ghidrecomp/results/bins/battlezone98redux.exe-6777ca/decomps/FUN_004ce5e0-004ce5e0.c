
void FUN_004ce5e0(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int local_30;
  uint local_2c;
  uint local_28;
  undefined4 local_24;
  undefined1 local_1d;
  int local_1c;
  char local_15;
  char local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,0,1,param_3);
    FUN_004ce0b0();
    iVar1 = sscanf(DAT_0260db08,"%*s [%d] =",&local_30);
    local_1d = iVar1 == 1;
    local_28 = (uint)(byte)local_1d;
    FUN_004ce100();
    for (local_1c = 0; local_1c < local_30; local_1c = local_1c + 1) {
      FUN_004ce0b0();
      iVar1 = sscanf(DAT_0260db08,"%s",local_14);
      if ((local_14[0] == 't') || (local_14[0] == 'T')) {
        local_24 = 1;
      }
      else {
        local_24 = 0;
      }
      *(undefined1 *)(param_2 + local_1c) = (undefined1)local_24;
      local_15 = iVar1 == 1;
      local_2c = (uint)(byte)local_15;
      FUN_004ce100();
      if (local_15 == '\0') break;
    }
  }
  else {
    FUN_004cdf10(1,param_3,param_2);
  }
  FUN_0083e885();
  return;
}

