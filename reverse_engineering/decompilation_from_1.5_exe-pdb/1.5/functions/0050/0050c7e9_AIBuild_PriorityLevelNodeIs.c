/*
 * Entry: 0050c7e9
 * Name: AIBuild_PriorityLevelNodeIs
 * Namespace: Global
 * Signature: void AIBuild_PriorityLevelNodeIs(tagCP_ACCOUNT * param_1, int param_2, int param_3, ushort param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AIBuild_PriorityLevelNodeIs
          (tagCP_ACCOUNT *param_1,int param_2,int param_3,ushort param_4,int param_5)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  Debug_Assert((int)param_1,0xeb5,".\\Schedule\\Aibuild.cpp","account");
  if ((param_2 < 0) || (param_1->priority_levels <= param_2)) {
    iVar2 = 0;
  }
  else {
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0xeb6,".\\Schedule\\Aibuild.cpp",
               "(priority_level >= 0) && (priority_level < account->priority_levels)");
  if ((param_3 < 0) || (param_1->priority_level[param_2].nodes <= param_3)) {
    iVar2 = 0;
  }
  else {
    iVar2 = 1;
  }
  Debug_Assert(iVar2,0xeb7,".\\Schedule\\Aibuild.cpp",
               "(node_number >= 0) && (node_number < account->priority_level[priority_level].nodes)"
              );
  pcVar4 = "PREREQ_IsValid (object_type)";
  pcVar3 = ".\\Schedule\\Aibuild.cpp";
  iVar2 = 0xeb8;
  bVar1 = PREREQ_IsValid(param_4);
  Debug_Assert((uint)bVar1,iVar2,pcVar3,pcVar4);
  Debug_Assert((uint)(0 < param_5),0xeb9,".\\Schedule\\Aibuild.cpp","number > 0");
  param_1->priority_level[param_2].node[param_3].object_type = param_4;
  param_1->priority_level[param_2].node[param_3].field1_0x4.number_to_have = param_5;
  return;
}
