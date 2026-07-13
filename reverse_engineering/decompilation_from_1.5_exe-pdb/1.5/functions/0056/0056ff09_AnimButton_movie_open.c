/*
 * Entry: 0056ff09
 * Name: AnimButton::movie_open
 * Namespace: AnimButton
 * Signature: int movie_open(AnimButton * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AnimButton::movie_open(AnimButton *this,char *param_1)

{
  MCIERROR MVar1;
  undefined1 local_20 [4];
  uint local_1c;
  char *local_18;
  char *local_14;
  undefined4 local_10;
  undefined4 local_c;
  HWND__ *local_8;
  
  local_10 = 0;
  local_8 = this->hParentHwnd;
  local_18 = "AVIVideo";
  local_14 = param_1;
  local_c = 0x48000000;
  MVar1 = mciSendCommandA(0,0x803,0x132200,(DWORD_PTR)local_20);
  if (MVar1 == 0) {
    (this->mci_movie).movieID = local_1c;
  }
  else {
    DEBUG_systemWarning("BattleZone (AnimButton) movie_open error %s!");
  }
  return (uint)(MVar1 == 0);
}
