/*
 * Entry: 005151de
 * Name: PREREQ_GetMakers
 * Namespace: Global
 * Signature: ushort * PREREQ_GetMakers(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort * __cdecl PREREQ_GetMakers(ushort param_1)

{
  return PREREQ_table[param_1].makers;
}
