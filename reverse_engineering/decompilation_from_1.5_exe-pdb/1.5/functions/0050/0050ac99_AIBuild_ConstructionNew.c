/*
 * Entry: 0050ac99
 * Name: AIBuild_ConstructionNew
 * Namespace: Global
 * Signature: void AIBuild_ConstructionNew(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ConstructionNew(int param_1)

{
  int iVar1;
  int *piVar2;
  size_t _Size;
  
  if (construction_initialised[param_1] == 0) {
    _Size = 4;
    iVar1 = Units_UnitTypeCount();
    piVar2 = calloc(iVar1 + 1 + maxbuildingtypes,_Size);
    facilities_under_construction[param_1] = 0;
    number_under_construction[param_1] = piVar2;
    construction_initialised[param_1] = 1;
  }
  else {
    _tlog_filename = ".\\Schedule\\Aibuild.cpp";
    _tlog_line = 0x208;
    tlog(1,"AIBuild_ConstructionNew called twice with no delete\n");
  }
  return;
}
