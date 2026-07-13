/*
 * Entry: 0053d705
 * Name: TorpedoClass::TorpedoClass
 * Namespace: TorpedoClass
 * Signature: TorpedoClass * TorpedoClass(TorpedoClass * this, TorpedoClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TorpedoClass * __thiscall
TorpedoClass::TorpedoClass(TorpedoClass *this,TorpedoClass *param_1,long64 param_2)

{
  TorpedoClass *pTVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  ushort uVar6;
  ExplosionClass *pEVar7;
  ushort uVar8;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  int local_1c;
  int local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pTVar1 = param_1;
  PowerUpClass::PowerUpClass
            ((PowerUpClass *)this,(PowerUpClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_2,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x4f358485,&this->setAltitude,
                   param_1->setAltitude);
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0xb8add2a,&this->alphaTrack,
                   param_1->alphaTrack);
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x473d5031,&this->alphaDamp,param_1->alphaDamp
                  );
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x9410fcff,&this->velocForward,
                   param_1->velocForward);
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0xe94c7c19,&this->accelThrust,
                   param_1->accelThrust);
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x4ad4b447,&this->omegaTurn,param_1->omegaTurn
                  );
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x19b84820,&this->alphaSteer,
                   param_1->alphaSteer);
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x7c7c544b,&this->lifeSpan,param_1->lifeSpan);
  this->xplBlast = param_1->xplBlast;
  *(undefined2 *)this->soundThrust = *(undefined2 *)param_1->soundThrust;
  bVar2 = ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x5be2a777,&local_8,0.0);
  bVar3 = ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x52fd4a53,&local_10,0.0);
  bVar4 = ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x38720d72,&local_14,0.0);
  bVar5 = ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x7c8a1300,&local_c,0.0);
  if (bVar5 || (bVar4 || (bVar2 || bVar3))) {
    this->xplBlast = (ExplosionClass *)(local_14 + local_10 + local_c + local_8);
    if (local_c == 0.0) {
      uVar8 = 0;
    }
    else {
      uVar8 = 2;
    }
    if (local_10 == 0.0) {
      param_1._0_2_ = 0;
    }
    else {
      param_1._0_2_ = 4;
    }
    if (local_14 == 0.0) {
      uVar6 = 0;
    }
    else {
      uVar6 = 8;
    }
    *(ushort *)this->soundThrust = local_8 != 0.0 | uVar8 | (ushort)param_1 | uVar6;
  }
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0xd61bc22b,(long64 *)&local_1c,
                   (ulonglong)unaff_ESI << 0x20);
  if (local_1c == 0 && local_18 == 0) {
    pEVar7 = *(ExplosionClass **)(pTVar1->soundThrust + 4);
  }
  else {
    pEVar7 = ExplosionClass::Find(CONCAT44(local_18,local_1c));
  }
  *(ExplosionClass **)(this->soundThrust + 4) = pEVar7;
  ParameterDB::Get((ParameterDB *)&param_2,0xcba43500,0x48b2e796,this->soundThrust + 8,0x10,
                   pTVar1->soundThrust + 8);
  ParameterDB::~ParameterDB((ParameterDB *)&param_2);
  return this;
}
