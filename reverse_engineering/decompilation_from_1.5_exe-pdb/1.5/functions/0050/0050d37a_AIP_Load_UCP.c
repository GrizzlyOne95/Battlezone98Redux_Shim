/*
 * Entry: 0050d37a
 * Name: AIP_Load_UCP
 * Namespace: Global
 * Signature: void AIP_Load_UCP(void * param_1, tagAIP_struct * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AIP_Load_UCP(void *param_1,tagAIP_struct *param_2)

{
  tagCONSTRUCTION_PROGRAM *ptVar1;
  int iVar2;
  int iVar3;
  tagCP_ACCOUNT *ptVar4;
  int iVar5;
  int local_164;
  int local_160;
  void *local_15c;
  char local_158 [108];
  undefined1 local_ec [148];
  char local_58 [80];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_ec;
  local_15c = param_1;
  ptVar1 = AIBuild_ConstructionProgramNew();
  param_2->the_construction_program = ptVar1;
  tlog_ild("Loading UCP");
  iVar5 = 0;
  iVar2 = 0;
  do {
    *(undefined4 *)(iVar2 + (int)param_2->budget) = 0;
    iVar2 = iVar2 + 4;
  } while (iVar2 < 0x80);
  local_160 = IParse_Get_Struct_Array_Element_Count(param_1,"unit_construction_program",&local_164);
  tlog_ild("Account Count: %d.");
  if (0 < local_160) {
    do {
      sprintf(local_158,"unit_construction_program[%d].account_name",iVar5);
      IParse_Get_Runtime_String_Field(local_15c,local_158,&local_164,local_58);
      sprintf(local_158,"unit_construction_program[%d].budget",iVar5);
      iVar2 = IParse_Get_Runtime_Int_Field(local_15c,local_158,&local_164);
      sprintf(local_158,"unit_construction_program[%d].max_reserve",iVar5);
      iVar3 = IParse_Get_Runtime_Int_Field(local_15c,local_158,&local_164);
      tlog_ild("Loading account %s with a budget of %d max reserve %d.");
      ptVar4 = AIP_Load_Account(local_15c,param_2,local_58);
      AIBuild_ConstructionProgramAddAccount(param_2->the_construction_program,iVar5,ptVar4);
      if (iVar5 != 0) {
        param_2->budget[iVar5] = iVar2;
        param_2->max_reserve[iVar5] = iVar3;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < local_160);
  }
  return;
}
