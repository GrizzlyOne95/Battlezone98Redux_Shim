/*
 * Entry: 004b1be9
 * Name: Team::Cleanup
 * Namespace: Team
 * Signature: void Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Team::Cleanup(void)

{
  Team **ppTVar1;
  
  ppTVar1 = teamList;
  do {
    operator_delete(*ppTVar1);
    *ppTVar1 = (Team *)0x0;
    ppTVar1 = ppTVar1 + 1;
  } while ((int)ppTVar1 < 0xb0ce88);
  return;
}
