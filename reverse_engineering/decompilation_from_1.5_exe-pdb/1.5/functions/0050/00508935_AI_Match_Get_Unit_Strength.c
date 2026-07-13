/*
 * Entry: 00508935
 * Name: AI_Match_Get_Unit_Strength
 * Namespace: Global
 * Signature: int AI_Match_Get_Unit_Strength(tagUNIT * param_1, tag_team * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl AI_Match_Get_Unit_Strength(tagUNIT *param_1,tag_team *param_2)

{
  int iVar1;
  int extraout_EAX;
  int iVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  CHAR local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  Debug_Assert((int)param_1,0x147,".\\Schedule\\AI_Match.cpp","the_unit");
  Debug_Assert((int)param_1->type,0x148,".\\Schedule\\AI_Match.cpp","the_unit->type");
  Debug_Assert((int)param_2,0x149,".\\Schedule\\AI_Match.cpp","the_team");
  iVar2 = param_1->type->unittypeid;
  Debug_Assert((uint)(-1 < iVar2),0x14b,".\\Schedule\\AI_Match.cpp","unit_type >= 0");
  pcVar5 = "unit_type < Units_UnitTypeCount()";
  pcVar4 = ".\\Schedule\\AI_Match.cpp";
  iVar3 = 0x14c;
  iVar1 = Units_UnitTypeCount();
  Debug_Assert((uint)(iVar2 < iVar1),iVar3,pcVar4,pcVar5);
  if (-1 < iVar2) {
    iVar1 = Units_UnitTypeCount();
    if (iVar2 < iVar1) goto LAB_00508a07;
  }
  iVar1 = Units_UnitTypeCount();
  sprintf("AI_Match_Get_Unit_Strength: \"%s\" unknown type %d (count=%d)",param_1->type->symbolid,
          iVar2,iVar1);
  OutputDebugStringA(local_108);
LAB_00508a07:
  _ftol2_sse();
  iVar2 = extraout_EAX;
  if (extraout_EAX < 1) {
    iVar2 = 1;
  }
  return iVar2;
}
