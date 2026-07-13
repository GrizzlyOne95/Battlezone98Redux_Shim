/*
 * Entry: 0056ffc2
 * Name: AnimButton::movie_seek
 * Namespace: AnimButton
 * Signature: void movie_seek(AnimButton * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnimButton::movie_seek(AnimButton *this,int param_1)

{
  MCIERROR MVar1;
  undefined4 local_c;
  int local_8;
  
  local_c = 0;
  local_8 = param_1;
  MVar1 = mciSendCommandA((this->mci_movie).movieID,0x807,8,(DWORD_PTR)&local_c);
  if (MVar1 != 0) {
    DEBUG_systemWarning("BattleZone (AnimButton) movie_seek error!");
  }
  return;
}
