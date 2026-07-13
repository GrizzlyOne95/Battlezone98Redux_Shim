/*
 * Entry: 00571a75
 * Name: AnimButton::movie_check
 * Namespace: AnimButton
 * Signature: void movie_check(AnimButton * this, uint param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnimButton::movie_check(AnimButton *this,uint param_1,long param_2)

{
  int iVar1;
  
  if (this->isMCIPlaying == 0) {
    return;
  }
  if (param_1 != 1) {
    return;
  }
  if ((param_2 & 0xffffU) != (this->mci_movie).movieID) {
    return;
  }
  iVar1 = this->nStatusCommand;
  if (iVar1 == 0) {
    this->nStatusCommand = this->nCommand;
    movie_stop(this);
    movie_seek(this,this->nEnd);
    return;
  }
  if (iVar1 == 1) {
LAB_00571aa7:
    movie_stop(this);
  }
  else {
    if (iVar1 == 2) {
      movie_play(this,this->nStart,this->nEnd);
    }
    else if (iVar1 != 3) goto LAB_00571aa7;
    this->nStart = this->nSpecialFrame;
    movie_play(this,this->nSpecialFrame,this->nEnd);
    this->nStatusCommand = 2;
  }
  return;
}
