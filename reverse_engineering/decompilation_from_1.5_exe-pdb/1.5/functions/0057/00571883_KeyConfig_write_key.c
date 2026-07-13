/*
 * Entry: 00571883
 * Name: KeyConfig::write_key
 * Namespace: KeyConfig
 * Signature: int write_key(KeyConfig * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall KeyConfig::write_key(KeyConfig *this,char *param_1)

{
  int iVar1;
  int iVar2;
  _KeyItem *p_Var3;
  char *pcVar4;
  bool bVar5;
  
  iVar1 = get_key(this,param_1);
  if (-1 < iVar1) {
    iVar2 = 5;
    bVar5 = true;
    p_Var3 = this->keyList + iVar1;
    pcVar4 = "NULL";
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar5 = p_Var3->cKeyName[0] == *pcVar4;
      p_Var3 = (_KeyItem *)(p_Var3->cKeyName + 1);
      pcVar4 = pcVar4 + 1;
    } while (bVar5);
    if (!bVar5) {
      write_input_map_key(param_1,this->keyList[iVar1].cKeyName);
      return 1;
    }
  }
  return 0;
}
