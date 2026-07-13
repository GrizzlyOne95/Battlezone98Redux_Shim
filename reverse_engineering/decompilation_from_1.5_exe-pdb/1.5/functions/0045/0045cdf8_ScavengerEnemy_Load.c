/*
 * Entry: 0045cdf8
 * Name: ScavengerEnemy::Load
 * Namespace: ScavengerEnemy
 * Signature: bool Load(ScavengerEnemy * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavengerEnemy::Load(ScavengerEnemy *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,(float *)&this->field_0x14,4);
  if (((((bVar1) && (bVar1 = ::in(param_1,(int *)&this->field_0x18,4), bVar1)) &&
       (bVar1 = ::in(param_1,(int *)&this->field_0x1c,4), bVar1)) &&
      ((((bVar1 = ::in(param_1,(int *)&this->field_0x20,4), bVar1 &&
         (bVar1 = in_ptr(param_1,(void **)&this->field_0x24,4,"craft",this), bVar1)) &&
        ((bVar1 = ::in(param_1,(VECTOR_3D *)&this->field_0x28,0xc), bVar1 &&
         ((bVar1 = ::in(param_1,(VECTOR_3D *)&this->field_0x34,0xc), bVar1 &&
          (bVar1 = ::in(param_1,(float *)&this->field_0x40,4), bVar1)))))) &&
       (bVar1 = ::in(param_1,(bool *)&this->field_0x44,1), bVar1)))) &&
     (((bVar1 = ::in(param_1,(int *)&this->field_0x48,4), bVar1 &&
       (bVar1 = in_ptr(param_1,(void **)&this->field_0x54,4,"task",this), bVar1)) &&
      (bVar1 = AiProcess::Load((AiProcess *)this,param_1), bVar1)))) {
    return true;
  }
  return false;
}
