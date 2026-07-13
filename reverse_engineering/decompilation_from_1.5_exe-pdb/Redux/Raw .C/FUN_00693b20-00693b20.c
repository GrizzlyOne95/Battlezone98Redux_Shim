
void FUN_00693b20(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_164 [4];
  undefined2 local_160;
  int local_15c;
  char local_158 [256];
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006a6030("Loading Force Matchings");
  for (local_15c = 0; local_15c < 100; local_15c = local_15c + 1) {
    *(undefined4 *)(param_2 + 0x98 + local_15c * 4) = 0x3f800000;
  }
  iVar2 = FUN_0069d0a0(param_1,"My_Matchings",local_164);
  FUN_006a6030("Force Matchings Count: %d.",iVar2);
  for (local_15c = 0; local_15c < iVar2; local_15c = local_15c + 1) {
    sprintf(local_158,"My_Matchings[%d].unit_name",local_15c);
    FUN_0069cfa0();
    sprintf(local_158,"My_Matchings[%d].multiplier",local_15c);
    fVar4 = (float10)FUN_0069cef0(param_1,local_158,local_164);
    local_160 = FUN_006a04b0(local_58);
    cVar1 = FUN_006a0640(local_160);
    if (cVar1 == '\0') {
      FUN_006a5f50();
    }
    else {
      cVar1 = FUN_006a0600(local_160);
      if (cVar1 == '\0') {
        FUN_006a5f50();
      }
      else {
        iVar3 = FUN_006a0460(local_160);
        FUN_006a6030("Multiplier of %f for %s, unit %d (prereq id %d)",(double)(float)fVar4,local_58
                     ,iVar3,local_160);
        *(float *)(param_2 + 0x98 + iVar3 * 4) = (float)fVar4;
      }
    }
  }
  FUN_0083e885();
  return;
}

