/*
 * Entry: 0056fbae
 * Name: KeyConfig::get_key
 * Namespace: KeyConfig
 * Signature: int get_key(KeyConfig * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Type propagation algorithm not settling */

int __thiscall KeyConfig::get_key(KeyConfig *this,char *param_1)

{
  byte bVar1;
  char *pcVar2;
  byte *pbVar3;
  int iVar4;
  char *pcVar5;
  _KeyItem *p_Var6;
  bool bVar7;
  int local_8;
  
  local_8 = 0;
  if (0 < this->nKeyCount) {
    pcVar5 = this->keyList[0].cKeyFunction;
    pbVar3 = (byte *)param_1;
    pcVar2 = pcVar5;
LAB_0056fbca:
    do {
      bVar1 = *pbVar3;
      bVar7 = bVar1 < (byte)*pcVar5;
      if (bVar1 == *pcVar5) {
        if (bVar1 != 0) {
          bVar1 = pbVar3[1];
          bVar7 = bVar1 < (byte)pcVar5[1];
          if (bVar1 != pcVar5[1]) goto LAB_0056fbe8;
          pcVar5 = pcVar5 + 2;
          pbVar3 = pbVar3 + 2;
          if (bVar1 != 0) goto LAB_0056fbca;
        }
        iVar4 = 0;
      }
      else {
LAB_0056fbe8:
        iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
      }
      if (iVar4 == 0) {
        iVar4 = 5;
        bVar7 = true;
        p_Var6 = this->keyList + local_8;
        pcVar5 = "NULL";
        goto code_r0x0056fc2c;
      }
      local_8 = local_8 + 1;
      pcVar5 = pcVar2 + 0x204;
      pbVar3 = (byte *)param_1;
      pcVar2 = pcVar5;
    } while (local_8 < this->nKeyCount);
  }
  DEBUG_systemError("BattleZone (input_config) get_key Error!");
  return -1;
  while( true ) {
    iVar4 = iVar4 + -1;
    bVar7 = p_Var6->cKeyName[0] == *pcVar5;
    p_Var6 = (_KeyItem *)(p_Var6->cKeyName + 1);
    pcVar5 = pcVar5 + 1;
    if (!bVar7) break;
code_r0x0056fc2c:
    if (iVar4 == 0) break;
  }
  if (bVar7) {
    return -1;
  }
  return local_8;
}
