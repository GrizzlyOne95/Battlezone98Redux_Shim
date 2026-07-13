/*
 * Entry: 00571a21
 * Name: AnimButton::movie_play
 * Namespace: AnimButton
 * Signature: int movie_play(AnimButton * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AnimButton::movie_play(AnimButton *this,int param_1,int param_2)

{
  MCIERROR MVar1;
  HWND__ *local_10;
  int local_c;
  int local_8;
  
  local_10 = this->hParentHwnd;
  local_c = param_1;
  local_8 = param_2;
  MVar1 = mciSendCommandA((this->mci_movie).movieID,0x806,0xd,(DWORD_PTR)&local_10);
  if (MVar1 == 0) {
    this->isMCIPlaying = 1;
  }
  else {
    GetMCIError(MVar1);
    DEBUG_systemWarning("BattleZone (AnimButton) movie_play error!");
  }
  return (uint)(MVar1 == 0);
}
