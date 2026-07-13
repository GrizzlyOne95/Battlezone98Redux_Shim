/*
 * Entry: 0050ad9e
 * Name: AIBuild_AreFacilitiesUnderConstruction
 * Namespace: Global
 * Signature: uchar AIBuild_AreFacilitiesUnderConstruction(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl AIBuild_AreFacilitiesUnderConstruction(int param_1)

{
  return 0 < facilities_under_construction[param_1];
}
