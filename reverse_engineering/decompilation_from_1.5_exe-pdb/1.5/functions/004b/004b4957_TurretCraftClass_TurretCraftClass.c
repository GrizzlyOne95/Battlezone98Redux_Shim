/*
 * Entry: 004b4957
 * Name: TurretCraftClass::TurretCraftClass
 * Namespace: TurretCraftClass
 * Signature: TurretCraftClass * TurretCraftClass(TurretCraftClass * this, TurretCraftClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretCraftClass * __thiscall
TurretCraftClass::TurretCraftClass(TurretCraftClass *this,TurretCraftClass *param_1,long64 param_2)

{
  TurretCraftClass *pTVar1;
  undefined4 unaff_EDI;
  
  pTVar1 = param_1;
  CraftClass::CraftClass
            ((CraftClass *)this,(CraftClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xa3bfe245,0x6d06fa2,&this->omegaTurret,
                   pTVar1->omegaTurret);
  ParameterDB::Get((ParameterDB *)&param_1,0xa3bfe245,0xb8add2a,&this->alphaTrack,pTVar1->alphaTrack
                  );
  ParameterDB::Get((ParameterDB *)&param_1,0xa3bfe245,0x473d5031,&this->alphaDamp,pTVar1->alphaDamp)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xa3bfe245,0xdd47602d,&this->pitchPitch,
                   pTVar1->pitchPitch);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
