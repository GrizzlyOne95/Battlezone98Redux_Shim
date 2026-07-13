/*
 * Entry: 005726c6
 * Name: AnimButton::AnimButton
 * Namespace: AnimButton
 * Signature: AnimButton * AnimButton(AnimButton * this, HWND__ * param_1, char * param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimButton * __thiscall
AnimButton::AnimButton
          (AnimButton *this,HWND__ *param_1,char *param_2,int param_3,int param_4,int param_5,
          int param_6,int param_7,int param_8)

{
  char cVar1;
  int iVar2;
  
  this->hParentHwnd = param_1;
  iVar2 = 0x20 - (int)param_2;
  do {
    cVar1 = *param_2;
    param_2[(int)this + iVar2] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  this->nFrameCount = param_3;
  this->nCommand = param_8;
  (this->buttonRect).left = param_4;
  this->nEnd = param_3 + -1;
  (this->buttonRect).right = param_4 + param_6;
  (this->buttonRect).top = param_5;
  (this->buttonRect).bottom = param_5 + param_7;
  this->nButtonMode = 0;
  this->nStart = 0;
  this->nSpecialFrame = 0;
  this->nStatusCommand = 0;
  this->isMCIPlaying = 0;
  movie_open(this,this->movieName);
  movie_init(this,&this->buttonRect);
  return this;
}
