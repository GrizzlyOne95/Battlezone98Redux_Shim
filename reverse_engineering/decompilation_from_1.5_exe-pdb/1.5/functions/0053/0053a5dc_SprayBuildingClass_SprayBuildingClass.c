/*
 * Entry: 0053a5dc
 * Name: SprayBuildingClass::SprayBuildingClass
 * Namespace: SprayBuildingClass
 * Signature: SprayBuildingClass * SprayBuildingClass(SprayBuildingClass * this, SprayBuildingClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SprayBuildingClass * __thiscall
SprayBuildingClass::SprayBuildingClass
          (SprayBuildingClass *this,SprayBuildingClass *param_1,long64 param_2)

{
  SprayBuildingClass *pSVar1;
  OrdnanceClass *pOVar2;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int in_stack_00000008;
  
  pSVar1 = param_1;
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x47523d0e,0x19d3ebc6,(long64 *)&stack0x00000008,
                   (ulonglong)unaff_ESI << 0x20);
  if (in_stack_00000008 == 0 && (int)param_2 == 0) {
    this->payloadClass = (OrdnanceClass *)0x0;
  }
  else {
    pOVar2 = OrdnanceClass::Find(CONCAT44((int)param_2,in_stack_00000008));
    this->payloadClass = pOVar2;
  }
  ParameterDB::Get((ParameterDB *)&param_1,0x47523d0e,0xcfde2fc0,this->fireSound,0x10,
                   pSVar1->fireSound);
  ParameterDB::Get((ParameterDB *)&param_1,0x47523d0e,0x682cd2b2,&this->triggerDelay,
                   pSVar1->triggerDelay);
  ParameterDB::Get((ParameterDB *)&param_1,0x47523d0e,0xd9356908,&this->shotDelay,pSVar1->shotDelay)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0x47523d0e,0x4f358485,&this->setAltitude,
                   pSVar1->setAltitude);
  ParameterDB::Get((ParameterDB *)&param_1,0x47523d0e,0x73accd30,&this->omegaSpin,
                   pSVar1->setAltitude);
  ParameterDB::Get((ParameterDB *)&param_1,0x47523d0e,0x98902ade,&this->anglePitch,
                   pSVar1->anglePitch);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
