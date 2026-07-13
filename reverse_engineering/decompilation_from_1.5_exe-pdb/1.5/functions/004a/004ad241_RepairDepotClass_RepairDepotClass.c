/*
 * Entry: 004ad241
 * Name: RepairDepotClass::RepairDepotClass
 * Namespace: RepairDepotClass
 * Signature: RepairDepotClass * RepairDepotClass(RepairDepotClass * this, RepairDepotClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RepairDepotClass * __thiscall
RepairDepotClass::RepairDepotClass(RepairDepotClass *this,RepairDepotClass *param_1,long64 param_2)

{
  RepairDepotClass *pRVar1;
  undefined4 unaff_EDI;
  
  pRVar1 = param_1;
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xaa3067d6,0xec53dbd9,&this->repairRange,
                   pRVar1->repairRange);
  ParameterDB::Get((ParameterDB *)&param_1,0xaa3067d6,0x361c9203,&this->repairDelay,
                   pRVar1->repairDelay);
  ParameterDB::Get((ParameterDB *)&param_1,0xaa3067d6,0xce3138,&this->repairAmount,
                   pRVar1->repairAmount);
  ParameterDB::Get((ParameterDB *)&param_1,0xaa3067d6,0x7982020b,this->repairSound,0x10,
                   pRVar1->repairSound);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
