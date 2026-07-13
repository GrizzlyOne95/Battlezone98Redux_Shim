/*
 * Entry: 00556605
 * Name: PlayerNameList::Load
 * Namespace: PlayerNameList
 * Signature: void Load(PlayerNameList * this, HWND__ * param_1, HWND__ * param_2, HWND__ * param_3, HWND__ * param_4, FlagList * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PlayerNameList::Load
          (PlayerNameList *this,HWND__ *param_1,HWND__ *param_2,HWND__ *param_3,HWND__ *param_4,
          FlagList *param_5)

{
  this->flagList = param_5;
  this->hwnd = param_1;
  this->hwndMail = param_2;
  this->hwndURL = param_3;
  this->hwndDescription = param_4;
  Load(this,"netnam2.txt");
  return;
}
