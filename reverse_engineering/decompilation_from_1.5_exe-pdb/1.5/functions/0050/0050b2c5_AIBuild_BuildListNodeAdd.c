/*
 * Entry: 0050b2c5
 * Name: AIBuild_BuildListNodeAdd
 * Namespace: Global
 * Signature: void AIBuild_BuildListNodeAdd(tag_team * param_1, int param_2, int param_3, int param_4, int param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AIBuild_BuildListNodeAdd
          (tag_team *param_1,int param_2,int param_3,int param_4,int param_5,int *param_6)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = (param_1->aibuild).build_list.nodes;
  if (iVar2 != 0x28) {
    (param_1->aibuild).build_list.node[iVar2].prereq_type = param_2;
    (param_1->aibuild).build_list.node[iVar2].account = param_3;
    (param_1->aibuild).build_list.node[iVar2].number_to_build = param_4;
    (param_1->aibuild).build_list.node[iVar2].build_type = param_5;
    (param_1->aibuild).build_list.node[iVar2].field4_0x10.number_left_to_build = param_6;
    piVar1 = &(param_1->aibuild).build_list.nodes;
    *piVar1 = *piVar1 + 1;
  }
  return;
}
