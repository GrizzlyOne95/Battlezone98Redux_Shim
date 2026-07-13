/*
 * Entry: 00485129
 * Name: CommTowerClass::CommTowerClass
 * Namespace: CommTowerClass
 * Signature: CommTowerClass * CommTowerClass(CommTowerClass * this, CommTowerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CommTowerClass * __thiscall
CommTowerClass::CommTowerClass(CommTowerClass *this,CommTowerClass *param_1,long64 param_2)

{
  CommTowerClass *pCVar1;
  undefined4 unaff_EDI;
  
  pCVar1 = param_1;
  BuildingClass::BuildingClass
            ((BuildingClass *)this,(BuildingClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x178c1cee,0x487f8e17,&this->rangeScan,pCVar1->rangeScan)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0x178c1cee,0xde687e15,&this->periodScan,
                   pCVar1->periodScan);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
