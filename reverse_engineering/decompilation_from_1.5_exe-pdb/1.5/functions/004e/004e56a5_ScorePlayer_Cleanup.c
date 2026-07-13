/*
 * Entry: 004e56a5
 * Name: ScorePlayer::Cleanup
 * Namespace: ScorePlayer
 * Signature: void Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ScorePlayer::Cleanup(void)

{
  uint uVar1;
  ScorePlayer **ppSVar2;
  
  uVar1 = (int)playerV._Mylast - (int)playerV._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    ppSVar2 = std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::back(&playerV);
    operator_delete(*ppSVar2);
    std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::pop_back(&playerV);
    uVar1 = (int)playerV._Mylast - (int)playerV._Myfirst;
  }
  return;
}
