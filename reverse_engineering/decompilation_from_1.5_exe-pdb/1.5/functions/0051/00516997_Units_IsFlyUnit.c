/*
 * Entry: 00516997
 * Name: Units_IsFlyUnit
 * Namespace: Global
 * Signature: int Units_IsFlyUnit(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Units_IsFlyUnit(tagUNIT *param_1)

{
  return (uint)(param_1->movemode == MM_FLY);
}
