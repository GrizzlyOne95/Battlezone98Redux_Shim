/*
 * Entry: 0040d306
 * Name: ArtilleryProcess::DoWait
 * Namespace: ArtilleryProcess
 * Signature: void DoWait(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::DoWait(ArtilleryProcess *this)

{
  int iVar1;
  char cVar2;
  float fVar3;
  
  iVar1 = ((int *)this->_padding_)[0x8a];
  cVar2 = (**(code **)(*(int *)this->_padding_ + 0x68))();
  if ((cVar2 != '\0') && (*(int *)(iVar1 + 0xe0) == 0)) {
    fVar3 = Get_Time();
    if ((float)this->_padding_ < fVar3) {
      (**(code **)(*(int *)this->_padding_ + 0x5c))();
    }
    *(undefined4 *)(iVar1 + 0xd4) = 0;
    *(undefined4 *)(iVar1 + 0xd8) = 0;
    *(undefined4 *)(iVar1 + 0xd0) = 0;
    *(undefined4 *)(iVar1 + 0xc4) = 0;
    *(undefined4 *)(iVar1 + 0xcc) = 0;
    return;
  }
  UnitProcess::DoWait((UnitProcess *)this);
  return;
}
