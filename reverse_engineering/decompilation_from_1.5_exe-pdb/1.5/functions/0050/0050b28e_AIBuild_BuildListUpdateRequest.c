/*
 * Entry: 0050b28e
 * Name: AIBuild_BuildListUpdateRequest
 * Namespace: Global
 * Signature: void AIBuild_BuildListUpdateRequest(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_BuildListUpdateRequest(tag_team *param_1)

{
  (param_1->aibuild).build_list.update_required = 1;
  return;
}
