/*
 * Entry: 0050c310
 * Name: AIBuild_AccountDump
 * Namespace: Global
 * Signature: void AIBuild_AccountDump(tag_team * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_AccountDump(tag_team *param_1,int param_2)

{
  tagCONSTRUCTION_PROGRAM *ptVar1;
  tagCP_PRIORITY_LEVEL *ptVar2;
  tagCP_ACCOUNT **pptVar3;
  int iVar4;
  char *pcVar5;
  int local_10;
  int local_8;
  
  Debug_Assert((int)param_1,0xd3b,".\\Schedule\\Aibuild.cpp","the_team");
  tlog_gdm("AIBuild AccountDump Team %d Account %d\n");
  ptVar1 = (param_1->aibuild).construction_program;
  if (ptVar1 == (tagCONSTRUCTION_PROGRAM *)0x0) {
    pcVar5 = "  No construction program\n";
  }
  else {
    pptVar3 = ptVar1->account + param_2;
    if (*pptVar3 != (tagCP_ACCOUNT *)0x0) {
      local_8 = 0;
      local_10 = 0;
      do {
        ptVar2 = (*pptVar3)->priority_level;
        tlog_gdm("  Priority level %d priority %d nodes %d [%s]\n");
        iVar4 = 0;
        do {
          tlog_gdm("  #%d num %d, internal %d\n");
          iVar4 = iVar4 + 1;
        } while (iVar4 < *(int *)((int)&ptVar2->nodes + local_10));
        local_8 = local_8 + 1;
        local_10 = local_10 + 0x10;
        pptVar3 = ((param_1->aibuild).construction_program)->account + param_2;
      } while (local_8 < (*pptVar3)->priority_levels);
      return;
    }
    pcVar5 = "  No account\n";
  }
  tlog_gdm(pcVar5);
  return;
}
