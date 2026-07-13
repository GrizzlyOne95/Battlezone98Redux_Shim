/*
 * Entry: 0055c29d
 * Name: SyncGamePlayerList::FormatItem
 * Namespace: SyncGamePlayerList
 * Signature: void FormatItem(SyncGamePlayerList * this, char * param_1, Player * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
SyncGamePlayerList::FormatItem(SyncGamePlayerList *this,char *param_1,Player *param_2)

{
  int iVar1;
  int iVar2;
  
  if (Net::myPlayerID == param_2->id) {
    sprintf(param_1,"%s %d %s",param_2,(int)param_2->blob[0],param_2->blob + 1);
  }
  else {
    iVar2 = param_2->loss_pct;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
    iVar1 = 9999;
    if (param_2->avg_ms < 10000) {
      iVar1 = param_2->avg_ms;
    }
    sprintf(param_1,"%s %d %s %ld %d",param_2,(int)param_2->blob[0],param_2->blob + 1,iVar1,iVar2);
  }
  return;
}
