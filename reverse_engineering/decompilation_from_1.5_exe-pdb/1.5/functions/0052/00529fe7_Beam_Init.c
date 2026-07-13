/*
 * Entry: 00529fe7
 * Name: Beam::Init
 * Namespace: Beam
 * Signature: void Init(Beam * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Beam::Init(Beam *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  int iVar1;
  float fVar2;
  
  Bullet::Init((Bullet *)this,param_1,param_2);
  iVar1 = this->_padding_;
  (this->origin).x = *(double *)(iVar1 + 0x48);
  (this->origin).y = *(double *)(iVar1 + 0x50);
  (this->origin).z = *(double *)(iVar1 + 0x58);
  fVar2 = TimeStep();
  this->_padding_ = (int)-fVar2;
  return;
}
