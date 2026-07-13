/*
 * Entry: 00550aa5
 * Name: PlayerInfo::~PlayerInfo
 * Namespace: PlayerInfo
 * Signature: void ~PlayerInfo(PlayerInfo * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerInfo::~PlayerInfo(PlayerInfo *this)

{
  char *pcVar1;
  
  if (this->itype == 2) {
    if (this->email != (char *)0x0) {
      operator_delete__(this->email);
    }
    if (this->url != (char *)0x0) {
      operator_delete__(this->url);
    }
    pcVar1 = this->description;
  }
  else {
    if (this->itype != 1) {
      return;
    }
    pcVar1 = this->packt;
  }
  if (pcVar1 != (char *)0x0) {
    operator_delete__(pcVar1);
  }
  return;
}
