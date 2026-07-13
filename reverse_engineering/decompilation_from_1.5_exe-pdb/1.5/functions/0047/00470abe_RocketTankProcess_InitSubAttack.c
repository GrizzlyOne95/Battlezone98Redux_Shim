/*
 * Entry: 00470abe
 * Name: RocketTankProcess::InitSubAttack
 * Namespace: RocketTankProcess
 * Signature: void InitSubAttack(RocketTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RocketTankProcess::InitSubAttack(RocketTankProcess *this)

{
  GameObject *pGVar1;
  WingmanBlastAttack *pWVar2;
  RocketTankAttack *this_00;
  
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  if (*(int *)&this->field_0x20 == 8) {
    pWVar2 = operator_new(0x138);
    if (pWVar2 != (WingmanBlastAttack *)0x0) {
      pWVar2 = WingmanBlastAttack::WingmanBlastAttack(pWVar2,*(Craft **)&this->field_0x2c,pGVar1);
      goto LAB_00470b08;
    }
  }
  else {
    this_00 = operator_new(0x138);
    if (this_00 != (RocketTankAttack *)0x0) {
      pWVar2 = (WingmanBlastAttack *)
               RocketTankAttack::RocketTankAttack(this_00,*(Craft **)&this->field_0x2c,pGVar1);
      goto LAB_00470b08;
    }
  }
  pWVar2 = (WingmanBlastAttack *)0x0;
LAB_00470b08:
  *(WingmanBlastAttack **)&this->field_0x30 = pWVar2;
  return;
}
