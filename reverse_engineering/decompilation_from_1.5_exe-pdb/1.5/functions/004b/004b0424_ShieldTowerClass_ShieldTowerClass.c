/*
 * Entry: 004b0424
 * Name: ShieldTowerClass::ShieldTowerClass
 * Namespace: ShieldTowerClass
 * Signature: ShieldTowerClass * ShieldTowerClass(ShieldTowerClass * this, ShieldTowerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ShieldTowerClass * __thiscall
ShieldTowerClass::ShieldTowerClass(ShieldTowerClass *this,ShieldTowerClass *param_1,long64 param_2)

{
  ShieldTowerClass *pSVar1;
  undefined4 unaff_EDI;
  
  pSVar1 = param_1;
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0xe4ca43fc,(float *)&this->shieldBox,
                   (pSVar1->shieldBox).min.x);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0x7fb47d32,&(this->shieldBox).max.x,
                   (pSVar1->shieldBox).max.x);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0xe5ca458f,&(this->shieldBox).min.y,
                   (pSVar1->shieldBox).min.y);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0x80b47ec5,&(this->shieldBox).max.y,
                   (pSVar1->shieldBox).max.y);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0xe6ca4722,&(this->shieldBox).min.z,
                   (pSVar1->shieldBox).min.z);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0x7db47a0c,&(this->shieldBox).max.z,
                   (pSVar1->shieldBox).max.z);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0xd5099ea,&this->objPush,pSVar1->objPush);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0x27970654,&this->objDrag,pSVar1->objDrag);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0x1ad95fc4,&this->ordPush,pSVar1->ordPush);
  ParameterDB::Get((ParameterDB *)&param_1,0xbca7f8b7,0x5b205972,&this->ordDrag,pSVar1->ordDrag);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
