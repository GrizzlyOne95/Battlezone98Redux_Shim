/*
 * Entry: 0056ff9a
 * Name: AnimButton::movie_stop
 * Namespace: AnimButton
 * Signature: void movie_stop(AnimButton * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnimButton::movie_stop(AnimButton *this)

{
  MCIERROR MVar1;
  
  if (this->isMCIPlaying != 0) {
    MVar1 = mciSendCommandA((this->mci_movie).movieID,0x808,2,0);
    if (MVar1 != 0) {
      DEBUG_systemWarning("BattleZone (AnimButton) movie_stop error!");
    }
  }
  return;
}
