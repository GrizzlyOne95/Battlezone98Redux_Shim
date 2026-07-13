/*
 * Entry: 005151b2
 * Name: PREREQ_GetPrereqs
 * Namespace: Global
 * Signature: ushort * PREREQ_GetPrereqs(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort * __cdecl PREREQ_GetPrereqs(ushort param_1)

{
  return PREREQ_table[param_1].prereqs;
}
