/*
 * Entry: 0050b29d
 * Name: AIBuild_BuildListUpdateRequested
 * Namespace: Global
 * Signature: int AIBuild_BuildListUpdateRequested(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_BuildListUpdateRequested(tag_team *param_1)

{
  return (param_1->aibuild).build_list.update_required;
}
