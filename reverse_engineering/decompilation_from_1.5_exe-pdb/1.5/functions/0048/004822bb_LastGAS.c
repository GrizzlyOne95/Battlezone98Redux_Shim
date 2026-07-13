/*
 * Entry: 004822bb
 * Name: LastGAS
 * Namespace: Global
 * Signature: int LastGAS(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LastGAS(void)

{
  int iVar1;
  GAS_MASTER *unaff_EDI;
  GAS_MASTER *pGVar2;
  
  PurgeGASLists();
  Trace("AudioSys - minFreeCopies(%d)\n");
  StopMusic();
  PlayerDone();
  if (GM == (GAS_MASTER *)0x0) {
    return 0;
  }
  StopGAS(unaff_EDI);
  UsedMemory = 0;
  GM = (GAS_MASTER *)0x0;
  pGVar2 = &GAS_Master;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    pGVar2->DSHandle = (IDirectSound *)0x0;
    pGVar2 = (GAS_MASTER *)&pGVar2->primaryBuffer;
  }
  return 1;
}
