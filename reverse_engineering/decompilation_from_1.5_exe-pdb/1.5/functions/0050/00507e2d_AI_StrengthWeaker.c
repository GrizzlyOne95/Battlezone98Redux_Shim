/*
 * Entry: 00507e2d
 * Name: AI_StrengthWeaker
 * Namespace: Global
 * Signature: int AI_StrengthWeaker(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_StrengthWeaker(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  TEAM_RELATION TVar4;
  int iVar5;
  char *pcVar6;
  int local_14;
  int *local_c;
  int local_8;
  
  tlog_gdm("AI_StrengthWeaker::Begins (team %d, percentage %d)\n");
  iVar1 = teamdata[param_1].unitcount;
  local_14 = 0;
  bVar3 = false;
  local_8 = 0;
  local_c = &teamdata[0].unitcount;
  iVar5 = param_1;
  do {
    if (local_8 != param_1) {
      TVar4 = Team_GetRelation(local_8,param_1);
      if (TVar4 == TR_ENEMY) {
        iVar2 = *local_c;
        tlog_gdm("  [%d] = %d units\n");
        if ((!bVar3) || (iVar5 < iVar2)) {
          bVar3 = true;
          iVar5 = iVar2;
        }
      }
    }
    local_c = local_c + 0x7a;
    local_8 = local_8 + 1;
  } while ((int)local_c < 0xcd592c);
  if (bVar3) {
    tlog_gdm("  team strength %d max str %d\n");
    if (iVar1 * 100 < iVar5 * param_2) {
      local_14 = 1;
      pcVar6 = "  WEAKER\n";
      goto LAB_00507ef5;
    }
  }
  pcVar6 = "  NOT WEAKER\n";
LAB_00507ef5:
  tlog_gdm(pcVar6);
  return local_14;
}
