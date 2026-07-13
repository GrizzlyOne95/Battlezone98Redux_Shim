/*
 * Entry: 00558adc
 * Name: PlayerList::FormatItem
 * Namespace: PlayerList
 * Signature: void FormatItem(PlayerList * this, char * param_1, Player * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::FormatItem(PlayerList *this,char *param_1,Player *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2->id == Net::myPlayerID) {
    sprintf(param_1,"%s",param_2);
  }
  else {
    iVar2 = param_2->loss_pct;
    iVar1 = param_2->avg_ms;
    if (iVar1 < 1) {
      if (iVar2 < 0) {
        iVar2 = 0;
      }
      sprintf(param_1,"%s ? %d",param_2,iVar2);
    }
    else {
      if (iVar2 < 0) {
        iVar2 = 0;
      }
      iVar3 = 9999;
      if (iVar1 < 10000) {
        iVar3 = iVar1;
      }
      sprintf(param_1,"%s %ld %d",param_2,iVar3,iVar2);
    }
  }
  return;
}
