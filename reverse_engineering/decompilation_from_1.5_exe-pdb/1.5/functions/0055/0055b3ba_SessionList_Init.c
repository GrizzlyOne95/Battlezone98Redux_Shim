/*
 * Entry: 0055b3ba
 * Name: SessionList::Init
 * Namespace: SessionList
 * Signature: void Init(SessionList * this, HWND__ * param_1, dp_s * param_2, HWND__ * param_3, HWND__ * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
SessionList::Init(SessionList *this,HWND__ *param_1,dp_s *param_2,HWND__ *param_3,HWND__ *param_4)

{
  this->dp = param_2;
  this->hList = param_1;
  this->hOutput = param_3;
  this->hParentHwnd = param_4;
  Reset(this);
  return;
}
