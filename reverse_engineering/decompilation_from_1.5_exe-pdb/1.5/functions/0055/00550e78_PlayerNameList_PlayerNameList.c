/*
 * Entry: 00550e78
 * Name: PlayerNameList::PlayerNameList
 * Namespace: PlayerNameList
 * Signature: PlayerNameList * PlayerNameList(PlayerNameList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PlayerNameList * __thiscall PlayerNameList::PlayerNameList(PlayerNameList *this)

{
  this->hwnd = (HWND__ *)0x0;
  this->hwndMail = (HWND__ *)0x0;
  this->hwndURL = (HWND__ *)0x0;
  this->hwndDescription = (HWND__ *)0x0;
  this->count = 0;
  this->name = (char **)0x0;
  this->email = (char **)0x0;
  this->url = (char **)0x0;
  this->description = (char **)0x0;
  this->flag = (char **)0x0;
  this->edit = false;
  this->flagList = (FlagList *)0x0;
  return this;
}
