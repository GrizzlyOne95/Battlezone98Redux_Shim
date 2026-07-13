/*
 * Entry: 0055c22d
 * Name: SyncGamePlayerList::InfoChanged
 * Namespace: SyncGamePlayerList
 * Signature: bool InfoChanged(SyncGamePlayerList * this, Player * param_1, dp_playerId_t * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
SyncGamePlayerList::InfoChanged(SyncGamePlayerList *this,Player *param_1,dp_playerId_t *param_2)

{
  byte bVar1;
  char *pcVar2;
  int iVar3;
  Player *pPVar4;
  uint uVar5;
  uchar *puVar6;
  bool bVar7;
  
  pcVar2 = param_2->name;
  pPVar4 = param_1;
  do {
    bVar1 = pPVar4->caName[0];
    bVar7 = bVar1 < (byte)*pcVar2;
    if (bVar1 != *pcVar2) {
LAB_0055c25f:
      iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
      goto LAB_0055c264;
    }
    if (bVar1 == 0) break;
    bVar1 = pPVar4->caName[1];
    bVar7 = bVar1 < (byte)pcVar2[1];
    if (bVar1 != pcVar2[1]) goto LAB_0055c25f;
    pPVar4 = (Player *)(pPVar4->caName + 2);
    pcVar2 = pcVar2 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_0055c264:
  if (iVar3 == 0) {
    uVar5 = (uint)param_2->bloblen;
    bVar7 = true;
    pcVar2 = param_1->blob;
    puVar6 = param_2->blob;
    do {
      if (uVar5 == 0) break;
      uVar5 = uVar5 - 1;
      bVar7 = *pcVar2 == *puVar6;
      pcVar2 = pcVar2 + 1;
      puVar6 = puVar6 + 1;
    } while (bVar7);
    if (bVar7) {
      return false;
    }
  }
  SendMessageA((HWND)this->hLaunchButton,0xc,0,0x5eff18);
  return true;
}
