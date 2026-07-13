/*
 * Entry: 0050770a
 * Name: AI_SpecialForcesInit
 * Namespace: Global
 * Signature: void AI_SpecialForcesInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AI_SpecialForcesInit(void)

{
  if (special_forces_initialised != 0) {
    tlog(1,"AI_SpecialForcesInit called twice without matching Close\n");
  }
  C_Linked_List_Init(&special_forces_groups);
  special_forces_initialised = 1;
  return;
}
