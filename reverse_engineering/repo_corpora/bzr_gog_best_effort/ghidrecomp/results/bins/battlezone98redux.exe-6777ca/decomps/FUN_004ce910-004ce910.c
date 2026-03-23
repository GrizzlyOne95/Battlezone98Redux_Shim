
void FUN_004ce910(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int local_60;
  uint local_5c;
  uint local_58;
  undefined1 local_51;
  int local_50;
  char local_49;
  undefined1 local_48 [64];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,0,4,param_3);
    FUN_004ce0b0();
    iVar1 = sscanf(DAT_0260db08,"%s [%d] =",local_48,&local_60);
    local_51 = iVar1 == 2;
    local_58 = (uint)(byte)local_51;
    FUN_004ce100();
    for (local_50 = 0; local_50 < local_60; local_50 = local_50 + 1) {
      FUN_004ce0b0();
      iVar1 = sscanf(DAT_0260db08,"%ld",param_2 + local_50 * 4);
      local_49 = iVar1 == 1;
      local_5c = (uint)(byte)local_49;
      FUN_004ce100();
      if (local_49 == '\0') break;
    }
  }
  else {
    FUN_004cdda0(4,param_3,param_2);
  }
  FUN_0083e885();
  return;
}

