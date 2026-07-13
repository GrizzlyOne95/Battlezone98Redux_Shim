/*
 * Entry: 0050acff
 * Name: AIBuild_ConstructionDelete
 * Namespace: Global
 * Signature: void AIBuild_ConstructionDelete(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ConstructionDelete(int param_1)

{
  if (construction_initialised[param_1] == 1) {
    free(number_under_construction[param_1]);
    construction_initialised[param_1] = 0;
  }
  else {
    _tlog_filename = ".\\Schedule\\Aibuild.cpp";
    _tlog_line = 0x214;
    tlog(1,"AIBuild_ConstructionDelete called without New\n");
  }
  return;
}
