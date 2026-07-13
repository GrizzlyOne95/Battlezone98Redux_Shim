
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006902b0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int local_100c;
  undefined1 local_1008 [4096];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_100c = 0;
  iVar1 = FUN_0068f4d0(local_1008,param_2);
  if (iVar1 != 0) {
    FUN_006a5fd0("Loading AIP \'%s\'\n",local_1008);
    local_100c = FUN_00693fe0(local_1008);
    if (local_100c != 0) {
      FUN_0069d330(&DAT_00930f68,local_100c);
      FUN_006a5fd0("  Loaded OK");
    }
  }
  if (local_100c == 0) {
    _DAT_009310bc = "Schedule\\Ai.cpp";
    _DAT_009310c0 = 0x3d3;
    FUN_006a5f50(1,"Could not find / could not load AIP \'%s\'",param_2);
  }
  FUN_0083e885();
  return;
}

