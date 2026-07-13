/*
 * Entry: 0051528e
 * Name: PREREQ_HavePlans
 * Namespace: Global
 * Signature: uchar PREREQ_HavePlans(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl PREREQ_HavePlans(ushort param_1,char param_2)

{
  return PREREQ_table[param_1].haveplans[param_2];
}
