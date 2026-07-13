/*
 * Entry: 00537a51
 * Name: RemoteDetonatorClass::RemoteDetonatorClass
 * Namespace: RemoteDetonatorClass
 * Signature: RemoteDetonatorClass * RemoteDetonatorClass(RemoteDetonatorClass * this, RemoteDetonatorClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

RemoteDetonatorClass * __thiscall
RemoteDetonatorClass::RemoteDetonatorClass
          (RemoteDetonatorClass *this,RemoteDetonatorClass *param_1,long64 param_2)

{
  int iVar1;
  undefined4 unaff_EDI;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  MortarClass::MortarClass
            ((MortarClass *)this,(MortarClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2));
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB(&local_1c,(char *)&this->_padding_);
  ParameterDB::Get(&local_1c,0xb7b58a5f,0x5b8f7784,local_18,0x10,(char *)0x0);
  if (local_18[0] == '\0') {
    iVar1 = param_1->armedReticle;
  }
  else {
    iVar1 = GetSpriteIndex(local_18);
  }
  this->armedReticle = iVar1;
  ParameterDB::~ParameterDB(&local_1c);
  return this;
}
