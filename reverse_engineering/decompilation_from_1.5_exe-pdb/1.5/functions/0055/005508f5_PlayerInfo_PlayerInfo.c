/*
 * Entry: 005508f5
 * Name: PlayerInfo::PlayerInfo
 * Namespace: PlayerInfo
 * Signature: PlayerInfo * PlayerInfo(PlayerInfo * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PlayerInfo * __thiscall PlayerInfo::PlayerInfo(PlayerInfo *this,char *param_1)

{
  size_t sVar1;
  char *pcVar2;
  int iVar3;
  
  this->itype = 2;
  iVar3 = *(int *)param_1;
  this->packt = (char *)0x0;
  this->email = (char *)0x0;
  this->url = (char *)0x0;
  this->description = (char *)0x0;
  if (iVar3 != 0) {
    this->packt = param_1;
    sVar1 = *(size_t *)(param_1 + 4);
    iVar3 = 8;
    if (sVar1 != 0) {
      pcVar2 = operator_new__(sVar1 + 1);
      this->email = pcVar2;
      strncpy(pcVar2,this->packt + 8,sVar1);
      this->email[sVar1] = '\0';
      iVar3 = sVar1 + 8;
    }
    sVar1 = *(size_t *)(this->packt + iVar3);
    iVar3 = iVar3 + 4;
    if (sVar1 != 0) {
      pcVar2 = operator_new__(sVar1 + 1);
      this->url = pcVar2;
      strncpy(pcVar2,this->packt + iVar3,sVar1);
      this->url[sVar1] = '\0';
      iVar3 = iVar3 + sVar1;
    }
    sVar1 = *(size_t *)(this->packt + iVar3);
    if (sVar1 != 0) {
      pcVar2 = operator_new__(sVar1 + 1);
      this->description = pcVar2;
      strncpy(pcVar2,this->packt + iVar3 + 4,sVar1);
      this->description[sVar1] = '\0';
    }
  }
  return this;
}
