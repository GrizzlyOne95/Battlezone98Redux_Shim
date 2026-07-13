/*
 * Entry: 0050d4da
 * Name: AIP_Load_Force_Matching
 * Namespace: Global
 * Signature: void AIP_Load_Force_Matching(void * param_1, tagAIP_struct * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AIP_Load_Force_Matching(void *param_1,tagAIP_struct *param_2)

{
  uchar uVar1;
  ushort uVar2;
  int iVar3;
  float *pfVar4;
  double dVar5;
  char *pcVar6;
  int local_168;
  void *local_164;
  int local_160;
  int local_15c;
  char local_158 [104];
  undefined1 local_f0 [152];
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_f0;
  local_164 = param_1;
  tlog_ild("Loading Force Matchings");
  pfVar4 = param_2->unit_multiplier;
  for (iVar3 = 100; iVar3 != 0; iVar3 = iVar3 + -1) {
    *pfVar4 = 1.0;
    pfVar4 = pfVar4 + 1;
  }
  local_160 = IParse_Get_Struct_Array_Element_Count(param_1,"My_Matchings",&local_168);
  tlog_ild("Force Matchings Count: %d.");
  local_15c = 0;
  if (0 < local_160) {
    do {
      sprintf(local_158,"My_Matchings[%d].unit_name",local_15c);
      IParse_Get_Runtime_String_Field(local_164,local_158,&local_168,local_58);
      sprintf(local_158,"My_Matchings[%d].multiplier",local_15c);
      dVar5 = IParse_Get_Runtime_Float_Field(local_164,local_158,&local_168);
      uVar2 = PREREQ_WhatIs(local_58);
      uVar1 = PREREQ_IsValid(uVar2);
      if (uVar1 == '\0') {
        pcVar6 = "UNKOWN PREREQ \'%s\' IN FORCE MATCHING AT %d\n";
LAB_0050d5c6:
        tlog(1,pcVar6);
      }
      else {
        uVar1 = PREREQ_IsUnit(uVar2);
        if (uVar1 == '\0') {
          pcVar6 = "NON-UNIT \'%s\' IN FORCE MATCHING AT %d\n";
          goto LAB_0050d5c6;
        }
        iVar3 = PREREQ_MapPrereqIdToUnitId((uint)uVar2);
        tlog_ild("Multiplier of %f for %s, unit %d (prereq id %d)");
        param_2->unit_multiplier[iVar3] = (float)dVar5;
      }
      local_15c = local_15c + 1;
    } while (local_15c < local_160);
  }
  return;
}
