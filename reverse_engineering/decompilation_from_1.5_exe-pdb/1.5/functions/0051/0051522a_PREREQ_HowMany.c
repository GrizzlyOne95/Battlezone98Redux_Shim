/*
 * Entry: 0051522a
 * Name: PREREQ_HowMany
 * Namespace: Global
 * Signature: int PREREQ_HowMany(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PREREQ_HowMany(ushort param_1,char param_2)

{
  return PREREQ_table[param_1].howmany[param_2];
}
