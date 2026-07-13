/*
 * Entry: 00572763
 * Name: AnimButton::SetButtonMode
 * Namespace: AnimButton
 * Signature: int SetButtonMode(AnimButton * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall AnimButton::SetButtonMode(AnimButton *this,int param_1)

{
  if (this->nStatusCommand != 0) {
    if (param_1 == 0) {
      if (this->nButtonMode != 0) {
        movie_stop(this);
        movie_seek(this,this->nStart);
        this->nButtonMode = 0;
        return 1;
      }
    }
    else if ((param_1 == 1) && (this->nButtonMode != 1)) {
      movie_play(this,this->nStart,this->nEnd);
      this->nButtonMode = 1;
      return 1;
    }
  }
  return 0;
}
