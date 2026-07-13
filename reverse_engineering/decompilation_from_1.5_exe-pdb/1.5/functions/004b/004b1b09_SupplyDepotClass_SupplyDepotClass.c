/*
 * Entry: 004b1b09
 * Name: SupplyDepotClass::SupplyDepotClass
 * Namespace: SupplyDepotClass
 * Signature: SupplyDepotClass * SupplyDepotClass(SupplyDepotClass * this, SupplyDepotClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SupplyDepotClass * __thiscall
SupplyDepotClass::SupplyDepotClass(SupplyDepotClass *this,SupplyDepotClass *param_1,long64 param_2)

{
  SupplyDepotClass *pSVar1;
  undefined4 unaff_EDI;
  
  pSVar1 = param_1;
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x7e56e2e8,0x1f80fefb,&this->supplyRange,
                   pSVar1->supplyRange);
  ParameterDB::Get((ParameterDB *)&param_1,0x7e56e2e8,0xbc6c4e61,&this->supplyDelay,
                   pSVar1->supplyDelay);
  ParameterDB::Get((ParameterDB *)&param_1,0x7e56e2e8,0x5c81dbd2,&this->supplyAmount,
                   pSVar1->supplyAmount);
  ParameterDB::Get((ParameterDB *)&param_1,0x7e56e2e8,0xb1d46bcd,this->supplySound,0x10,
                   pSVar1->supplySound);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
