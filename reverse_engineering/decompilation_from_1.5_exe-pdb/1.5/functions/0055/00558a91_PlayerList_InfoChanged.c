/*
 * Entry: 00558a91
 * Name: PlayerList::InfoChanged
 * Namespace: PlayerList
 * Signature: bool InfoChanged(PlayerList * this, Player * param_1, dp_playerId_t * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PlayerList::InfoChanged(PlayerList *this,Player *param_1,dp_playerId_t *param_2)

{
  byte bVar1;
  char *pcVar2;
  int iVar3;
  Player *pPVar4;
  bool bVar5;
  
  pcVar2 = param_2->name;
  pPVar4 = param_1;
  do {
    bVar1 = pPVar4->caName[0];
    bVar5 = bVar1 < (byte)*pcVar2;
    if (bVar1 != *pcVar2) {
LAB_00558abe:
      iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
      goto LAB_00558ac3;
    }
    if (bVar1 == 0) break;
    bVar1 = pPVar4->caName[1];
    bVar5 = bVar1 < (byte)pcVar2[1];
    if (bVar1 != pcVar2[1]) goto LAB_00558abe;
    pPVar4 = (Player *)(pPVar4->caName + 2);
    pcVar2 = pcVar2 + 2;
  } while (bVar1 != 0);
  iVar3 = 0;
LAB_00558ac3:
  if ((iVar3 == 0) && (param_1->id == (param_2->field0_0x0).id)) {
    bVar5 = false;
  }
  else {
    bVar5 = true;
  }
  return bVar5;
}
