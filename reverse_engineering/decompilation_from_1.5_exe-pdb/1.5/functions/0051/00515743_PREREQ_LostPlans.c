/*
 * Entry: 00515743
 * Name: PREREQ_LostPlans
 * Namespace: Global
 * Signature: void PREREQ_LostPlans(ushort param_1, char param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PREREQ_LostPlans(ushort param_1,char param_2)

{
  if (PREREQ_table[param_1].haveplans[param_2] == '\x01') {
    PREREQ_table[param_1].haveplans[param_2] = '\0';
    PREREQ_table[param_1].havestolen[param_2] = '\0';
    PREREQ_Update(param_2);
  }
  return;
}
