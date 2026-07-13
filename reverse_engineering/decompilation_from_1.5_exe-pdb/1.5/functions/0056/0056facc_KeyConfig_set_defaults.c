/*
 * Entry: 0056facc
 * Name: KeyConfig::set_defaults
 * Namespace: KeyConfig
 * Signature: void set_defaults(KeyConfig * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall KeyConfig::set_defaults(KeyConfig *this)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  _KeyItem *p_Var4;
  char *pcVar5;
  int local_10;
  char *local_8;
  
  local_10 = 0;
  this->nKeyCount = 0x3e;
  local_8 = KeyboardDefaultList[0].cKeyFunction;
  pcVar3 = this->keyList[0].cKeyFunction;
  do {
    p_Var4 = (_KeyItem *)(local_8 + -0x100);
    iVar2 = -0x100 - (int)p_Var4;
    do {
      cVar1 = p_Var4->cKeyName[0];
      (pcVar3 + iVar2)[(int)p_Var4->cKeyName] = cVar1;
      p_Var4 = (_KeyItem *)(p_Var4->cKeyName + 1);
    } while (cVar1 != '\0');
    pcVar5 = local_8;
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)pcVar3 - (int)local_8] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    local_10 = local_10 + 1;
    local_8 = local_8 + 0x204;
    *(int *)(pcVar3 + 0x100) = *(int *)(pcVar3 + (0x6409ec - (int)this));
    pcVar3 = pcVar3 + 0x204;
  } while (local_10 < this->nKeyCount);
  return;
}
