
void FUN_00693d50(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_164 [4];
  uint local_160;
  int local_15c;
  char local_158 [256];
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006a6030("Loading Building Matchings");
  for (local_15c = 0; local_15c < 0x3c; local_15c = local_15c + 1) {
    *(undefined4 *)(param_2 + 0x228 + local_15c * 4) = 0x3f800000;
    *(undefined4 *)(param_2 + 0x318 + local_15c * 4) = 0;
  }
  iVar2 = FUN_0069d0a0(param_1,"My_Building_Matchings",local_164);
  FUN_006a6030("Building Matchings Count: %d.",iVar2);
  for (local_15c = 0; local_15c < iVar2; local_15c = local_15c + 1) {
    sprintf(local_158,"My_Building_Matchings[%d].unit_name",local_15c);
    FUN_0069cfa0();
    sprintf(local_158,"My_Building_Matchings[%d].multiplier",local_15c);
    fVar5 = (float10)FUN_0069cef0(param_1,local_158,local_164);
    sprintf(local_158,"My_Building_Matchings[%d].build_pos",local_15c);
    uVar3 = FUN_0069ce40(param_1,local_158,local_164);
    local_160 = FUN_006a04b0(local_58);
    local_160 = local_160 & 0xffff;
    cVar1 = FUN_006a0640(local_160);
    if (cVar1 == '\0') {
      FUN_006a5f50();
    }
    else {
      cVar1 = FUN_006a05c0(local_160 & 0xffff);
      if (cVar1 == '\0') {
        FUN_006a5f50();
      }
      else {
        iVar4 = FUN_006a0480(local_160);
        FUN_006a6030("Multiplier of %f for %s, building %d (prereq id %d)",(double)(float)fVar5,
                     local_58,iVar4,local_160);
        *(float *)(param_2 + 0x228 + iVar4 * 4) = (float)fVar5;
        *(undefined4 *)(param_2 + 0x318 + iVar4 * 4) = uVar3;
      }
    }
  }
  FUN_0083e885();
  return;
}

