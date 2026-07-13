/*
 * Entry: 0050d64d
 * Name: AIP_Load_Building_Matching
 * Namespace: Global
 * Signature: void AIP_Load_Building_Matching(void * param_1, tagAIP_struct * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AIP_Load_Building_Matching(void *param_1,tagAIP_struct *param_2)

{
  uchar uVar1;
  ushort uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  char *pcVar7;
  int local_164;
  int local_160;
  int local_15c;
  char local_158 [100];
  undefined1 local_f4 [156];
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_f4;
  tlog_ild("Loading Building Matchings");
  piVar3 = param_2->building_pos;
  iVar5 = 0x3c;
  do {
    *piVar3 = 0;
    piVar3[-0x3c] = 0x3f800000;
    piVar3 = piVar3 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  local_160 = IParse_Get_Struct_Array_Element_Count(param_1,"My_Building_Matchings",&local_164);
  tlog_ild("Building Matchings Count: %d.");
  local_15c = 0;
  if (0 < local_160) {
    do {
      sprintf(local_158,"My_Building_Matchings[%d].unit_name",local_15c);
      IParse_Get_Runtime_String_Field(param_1,local_158,&local_164,local_58);
      sprintf(local_158,"My_Building_Matchings[%d].multiplier",local_15c);
      dVar6 = IParse_Get_Runtime_Float_Field(param_1,local_158,&local_164);
      sprintf(local_158,"My_Building_Matchings[%d].build_pos",local_15c);
      iVar5 = IParse_Get_Runtime_Int_Field(param_1,local_158,&local_164);
      uVar2 = PREREQ_WhatIs(local_58);
      uVar1 = PREREQ_IsValid(uVar2);
      if (uVar1 == '\0') {
        pcVar7 = "UNKOWN PREREQ \'%s\' IN BUILDING MATCHING AT %d\n";
LAB_0050d764:
        tlog(1,pcVar7);
      }
      else {
        uVar1 = PREREQ_IsBuilding(uVar2);
        if (uVar1 == '\0') {
          pcVar7 = "NON-BUILDING \'%s\' IN FORCE MATCHING AT %d\n";
          goto LAB_0050d764;
        }
        iVar4 = PREREQ_MapPrereqIdToBuildingId((uint)uVar2);
        tlog_ild("Multiplier of %f for %s, building %d (prereq id %d)");
        param_2->building_multiplier[iVar4] = (float)dVar6;
        param_2->building_pos[iVar4] = iVar5;
      }
      local_15c = local_15c + 1;
    } while (local_15c < local_160);
  }
  return;
}
