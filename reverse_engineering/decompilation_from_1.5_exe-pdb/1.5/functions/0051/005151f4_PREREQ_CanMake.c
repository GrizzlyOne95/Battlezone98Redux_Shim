/*
 * Entry: 005151f4
 * Name: PREREQ_CanMake
 * Namespace: Global
 * Signature: uchar PREREQ_CanMake(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl PREREQ_CanMake(ushort param_1,char param_2)

{
  return PREREQ_table[param_1].canmake[param_2];
}
