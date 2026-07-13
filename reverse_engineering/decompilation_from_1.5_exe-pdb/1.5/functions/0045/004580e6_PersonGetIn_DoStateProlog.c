/*
 * Entry: 004580e6
 * Name: PersonGetIn::DoStateProlog
 * Namespace: PersonGetIn
 * Signature: bool DoStateProlog(PersonGetIn * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PersonGetIn::DoStateProlog(PersonGetIn *this)

{
  bool bVar1;
  GameObject *pGVar2;
  
  pGVar2 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
  if ((pGVar2 != (GameObject *)0x0) && (pGVar2->aiProcess == (AiProcess *)0x0)) {
    bVar1 = GotoTask::DoStateProlog((GotoTask *)this);
    return bVar1;
  }
  UnitTask::CleanGoto((UnitTask *)this);
  *(undefined4 *)&this->field_0xc = 0xd;
  return false;
}
