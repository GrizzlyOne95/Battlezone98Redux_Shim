/*
 * Entry: 0053dbab
 * Name: Tracer::Init
 * Namespace: Tracer
 * Signature: void Init(Tracer * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tracer::Init(Tracer *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  double dVar1;
  double dVar2;
  int iVar3;
  
  Bullet::Init((Bullet *)this,param_1,param_2);
  iVar3 = this->_padding_;
  dVar1 = *(double *)(iVar3 + 0x50);
  dVar2 = *(double *)(iVar3 + 0x58);
  (this->startPos).x = *(double *)(iVar3 + 0x48);
  (this->startPos).y = dVar1;
  (this->startPos).z = dVar2;
  return;
}
