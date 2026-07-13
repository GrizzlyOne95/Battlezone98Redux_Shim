/*
 * Entry: 0050ac28
 * Name: AIBuild_ConstructionEnd
 * Namespace: Global
 * Signature: void AIBuild_ConstructionEnd(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AIBuild_ConstructionEnd(int param_1,int param_2)

{
  int *piVar1;
  uchar uVar2;
  
  Debug_Assert((uint)(0 < number_under_construction[param_1][param_2]),0x1e3,
               ".\\Schedule\\Aibuild.cpp","number_under_construction[team][prereq_type] > 0");
  number_under_construction[param_1][param_2] = number_under_construction[param_1][param_2] + -1;
  uVar2 = PREREQ_IsBuilding((ushort)param_2);
  if (uVar2 != '\0') {
    piVar1 = facilities_under_construction + param_1;
    Debug_Assert((uint)(0 < *piVar1),0x1e7,".\\Schedule\\Aibuild.cpp",
                 "facilities_under_construction[team] > 0");
    *piVar1 = *piVar1 + -1;
  }
  return;
}
