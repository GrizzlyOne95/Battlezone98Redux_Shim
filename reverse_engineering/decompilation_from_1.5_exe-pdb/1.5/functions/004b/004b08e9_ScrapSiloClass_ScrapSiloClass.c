/*
 * Entry: 004b08e9
 * Name: ScrapSiloClass::ScrapSiloClass
 * Namespace: ScrapSiloClass
 * Signature: ScrapSiloClass * ScrapSiloClass(ScrapSiloClass * this, ScrapSiloClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapSiloClass * __thiscall
ScrapSiloClass::ScrapSiloClass(ScrapSiloClass *this,ScrapSiloClass *param_1,long64 param_2)

{
  ScrapSiloClass *pSVar1;
  undefined4 unaff_EDI;
  
  pSVar1 = param_1;
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x2f77045d,0x92a6e0eb,&this->scrapHold,pSVar1->scrapHold)
  ;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
