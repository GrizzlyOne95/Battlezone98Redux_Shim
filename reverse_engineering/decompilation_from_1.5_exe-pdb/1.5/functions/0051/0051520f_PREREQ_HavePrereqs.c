/*
 * Entry: 0051520f
 * Name: PREREQ_HavePrereqs
 * Namespace: Global
 * Signature: uchar PREREQ_HavePrereqs(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl PREREQ_HavePrereqs(ushort param_1,char param_2)

{
  return PREREQ_table[param_1].haveprereqs[param_2];
}
