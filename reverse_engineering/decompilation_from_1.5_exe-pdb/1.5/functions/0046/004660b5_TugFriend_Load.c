/*
 * Entry: 004660b5
 * Name: TugFriend::Load
 * Namespace: TugFriend
 * Signature: bool Load(TugFriend * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TugFriend::Load(TugFriend *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,(int *)&this->field_0x14,4);
  if ((((((bVar1) && (bVar1 = ::in(param_1,(int *)&this->field_0x18,4), bVar1)) &&
        (bVar1 = in_ptr(param_1,(void **)&this->field_0x1c,4,"craft",this), bVar1)) &&
       ((bVar1 = ::in(param_1,(VECTOR_3D *)&this->field_0x20,0xc), bVar1 &&
        (bVar1 = ::in(param_1,(int *)&this->field_0x2c,4), bVar1)))) &&
      ((bVar1 = in_ptr(param_1,(void **)&this->field_0x30,4,"task",this), bVar1 &&
       ((bVar1 = ::in(param_1,(float *)&this->field_0x34,4), bVar1 &&
        (bVar1 = ::in(param_1,(VECTOR_3D *)&this->field_0x38,0xc), bVar1)))))) &&
     (bVar1 = AiProcess::Load((AiProcess *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
