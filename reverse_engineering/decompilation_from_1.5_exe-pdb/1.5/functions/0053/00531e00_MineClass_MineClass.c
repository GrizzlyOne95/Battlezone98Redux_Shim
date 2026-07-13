/*
 * Entry: 00531e00
 * Name: MineClass::MineClass
 * Namespace: MineClass
 * Signature: MineClass * MineClass(MineClass * this, MineClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MineClass * __thiscall MineClass::MineClass(MineClass *this,MineClass *param_1,long64 param_2)

{
  MineClass *pMVar1;
  undefined4 unaff_EDI;
  
  pMVar1 = param_1;
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x9a3cce76,0x7c7c544b,&this->lifeSpan,pMVar1->lifeSpan);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
