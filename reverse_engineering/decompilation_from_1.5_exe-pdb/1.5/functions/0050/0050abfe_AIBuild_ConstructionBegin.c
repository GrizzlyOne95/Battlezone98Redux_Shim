/*
 * Entry: 0050abfe
 * Name: AIBuild_ConstructionBegin
 * Namespace: Global
 * Signature: void AIBuild_ConstructionBegin(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ConstructionBegin(int param_1,int param_2)

{
  uchar uVar1;
  
  number_under_construction[param_1][param_2] = number_under_construction[param_1][param_2] + 1;
  uVar1 = PREREQ_IsBuilding((ushort)param_2);
  if (uVar1 != '\0') {
    facilities_under_construction[param_1] = facilities_under_construction[param_1] + 1;
  }
  return;
}
