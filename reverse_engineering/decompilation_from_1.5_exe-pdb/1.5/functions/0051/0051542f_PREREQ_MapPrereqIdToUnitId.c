/*
 * Entry: 0051542f
 * Name: PREREQ_MapPrereqIdToUnitId
 * Namespace: Global
 * Signature: int PREREQ_MapPrereqIdToUnitId(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PREREQ_MapPrereqIdToUnitId(int param_1)

{
  return *(int *)PREREQ_table[param_1].data;
}
