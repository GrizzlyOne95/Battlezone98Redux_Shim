/*
 * Entry: 0056ff6a
 * Name: AnimButton::movie_close
 * Namespace: AnimButton
 * Signature: void movie_close(AnimButton * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnimButton::movie_close(AnimButton *this)

{
  MCIERROR MVar1;
  
  if (this->isMCIPlaying != 0) {
    MVar1 = mciSendCommandA((this->mci_movie).movieID,0x804,2,0);
    if (MVar1 != 0) {
      DEBUG_systemWarning("BattleZone (AnimButton) movie_close error!");
    }
    this->isMCIPlaying = 0;
  }
  return;
}
