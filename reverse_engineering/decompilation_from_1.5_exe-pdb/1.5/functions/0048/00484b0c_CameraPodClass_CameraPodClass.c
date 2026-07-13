/*
 * Entry: 00484b0c
 * Name: CameraPodClass::CameraPodClass
 * Namespace: CameraPodClass
 * Signature: CameraPodClass * CameraPodClass(CameraPodClass * this, CameraPodClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CameraPodClass * __thiscall
CameraPodClass::CameraPodClass(CameraPodClass *this,CameraPodClass *param_1,long64 param_2)

{
  CameraPodClass *pCVar1;
  undefined4 unaff_EDI;
  
  pCVar1 = param_1;
  PowerUpClass::PowerUpClass
            ((PowerUpClass *)this,(PowerUpClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x6df5d19b,0x73accd30,&this->omegaSpin,pCVar1->omegaSpin)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0x6df5d19b,0x487f8e17,&this->rangeScan,pCVar1->rangeScan)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0x6df5d19b,0xde687e15,&this->periodScan,
                   pCVar1->periodScan);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
