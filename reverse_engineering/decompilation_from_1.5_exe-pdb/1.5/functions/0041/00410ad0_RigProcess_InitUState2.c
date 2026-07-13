/*
 * Entry: 00410ad0
 * Name: RigProcess::InitUState2
 * Namespace: RigProcess
 * Signature: void InitUState2(RigProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RigProcess::InitUState2(RigProcess *this)

{
  GameObject *pGVar1;
  UnBuild *pUVar2;
  
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  pUVar2 = operator_new(0x164);
  if (pUVar2 == (UnBuild *)0x0) {
    pUVar2 = (UnBuild *)0x0;
  }
  else {
    pUVar2 = UnBuild::UnBuild(pUVar2,*(Craft **)&this->field_0x2c,pGVar1);
  }
  *(UnBuild **)&this->field_0x30 = pUVar2;
  return;
}
