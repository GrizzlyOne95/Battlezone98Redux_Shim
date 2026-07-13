/*
 * Entry: 0045cdfd
 * Name: ScavengerEnemy::Save
 * Namespace: ScavengerEnemy
 * Signature: bool Save(ScavengerEnemy * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavengerEnemy::Save(ScavengerEnemy *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,(float *)&this->field_0x14,4,"oldhealth");
  if (((((bVar1) && (bVar1 = ::out(param_1,(int *)&this->field_0x18,4,"curState"), bVar1)) &&
       (bVar1 = ::out(param_1,(int *)&this->field_0x1c,4,"nextState"), bVar1)) &&
      ((((bVar1 = ::out(param_1,(int *)&this->field_0x20,4,"whoHandle"), bVar1 &&
         (bVar1 = out_ptr(param_1,&this->field_0x24,4,"craft"), bVar1)) &&
        ((bVar1 = ::out(param_1,(VECTOR_3D *)&this->field_0x28,0xc,"where"), bVar1 &&
         ((bVar1 = ::out(param_1,(VECTOR_3D *)&this->field_0x34,0xc,"lastScrap"), bVar1 &&
          (bVar1 = ::out(param_1,(float *)&this->field_0x40,4,"wait_time"), bVar1)))))) &&
       (bVar1 = ::out(param_1,(bool *)&this->field_0x44,1,"recycle"), bVar1)))) &&
     (((bVar1 = ::out(param_1,(int *)&this->field_0x48,4,"team"), bVar1 &&
       (bVar1 = out_ptr(param_1,&this->field_0x54,4,"task"), bVar1)) &&
      (bVar1 = AiProcess::Save((AiProcess *)this,param_1), bVar1)))) {
    return true;
  }
  return false;
}
