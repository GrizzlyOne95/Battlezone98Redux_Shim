/*
 * Entry: 004e0d91
 * Name: NetPlayer::FindUnusedTeam
 * Namespace: NetPlayer
 * Signature: int FindUnusedTeam(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl NetPlayer::FindUnusedTeam(void)

{
  int iVar1;
  
  iVar1 = 1;
  do {
    if (netPlayerByTeam[iVar1] == (NetPlayer *)0x0) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x10);
  return 0;
}
