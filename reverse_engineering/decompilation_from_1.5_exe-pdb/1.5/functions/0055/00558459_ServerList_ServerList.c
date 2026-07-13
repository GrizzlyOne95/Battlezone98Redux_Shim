/*
 * Entry: 00558459
 * Name: ServerList::ServerList
 * Namespace: ServerList
 * Signature: ServerList * ServerList(ServerList * this, HWND__ * param_1, dp_s * param_2, HWND__ * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ServerList * __thiscall
ServerList::ServerList(ServerList *this,HWND__ *param_1,dp_s *param_2,HWND__ *param_3)

{
  LRESULT LVar1;
  UINT_PTR UVar2;
  
  this->_padding_ = (int)&_vftable_;
  std::vector<Server_*,std::allocator<Server_*>_>::vector<Server_*,std::allocator<Server_*>_>
            (&this->serverV);
  this->dp = param_2;
  this->bStop = false;
  this->pcMs[0] = '\0';
  this->hParent = param_3;
  (this->rList).left = 0x14e;
  (this->rList).right = 0x23b;
  (this->rList).top = 0xc9;
  (this->rList).bottom = 0x1ab;
  this->hList = param_1;
  this->enumDelay = 2000;
  this->fastEnums = 5;
  LVar1 = SendMessageA((HWND)param_1,0x184,0,0);
  this->l = LVar1;
  this->bInEnumServers = false;
  this->bServerSelected = false;
  this->bTryGameServerAgain = false;
  UVar2 = SetTimer((HWND)param_3,1,100,(TIMERPROC)0x0);
  this->iTimerID = UVar2;
  Redraw(this);
  return this;
}
