/*
 * Entry: 00507d44
 * Name: AI_StrengthGreater
 * Namespace: Global
 * Signature: int AI_StrengthGreater(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_StrengthGreater(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  TEAM_RELATION TVar3;
  int *piVar4;
  int iVar5;
  char *pcVar6;
  int local_14;
  int local_10;
  int local_8;
  
  tlog_gdm("AI_StrengthGreater::Begins (team %d, percentage %d)\n");
  bVar2 = false;
  iVar5 = teamdata[param_1].unitcount;
  local_8 = 0;
  local_14 = 1;
  piVar4 = &teamdata[0].unitcount;
  do {
    if (local_8 != param_1) {
      TVar3 = Team_GetRelation(local_8,param_1);
      if (TVar3 == TR_ENEMY) {
        iVar1 = *piVar4;
        tlog_gdm("  [%d] = %d units\n");
        if ((!bVar2) || (local_10 < iVar1)) {
          bVar2 = true;
          local_10 = iVar1;
        }
      }
    }
    local_8 = local_8 + 1;
    piVar4 = piVar4 + 0x7a;
  } while ((int)piVar4 < 0xcd592c);
  if (bVar2) {
    pcVar6 = "  enemy found\n";
  }
  else {
    pcVar6 = "  enemy not found\n";
  }
  tlog_gdm(pcVar6);
  if (bVar2) {
    tlog_gdm("  team strength %d max str %d\n");
    iVar5 = iVar5 * 100;
    if (iVar5 - local_10 * param_2 == 0 || iVar5 < local_10 * param_2) {
      local_14 = 0;
      pcVar6 = "  NOT STRONGER\n";
      goto LAB_00507e18;
    }
  }
  pcVar6 = "  STRONGER\n";
LAB_00507e18:
  tlog_gdm(pcVar6);
  return local_14;
}
