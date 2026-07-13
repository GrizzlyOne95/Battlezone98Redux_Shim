/*
 * Entry: 00515446
 * Name: PREREQ_MapPrereqIdToBuildingId
 * Namespace: Global
 * Signature: int PREREQ_MapPrereqIdToBuildingId(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PREREQ_MapPrereqIdToBuildingId(int param_1)

{
  return *(uint *)((int)PREREQ_table[param_1].data + 0x24) >> 10 & 0xff;
}
