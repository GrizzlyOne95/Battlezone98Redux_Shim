/*
 * Entry: 004de815
 * Name: SetMyFlag
 * Namespace: Global
 * Signature: void SetMyFlag(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetMyFlag(void)

{
  char *pcVar1;
  char cVar2;
  ushort uVar3;
  NetPlayer *pNVar4;
  int iVar5;
  char *pcVar6;
  void *pvVar7;
  uint local_c;
  int local_8;
  
  uVar3 = Net::myPlayerID;
  pNVar4 = NetPlayer::Find(Net::myPlayerID);
  if (pNVar4 != (NetPlayer *)0x0) {
    pcVar1 = pNVar4->flagBuf;
    local_8 = 0x100;
    iVar5 = dpGetPlayerData(Net::dp,uVar3,0xd,pcVar1,&local_8,0);
    if ((iVar5 != 0) || (local_8 != 0x100)) {
      pcVar6 = Net::pcFlagName;
      do {
        cVar2 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar2 != '\0');
      if ((pcVar6 != Net::pcFlagName + 1) &&
         (pvVar7 = zixReadFile(Net::pcFlagName,(int *)&local_c), pvVar7 != (void *)0x0)) {
        if ((0x35 < local_c) && (*(short *)((int)pvVar7 + 0x1c) == 1)) {
          iVar5 = *(int *)((int)pvVar7 + 0x16) * *(int *)((int)pvVar7 + 0x12);
          memcpy(pcVar1,(int)pvVar7 + 0x3e,(int)(iVar5 + (iVar5 >> 0x1f & 7U)) >> 3);
          dpSetPlayerData(Net::dp,uVar3,0xd,pcVar1,0x100,0);
        }
        zixFree(pvVar7);
      }
    }
  }
  return;
}
