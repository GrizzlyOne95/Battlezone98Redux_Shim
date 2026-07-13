/*
 * Entry: 00415d0d
 * Name: Inst03Mission::Start
 * Namespace: Inst03Mission
 * Signature: void Start(Inst03Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst03Mission::Start(Inst03Mission *this)

{
  PathSpawn *pPVar1;
  
  LuaMission::Start((LuaMission *)this);
  if (this->pathSpawn == (PathSpawn *)0x0) {
    pPVar1 = operator_new(0x114c);
    if (pPVar1 == (PathSpawn *)0x0) {
      pPVar1 = (PathSpawn *)0x0;
    }
    else {
      pPVar1 = PathSpawn::PathSpawn(pPVar1,(AiMission *)this);
    }
    this->pathSpawn = pPVar1;
  }
  return;
}
