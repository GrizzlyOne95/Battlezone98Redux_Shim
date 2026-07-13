/*
 * Entry: 0056fc32
 * Name: KeyConfig::set_key
 * Namespace: KeyConfig
 * Signature: int set_key(KeyConfig * this, char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall KeyConfig::set_key(KeyConfig *this,char *param_1,char *param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  byte *pbVar4;
  _KeyItem *p_Var5;
  char *pcVar6;
  _KeyItem *p_Var7;
  int iVar8;
  char *pcVar9;
  bool bVar10;
  
  iVar8 = 0;
  if (0 < this->nKeyCount) {
    p_Var5 = this->keyList;
    pbVar4 = (byte *)param_2;
    p_Var7 = p_Var5;
LAB_0056fc44:
    do {
      bVar1 = *pbVar4;
      bVar10 = bVar1 < (byte)p_Var5->cKeyName[0];
      if (bVar1 == p_Var5->cKeyName[0]) {
        if (bVar1 != 0) {
          bVar1 = pbVar4[1];
          bVar10 = bVar1 < (byte)p_Var5->cKeyName[1];
          if (bVar1 != p_Var5->cKeyName[1]) goto LAB_0056fc62;
          p_Var5 = (_KeyItem *)(p_Var5->cKeyName + 2);
          pbVar4 = pbVar4 + 2;
          if (bVar1 != 0) goto LAB_0056fc44;
        }
        iVar3 = 0;
      }
      else {
LAB_0056fc62:
        iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
      }
      if (iVar3 == 0) {
        return 0;
      }
      iVar8 = iVar8 + 1;
      p_Var5 = p_Var7 + 1;
      pbVar4 = (byte *)param_2;
      p_Var7 = p_Var5;
    } while (iVar8 < this->nKeyCount);
  }
  iVar8 = 0;
  if (0 < this->nKeyCount) {
    pcVar6 = this->keyList[0].cKeyFunction;
    pbVar4 = (byte *)param_1;
    pcVar9 = pcVar6;
LAB_0056fc88:
    do {
      bVar1 = *pbVar4;
      bVar10 = bVar1 < (byte)*pcVar6;
      if (bVar1 == *pcVar6) {
        if (bVar1 != 0) {
          bVar1 = pbVar4[1];
          bVar10 = bVar1 < (byte)pcVar6[1];
          if (bVar1 != pcVar6[1]) goto LAB_0056fca6;
          pcVar6 = pcVar6 + 2;
          pbVar4 = pbVar4 + 2;
          if (bVar1 != 0) goto LAB_0056fc88;
        }
        iVar3 = 0;
      }
      else {
LAB_0056fca6:
        iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
      }
      if (iVar3 == 0) {
        if (this->keyList[iVar8].nReserved != 0) {
          return 0;
        }
        iVar8 = (iVar8 * 0x204 + 4) - (int)param_2;
        do {
          cVar2 = *param_2;
          param_2[(int)this + iVar8] = cVar2;
          param_2 = param_2 + 1;
        } while (cVar2 != '\0');
        return 1;
      }
      iVar8 = iVar8 + 1;
      pcVar6 = pcVar9 + 0x204;
      pbVar4 = (byte *)param_1;
      pcVar9 = pcVar6;
    } while (iVar8 < this->nKeyCount);
  }
  return 0;
}
