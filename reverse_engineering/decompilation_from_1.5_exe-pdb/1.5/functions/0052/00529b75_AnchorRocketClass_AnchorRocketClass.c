/*
 * Entry: 00529b75
 * Name: AnchorRocketClass::AnchorRocketClass
 * Namespace: AnchorRocketClass
 * Signature: AnchorRocketClass * AnchorRocketClass(AnchorRocketClass * this, AnchorRocketClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnchorRocketClass * __thiscall
AnchorRocketClass::AnchorRocketClass
          (AnchorRocketClass *this,AnchorRocketClass *param_1,long64 param_2)

{
  AnchorRocketClass *pAVar1;
  undefined4 unaff_EDI;
  
  pAVar1 = param_1;
  RocketClass::RocketClass
            ((RocketClass *)this,(RocketClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xec437ec4,0x27bac631,&this->accelDrag,pAVar1->accelDrag)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xec437ec4,0xc0783809,&this->alphaDrag,pAVar1->alphaDrag)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xec437ec4,0x10d7bd55,&this->anchorTime,
                   pAVar1->anchorTime);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
