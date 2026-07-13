/*
 * Entry: 0056fb49
 * Name: KeyConfig::clear_key
 * Namespace: KeyConfig
 * Signature: int clear_key(KeyConfig * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall KeyConfig::clear_key(KeyConfig *this,char *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  bool bVar7;
  
  iVar5 = 0;
  if (0 < this->nKeyCount) {
    pcVar4 = this->keyList[0].cKeyFunction;
    pbVar2 = (byte *)param_1;
    pcVar6 = pcVar4;
LAB_0056fb5e:
    do {
      bVar1 = *pbVar2;
      bVar7 = bVar1 < (byte)*pcVar4;
      if (bVar1 == *pcVar4) {
        if (bVar1 != 0) {
          bVar1 = pbVar2[1];
          bVar7 = bVar1 < (byte)pcVar4[1];
          if (bVar1 != pcVar4[1]) goto LAB_0056fb7c;
          pcVar4 = pcVar4 + 2;
          pbVar2 = pbVar2 + 2;
          if (bVar1 != 0) goto LAB_0056fb5e;
        }
        iVar3 = 0;
      }
      else {
LAB_0056fb7c:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
      }
      if (iVar3 == 0) {
        builtin_strncpy(this->keyList[iVar5].cKeyName,"NULL",5);
        return 1;
      }
      iVar5 = iVar5 + 1;
      pcVar4 = pcVar6 + 0x204;
      pbVar2 = (byte *)param_1;
      pcVar6 = pcVar4;
    } while (iVar5 < this->nKeyCount);
  }
  return 0;
}
