
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_00693520(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_197c;
  int local_196c;
  undefined1 local_1968 [4];
  int local_1964;
  int local_1960;
  int local_195c [512];
  int aiStack_115c [512];
  int aiStack_95c [513];
  char local_158 [256];
  undefined1 local_58 [80];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1960 = 0;
  local_197c = -1;
  FUN_006a6030("Loading Account");
  iVar2 = FUN_0069d0a0(param_1,param_3,local_1968);
  for (local_195c[0] = 0; local_195c[0] < iVar2; local_195c[0] = local_195c[0] + 1) {
    sprintf(local_158,"%s[%d].priority",param_3,local_195c[0]);
    iVar3 = FUN_0069ce40(param_1,local_158,local_1968);
    if (iVar3 == local_197c) {
      aiStack_95c[local_1960] = aiStack_95c[local_1960] + 1;
    }
    else {
      local_1960 = local_1960 + 1;
      aiStack_95c[local_1960] = 1;
      aiStack_115c[local_1960] = iVar3;
      sprintf(local_158,"%s[%d].build_type",param_3,local_195c[0]);
      iVar4 = FUN_0069ce40(param_1,local_158,local_1968);
      local_195c[local_1960] = iVar4;
      local_197c = iVar3;
    }
  }
  FUN_006a6030("  There are %d priority levels",local_1960);
  uVar5 = FUN_00693380(local_1960);
  local_1964 = 0;
  for (local_195c[0] = 0; local_195c[0] < local_1960; local_195c[0] = local_195c[0] + 1) {
    FUN_006a5fd0("Loading Prioirty Level %d pri %d nodes %d build type %d\n",local_195c[0],
                 aiStack_115c[local_195c[0] + 1],aiStack_95c[local_195c[0] + 1],
                 local_195c[local_195c[0] + 1]);
    FUN_00693430(uVar5,local_195c[0],aiStack_115c[local_195c[0] + 1],aiStack_95c[local_195c[0] + 1],
                 local_195c[local_195c[0] + 1]);
    for (local_196c = 0; local_196c < aiStack_95c[local_195c[0] + 1]; local_196c = local_196c + 1) {
      sprintf(local_158,"%s[%d].item_name",param_3,local_1964);
      FUN_0069cfa0(param_1,local_158,local_1968,local_58);
      sprintf(local_158,"%s[%d].build_amount",param_3,local_1964);
      uVar6 = FUN_0069ce40(param_1,local_158,local_1968);
      FUN_006a6030("  Loading Node %s with a priority of %d. Type, Amount = [%d, %d]",local_58,
                   aiStack_115c[local_195c[0] + 1],local_195c[local_195c[0] + 1],uVar6);
      sVar1 = FUN_006a04b0(local_58);
      if (sVar1 == 0) {
        FUN_006a5f50(1,"UNKOWN UNIT OR BUILDING TYPE \'%s\' ADDED TO ACCOUNT \'%s\'\n",local_58,
                     param_3);
      }
      else {
        FUN_006934e0(uVar5,local_195c[0],local_196c,sVar1,uVar6);
      }
      local_1964 = local_1964 + 1;
    }
  }
  FUN_0083e885();
  return;
}

