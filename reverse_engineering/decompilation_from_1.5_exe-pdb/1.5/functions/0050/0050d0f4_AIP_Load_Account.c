/*
 * Entry: 0050d0f4
 * Name: AIP_Load_Account
 * Namespace: Global
 * Signature: tagCP_ACCOUNT * AIP_Load_Account(void * param_1, tagAIP_struct * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

tagCP_ACCOUNT * __cdecl AIP_Load_Account(void *param_1,tagAIP_struct *param_2,char *param_3)

{
  char *pcVar1;
  ushort uVar2;
  int iVar3;
  tagCP_BUILD_TYPE tVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int local_1980 [511];
  tagCP_BUILD_TYPE atStack_1184 [512];
  int local_984 [490];
  undefined1 local_1dc [92];
  int local_180;
  tagCP_BUILD_TYPE local_17c;
  int local_178;
  void *local_174;
  int local_170;
  int local_16c;
  int local_168;
  char *local_164;
  tagCP_ACCOUNT *local_160;
  int local_15c;
  char local_158 [256];
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1dc;
  local_160 = (tagCP_ACCOUNT *)0xffffffff;
  iVar6 = 0;
  local_174 = param_1;
  local_164 = param_3;
  local_180 = 0;
  tlog_ild("Loading Account");
  local_170 = IParse_Get_Struct_Array_Element_Count(param_1,param_3,&local_16c);
  local_15c = 0;
  iVar5 = local_180;
  if (0 < local_170) {
    piVar8 = local_984;
    do {
      sprintf(local_158,"%s[%d].priority",local_164,local_15c);
      iVar3 = IParse_Get_Runtime_Int_Field(local_174,local_158,&local_16c);
      iVar5 = local_15c;
      pcVar1 = local_164;
      if ((tagCP_ACCOUNT *)iVar3 == local_160) {
        *piVar8 = *piVar8 + 1;
      }
      else {
        iVar7 = iVar6 + 1;
        local_1980[iVar6] = iVar3;
        piVar8 = local_984 + iVar7;
        local_160 = (tagCP_ACCOUNT *)iVar3;
        *piVar8 = 1;
        sprintf(local_158,"%s[%d].build_type",pcVar1,iVar5);
        tVar4 = IParse_Get_Runtime_Int_Field(local_174,local_158,&local_16c);
        atStack_1184[iVar7] = tVar4;
        iVar6 = iVar7;
      }
      local_15c = local_15c + 1;
      iVar5 = iVar6;
    } while (local_15c < local_170);
  }
  local_180 = iVar5;
  tlog_ild("  There are %d priority levels");
  local_160 = AIBuild_AccountNew(iVar6);
  local_168 = 0;
  local_15c = 0;
  if (0 < iVar6) {
    do {
      local_17c = atStack_1184[local_15c + 1];
      local_170 = local_1980[local_15c];
      iVar6 = local_984[local_15c + 1];
      tlog_gdm("Loading Prioirty Level %d pri %d nodes %d build type %d\n");
      AIBuild_PriorityLevelIs(local_160,local_15c,local_170,iVar6,local_17c);
      local_178 = 0;
      if (0 < iVar6) {
        do {
          sprintf(local_158,"%s[%d].item_name",local_164,local_168);
          IParse_Get_Runtime_String_Field(local_174,local_158,&local_16c,local_58);
          sprintf(local_158,"%s[%d].build_amount",local_164,local_168);
          iVar5 = IParse_Get_Runtime_Int_Field(local_174,local_158,&local_16c);
          tlog_ild("  Loading Node %s with a priority of %d. Type, Amount = [%d, %d]");
          uVar2 = PREREQ_WhatIs(local_58);
          if (uVar2 == 0) {
            tlog(1,"UNKOWN UNIT OR BUILDING TYPE \'%s\' ADDED TO ACCOUNT \'%s\'\n");
          }
          else {
            AIBuild_PriorityLevelNodeIs(local_160,local_15c,local_178,uVar2,iVar5);
          }
          local_168 = local_168 + 1;
          local_178 = local_178 + 1;
        } while (local_178 < iVar6);
      }
      local_15c = local_15c + 1;
    } while (local_15c < local_180);
  }
  return local_160;
}
