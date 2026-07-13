/*
 * Entry: 0055613f
 * Name: PlayerNameList::Add
 * Namespace: PlayerNameList
 * Signature: void Add(PlayerNameList * this, char * param_1, char * param_2, char * param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PlayerNameList::Add(PlayerNameList *this,char *param_1,char *param_2,char *param_3,char *param_4)

{
  char *pcVar1;
  
  if (this->flagList == (FlagList *)0x0) {
    pcVar1 = "";
  }
  else {
    pcVar1 = FlagList::GetSelection(this->flagList);
  }
  Add(this,param_1,param_2,param_3,param_4,pcVar1);
  return;
}
