/*
 * Entry: 004660ca
 * Name: TugEnemy::Save
 * Namespace: TugEnemy
 * Signature: bool Save(TugEnemy * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TugEnemy::Save(TugEnemy *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,(int *)&this->field_0x14,4,"curState");
  if ((((((bVar1) && (bVar1 = ::out(param_1,(int *)&this->field_0x18,4,"nextState"), bVar1)) &&
        (bVar1 = out_ptr(param_1,&this->field_0x1c,4,"craft"), bVar1)) &&
       ((bVar1 = ::out(param_1,(VECTOR_3D *)&this->field_0x20,0xc,"where"), bVar1 &&
        (bVar1 = ::out(param_1,(int *)&this->field_0x2c,4,"whoHandle"), bVar1)))) &&
      ((bVar1 = out_ptr(param_1,&this->field_0x30,4,"task"), bVar1 &&
       ((bVar1 = ::out(param_1,(float *)&this->field_0x34,4,"dropoffPoint"), bVar1 &&
        (bVar1 = ::out(param_1,(VECTOR_3D *)&this->field_0x38,0xc,"tugLocation"), bVar1)))))) &&
     (bVar1 = AiProcess::Save((AiProcess *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
