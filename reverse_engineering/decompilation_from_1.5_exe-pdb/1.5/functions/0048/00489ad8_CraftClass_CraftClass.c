/*
 * Entry: 00489ad8
 * Name: CraftClass::CraftClass
 * Namespace: CraftClass
 * Signature: CraftClass * CraftClass(CraftClass * this, CraftClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CraftClass * __thiscall CraftClass::CraftClass(CraftClass *this,CraftClass *param_1,long64 param_2)

{
  CraftClass *pCVar1;
  undefined4 unaff_EDI;
  
  pCVar1 = param_1;
  GameObjectClass::GameObjectClass
            ((GameObjectClass *)this,(GameObjectClass *)param_1,
             CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x487f8e17,&this->rangeScan,pCVar1->rangeScan)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xde687e15,&this->periodScan,
                   pCVar1->periodScan);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xf91cc422,&this->velocJam,pCVar1->velocJam);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x462d7284,&this->fPersonEjectRatio,
                   pCVar1->fPersonEjectRatio);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xe0d32ed5,this->selectOtherMsg,0x10,
                   (char *)0x0);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xed291e8a,this->selectOtherMsg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x72695529,this->selectWaitMsg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xf62bf4f4,this->selectGoMsg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x30459269,this->selectFollowMsg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xae256912,this->selectAttackMsg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x121488aa,this->selectPickupMsg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xa3a7b4fe,this->selectDropoffMsg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xe1e44043,this->selectDeployMsg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x861dffe6,this->selectUser1Msg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xf5578de9,this->selectUser2Msg,0x10,
                   this->selectOtherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x4438fcf2,this->otherMsg,0x10,(char *)0x0);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xad7c767c,this->goMsg,0x10,this->otherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x3bb77f51,this->goObjectMsg,0x10,
                   this->otherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x6b8a29c1,this->followMsg,0x10,this->otherMsg
                  );
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xb0914f33,this->followMeMsg,0x10,
                   this->followMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x3b7848ba,this->attackMsg,0x10,this->otherMsg
                  );
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x4207428d,this->repairMsg,0x10,this->otherMsg
                  );
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x8dff63e5,this->reloadMsg,0x10,this->otherMsg
                  );
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x551927e5,this->rescueMsg,0x10,this->otherMsg
                  );
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xbc02535b,this->recycleMsg,0x10,
                   this->otherMsg);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x9dc1ff0e,this->user1Msg,0x10,this->otherMsg)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x31b20a11,this->user2Msg,0x10,this->otherMsg)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x6dd9ab88,this->deployedMsg,0x10,(char *)0x0)
  ;
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0xc3a9b516,this->packedMsg,0x10,(char *)0x0);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x13e9acc1,this->killedMsg,0x10,(char *)0x0);
  ParameterDB::Get((ParameterDB *)&param_1,0xc287c42b,0x23f871f8,this->diedMsg,0x10,(char *)0x0);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
