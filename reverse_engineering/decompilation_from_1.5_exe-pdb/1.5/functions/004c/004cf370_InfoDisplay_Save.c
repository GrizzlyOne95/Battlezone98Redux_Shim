/*
 * Entry: 004cf370
 * Name: InfoDisplay::Save
 * Namespace: InfoDisplay
 * Signature: bool Save(InfoDisplay * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall InfoDisplay::Save(InfoDisplay *this,_iobuf *param_1)

{
  int *piVar1;
  bool bVar2;
  MessageInfo *pMVar3;
  int local_8;
  
  piVar1 = &this->objectiveCount;
  bVar2 = ::out(param_1,piVar1,4,"objectiveCount");
  local_8 = 0;
  if (0 < *piVar1) {
    pMVar3 = this->objectiveMessage;
    do {
      if (((bVar2 == false) || (bVar2 = ::out(param_1,pMVar3->name,0xe,"name"), !bVar2)) ||
         (bVar2 = ::out(param_1,&pMVar3->color,4,"color"), !bVar2)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      local_8 = local_8 + 1;
      pMVar3 = pMVar3 + 1;
    } while (local_8 < *piVar1);
  }
  if ((bVar2 == false) || (bVar2 = ::out(param_1,&this->objectiveLast,4,"objectiveLast"), !bVar2)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  return bVar2;
}
