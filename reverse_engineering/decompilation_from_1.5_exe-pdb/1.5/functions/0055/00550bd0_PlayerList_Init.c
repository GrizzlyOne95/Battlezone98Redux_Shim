/*
 * Entry: 00550bd0
 * Name: PlayerList::Init
 * Namespace: PlayerList
 * Signature: void Init(PlayerList * this, HWND__ * param_1, dp_s * param_2, HWND__ * param_3, Chat * param_4, _func___cdecl_void_short_long_int * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PlayerList::Init(PlayerList *this,HWND__ *param_1,dp_s *param_2,HWND__ *param_3,Chat *param_4,
                _func___cdecl_void_short_long_int *param_5)

{
  this->dp = param_2;
  this->hList = param_1;
  this->hOutput = param_3;
  this->chat = param_4;
  this->PingHandler = param_5;
  this->bInEnum = false;
  (**(code **)(this->_padding_ + 0xc))();
  return;
}
