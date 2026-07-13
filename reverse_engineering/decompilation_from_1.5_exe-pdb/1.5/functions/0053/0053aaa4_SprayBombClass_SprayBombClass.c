/*
 * Entry: 0053aaa4
 * Name: SprayBombClass::SprayBombClass
 * Namespace: SprayBombClass
 * Signature: SprayBombClass * SprayBombClass(SprayBombClass * this, SprayBombClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SprayBombClass * __thiscall
SprayBombClass::SprayBombClass(SprayBombClass *this,SprayBombClass *param_1,long64 param_2)

{
  SprayBombClass *pSVar1;
  GameObjectClass *pGVar2;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  SprayBombClass *local_c;
  SprayBombClass *local_8;
  
  pSVar1 = param_1;
  local_c = this;
  local_8 = this;
  GrenadeClass::GrenadeClass
            ((GrenadeClass *)this,(GrenadeClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_1,(char *)&this->_padding_);
  ParameterDB::Get((ParameterDB *)&param_1,0x47d244de,0x830b28dd,(long64 *)&local_c,
                   CONCAT44(unaff_ESI,(undefined4)param_2));
  pGVar2 = GameObjectClass::Find(CONCAT44(local_8,local_c));
  this->sprayClass = pGVar2;
  ParameterDB::Get((ParameterDB *)&param_1,0x47d244de,0xa7666fac,&this->bounceRatio,
                   pSVar1->bounceRatio);
  ParameterDB::Get((ParameterDB *)&param_1,0x47d244de,0x7e5a762c,this->soundBounce,0x10,
                   pSVar1->soundBounce);
  ParameterDB::~ParameterDB((ParameterDB *)&param_1);
  return this;
}
