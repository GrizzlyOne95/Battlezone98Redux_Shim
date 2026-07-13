/*
 * Entry: 0050b2a8
 * Name: AIBuild_BuildListInit
 * Namespace: Global
 * Signature: void AIBuild_BuildListInit(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_BuildListInit(tag_team *param_1)

{
  (param_1->aibuild).build_list.nodes = 0;
  (param_1->aibuild).build_list.update_required = 0;
  (param_1->aibuild).build_list.account_first = 1;
  return;
}
