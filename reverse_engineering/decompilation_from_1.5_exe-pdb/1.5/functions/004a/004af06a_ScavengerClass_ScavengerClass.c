/*
 * Entry: 004af06a
 * Name: ScavengerClass::ScavengerClass
 * Namespace: ScavengerClass
 * Signature: ScavengerClass * ScavengerClass(ScavengerClass * this, ScavengerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScavengerClass * __thiscall
ScavengerClass::ScavengerClass(ScavengerClass *this,ScavengerClass *param_1,long64 param_2)

{
  ScavengerClass *pSVar1;
  undefined3 extraout_var;
  char *pcVar2;
  char *pcVar3;
  char unaff_BL;
  char unaff_SI;
  undefined4 unaff_EDI;
  int iVar4;
  int iVar5;
  char cVar6;
  int iVar7;
  
  pSVar1 = param_1;
  HoverCraftClass::HoverCraftClass
            ((HoverCraftClass *)this,(HoverCraftClass *)param_1,CONCAT44(unaff_EDI,(int)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x3b47476d,0x5424e,(long *)(this->soundPickup + 4),
                   *(long *)(pSVar1->soundPickup + 4));
  ParameterDB::Get((ParameterDB *)&param_1,0x3b47476d,0xc7620108,this->soundPickup + 8,0x10,
                   pSVar1->soundPickup + 8);
  ParameterDB::Get((ParameterDB *)&param_1,0x3b47476d,0x41e5b62b,this->deployMsg + 8,0x10,
                   pSVar1->deployMsg + 8);
  ParameterDB::Get((ParameterDB *)&param_1,0x3b47476d,0x43d74028,this->foundMsg + 8,0x10,
                   pSVar1->foundMsg + 8);
  ParameterDB::Get((ParameterDB *)&param_1,0x3b47476d,0xcf941f93,this->notFoundMsg + 8,0x10,
                   pSVar1->notFoundMsg + 8);
  ParameterDB::Get((ParameterDB *)&param_1,0x3b47476d,0xcc359f08,this->noDropMsg + 8,0x10,
                   pSVar1->noDropMsg + 8);
  cVar6 = (char)this->_padding_;
  pcVar3 = (char *)CONCAT31(extraout_var,cVar6);
  if (cVar6 == 'b') {
    param_2._0_4_ = CONCAT31(param_2._1_3_,0x61);
  }
  else if (cVar6 == 'c') {
    param_2._0_4_ = CONCAT31(param_2._1_3_,0x73);
  }
  else {
    param_2._0_4_ = (uint)param_2._1_3_ << 8;
  }
  iVar4 = (int)param_2;
  cVar6 = (char)(int)param_2;
  iVar7 = (int)param_2;
  GetScavMessage(pcVar3,cVar6,unaff_SI,unaff_BL);
  pcVar2 = (char *)(uint)(byte)this->_padding_;
  iVar5 = iVar4;
  GetScavMessage(pcVar2,cVar6,(char)pcVar3,(char)iVar7);
  pcVar3 = (char *)(uint)(byte)this->_padding_;
  GetScavMessage(pcVar3,cVar6,(char)pcVar2,(char)iVar5);
  GetScavMessage((char *)(uint)(byte)this->_padding_,cVar6,(char)pcVar3,(char)iVar4);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
