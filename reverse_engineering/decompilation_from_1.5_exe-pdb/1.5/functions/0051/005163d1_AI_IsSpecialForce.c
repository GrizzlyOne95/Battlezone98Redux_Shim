/*
 * Entry: 005163d1
 * Name: AI_IsSpecialForce
 * Namespace: Global
 * Signature: int AI_IsSpecialForce(tagUNIT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_IsSpecialForce(tagUNIT *param_1)

{
  return (uint)(0 < *(int *)(param_1->id + 0xac));
}
