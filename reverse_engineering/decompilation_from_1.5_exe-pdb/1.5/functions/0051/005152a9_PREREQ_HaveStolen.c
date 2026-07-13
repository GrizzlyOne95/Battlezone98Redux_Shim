/*
 * Entry: 005152a9
 * Name: PREREQ_HaveStolen
 * Namespace: Global
 * Signature: uchar PREREQ_HaveStolen(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl PREREQ_HaveStolen(ushort param_1,char param_2)

{
  return PREREQ_table[param_1].havestolen[param_2];
}
