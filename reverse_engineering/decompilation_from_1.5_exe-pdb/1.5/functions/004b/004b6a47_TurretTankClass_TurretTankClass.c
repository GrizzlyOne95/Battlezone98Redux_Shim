/*
 * Entry: 004b6a47
 * Name: TurretTankClass::TurretTankClass
 * Namespace: TurretTankClass
 * Signature: TurretTankClass * TurretTankClass(TurretTankClass * this, TurretTankClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretTankClass * __thiscall
TurretTankClass::TurretTankClass(TurretTankClass *this,TurretTankClass *param_1,long64 param_2)

{
  TurretTankClass *pTVar1;
  undefined4 unaff_EDI;
  
  pTVar1 = param_1;
  HoverCraftClass::HoverCraftClass
            ((HoverCraftClass *)this,(HoverCraftClass *)param_1,
             CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x3e6439ad,0x6d06fa2,&this->timeUndeploy,
                   pTVar1->timeUndeploy);
  ParameterDB::Get((ParameterDB *)&param_1,0x3e6439ad,0x9fa4327,(float *)&this->field_0x3c4,
                   *(float *)&pTVar1->field_0x3c4);
  ParameterDB::Get((ParameterDB *)&param_1,0x3e6439ad,0x74c3a47c,(float *)(this + 1),
                   (float)pTVar1[1]._padding_);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
