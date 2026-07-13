/*
 * Entry: 005315ea
 * Name: MagnetMineClass::MagnetMineClass
 * Namespace: MagnetMineClass
 * Signature: MagnetMineClass * MagnetMineClass(MagnetMineClass * this, MagnetMineClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MagnetMineClass * __thiscall
MagnetMineClass::MagnetMineClass(MagnetMineClass *this,MagnetMineClass *param_1,long64 param_2)

{
  MagnetMineClass *pMVar1;
  undefined4 unaff_EDI;
  
  pMVar1 = param_1;
  MineClass::MineClass
            ((MineClass *)this,(MineClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x24f7f5bc,0x682cd2b2,&this->triggerDelay,
                   pMVar1->triggerDelay);
  ParameterDB::Get((ParameterDB *)&param_1,0x24f7f5bc,0x66623dd5,&this->fieldRadius,
                   pMVar1->fieldRadius);
  ParameterDB::Get((ParameterDB *)&param_1,0x24f7f5bc,0x6cf48f7f,&this->objPushCenter,
                   pMVar1->objPushCenter);
  ParameterDB::Get((ParameterDB *)&param_1,0x24f7f5bc,0xa9b5f7e3,&this->objPushEdge,
                   pMVar1->objPushEdge);
  ParameterDB::Get((ParameterDB *)&param_1,0x24f7f5bc,0x27970654,&this->objDrag,pMVar1->objDrag);
  ParameterDB::Get((ParameterDB *)&param_1,0x24f7f5bc,0xc829c5ad,&this->ordPushCenter,
                   pMVar1->ordPushCenter);
  ParameterDB::Get((ParameterDB *)&param_1,0x24f7f5bc,0x1703fa09,&this->ordPushEdge,
                   pMVar1->ordPushEdge);
  ParameterDB::Get((ParameterDB *)&param_1,0x24f7f5bc,0x5b205972,&this->ordDrag,pMVar1->ordDrag);
  this->objPushEdge = (this->objPushEdge - this->objPushCenter) / this->fieldRadius;
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
