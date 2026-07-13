/*
 * Entry: 00507341
 * Name: AI_UnitNotConstructing
 * Namespace: Global
 * Signature: void AI_UnitNotConstructing(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_UnitNotConstructing(tagUNIT *param_1)

{
  (param_1->ai).cc_constructing = 0;
  return;
}
