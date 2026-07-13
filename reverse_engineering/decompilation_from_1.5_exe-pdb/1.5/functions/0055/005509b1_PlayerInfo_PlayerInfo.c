/*
 * Entry: 005509b1
 * Name: PlayerInfo::PlayerInfo
 * Namespace: PlayerInfo
 * Signature: PlayerInfo * PlayerInfo(PlayerInfo * this, char * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PlayerInfo * __thiscall
PlayerInfo::PlayerInfo(PlayerInfo *this,char *param_1,char *param_2,char *param_3)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  
  cVar2 = *param_1;
  while (cVar2 == ' ') {
    param_1 = param_1 + 1;
    cVar2 = *param_1;
  }
  cVar2 = *param_2;
  while (cVar2 == ' ') {
    param_2 = param_2 + 1;
    cVar2 = *param_2;
  }
  cVar2 = *param_3;
  while (cVar2 == ' ') {
    param_3 = param_3 + 1;
    cVar2 = *param_3;
  }
  pcVar7 = param_1;
  do {
    cVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  iVar8 = (int)pcVar7 - (int)(param_1 + 1);
  pcVar7 = param_2;
  do {
    cVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  iVar6 = (int)pcVar7 - (int)(param_2 + 1);
  pcVar7 = param_3;
  do {
    cVar2 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar2 != '\0');
  iVar3 = (int)pcVar7 - (int)(param_3 + 1);
  iVar4 = iVar3 + iVar6 + iVar8;
  uVar1 = iVar4 + 0x10;
  this->itype = 1;
  this->packt = (char *)0x0;
  this->email = (char *)0x0;
  this->url = (char *)0x0;
  this->description = (char *)0x0;
  if (iVar4 != 0) {
    puVar5 = operator_new__(uVar1);
    this->email = param_1;
    this->url = param_2;
    this->packt = (char *)puVar5;
    this->description = param_3;
    *puVar5 = uVar1;
    *(int *)(this->packt + 4) = iVar8;
    memcpy(this->packt + 8,this->email,iVar8);
    *(int *)(this->packt + iVar8 + 8) = iVar6;
    memcpy(this->packt + iVar8 + 0xc,this->url,iVar6);
    iVar6 = iVar8 + 0xc + iVar6;
    *(int *)(this->packt + iVar6) = iVar3;
    memcpy(this->packt + iVar6 + 4,this->description,iVar3);
  }
  return this;
}
