/*
 * Entry: 00571917
 * Name: AnimButton::movie_init
 * Namespace: AnimButton
 * Signature: int movie_init(AnimButton * this, tagRECT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AnimButton::movie_init(AnimButton *this,tagRECT *param_1)

{
  tagRECT *ptVar1;
  MCIERROR MVar2;
  DWORD_PTR dwParam1;
  undefined4 local_34;
  long local_30;
  long lStack_2c;
  long lStack_28;
  long lStack_24;
  undefined4 local_20;
  HWND__ *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  HWND__ *local_10;
  int local_c;
  int local_8;
  
  local_1c = this->hParentHwnd;
  (this->mci_movie).mode = 0;
  local_20 = 0;
  local_14 = 0;
  local_18 = 0;
  MVar2 = mciSendCommandA((this->mci_movie).movieID,0x841,0x10000,(DWORD_PTR)&local_20);
  if (MVar2 == 0) {
    ptVar1 = &(this->mci_movie).rect;
    local_34 = 0;
    if (param_1 == (tagRECT *)0x0) {
      ptVar1->left = 0;
      (this->mci_movie).rect.top = 0;
      (this->mci_movie).rect.right = 0x27f;
      (this->mci_movie).rect.bottom = 0x1df;
      dwParam1 = 0x40000;
    }
    else {
      ptVar1->left = param_1->left;
      (this->mci_movie).rect.top = param_1->top;
      (this->mci_movie).rect.right = param_1->right - param_1->left;
      (this->mci_movie).rect.bottom = param_1->bottom - param_1->top;
      dwParam1 = 0x50000;
    }
    local_30 = ptVar1->left;
    lStack_2c = (this->mci_movie).rect.top;
    lStack_28 = (this->mci_movie).rect.right;
    lStack_24 = (this->mci_movie).rect.bottom;
    MVar2 = mciSendCommandA((this->mci_movie).movieID,0x842,dwParam1,(DWORD_PTR)&local_34);
    if (MVar2 == 0) {
      if (this->nCommand != 4) {
        local_10 = this->hParentHwnd;
        local_c = this->nStart;
        local_8 = this->nEnd;
        MVar2 = mciSendCommandA((this->mci_movie).movieID,0x806,0xd,(DWORD_PTR)&local_10);
        if (MVar2 != 0) {
          GetMCIError(MVar2);
          goto LAB_00571954;
        }
      }
      this->isMCIPlaying = 1;
      return 1;
    }
  }
LAB_00571954:
  DEBUG_systemWarning("BattleZone (AnimButton) movie_init error!");
  return 0;
}
