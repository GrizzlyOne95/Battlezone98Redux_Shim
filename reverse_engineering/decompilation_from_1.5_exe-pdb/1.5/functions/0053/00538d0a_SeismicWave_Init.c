/*
 * Entry: 00538d0a
 * Name: SeismicWave::Init
 * Namespace: SeismicWave
 * Signature: void Init(SeismicWave * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SeismicWave::Init(SeismicWave *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  float fVar1;
  float *pfVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  MAT_3D *pMVar5;
  MAT_3D local_5c;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  pfVar2 = (float *)(this->_padding_ + 0x80);
  pMVar5 = &local_5c;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar5->right_x = param_1->right_x;
    param_1 = (MAT_3D *)&param_1->right_y;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
  }
  local_5c.posit_x = (double)(local_5c.front_x * *pfVar2 + (float)local_5c.posit_x);
  local_5c.posit_y = (double)(local_5c.front_y * *pfVar2 + (float)local_5c.posit_y);
  local_5c.posit_z = (double)(local_5c.front_z * *pfVar2 + (float)local_5c.posit_z);
  Ordnance::Init((Ordnance *)this,&local_5c,param_2);
  iVar4 = this->_padding_;
  local_10 = ((VECTOR_3D *)(iVar4 + 0x38))->x;
  local_c = *(float *)(iVar4 + 0x3c);
  local_8 = *(float *)(iVar4 + 0x40);
  pVVar3 = ScaleVector(&local_1c,*(float *)(this->_padding_ + 0x50),*(VECTOR_3D *)(iVar4 + 0x38));
  local_10 = pVVar3->x;
  local_c = pVVar3->y;
  local_8 = pVVar3->z;
  this->_padding_ = (int)local_10;
  this->_padding_ = (int)local_c;
  this->_padding_ = (int)local_8;
  fVar1 = *(float *)(this->_padding_ + 0x50);
  this->_padding_ = (int)fVar1;
  if (fVar1 <= 0.0) {
    fVar1 = 1e+30;
  }
  else {
    fVar1 = 1.0 / fVar1;
  }
  this->_padding_ = (int)fVar1;
  this->scale = 0.0;
  UpdateExtents(this);
  return;
}
