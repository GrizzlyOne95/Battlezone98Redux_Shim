/*
 * Entry: 005151c8
 * Name: PREREQ_GetAllPrereqs
 * Namespace: Global
 * Signature: ushort * PREREQ_GetAllPrereqs(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort * __cdecl PREREQ_GetAllPrereqs(ushort param_1)

{
  return PREREQ_table[param_1].allprereqs;
}
