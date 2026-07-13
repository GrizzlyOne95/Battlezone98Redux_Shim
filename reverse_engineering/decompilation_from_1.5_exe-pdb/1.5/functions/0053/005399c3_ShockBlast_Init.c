/*
 * Entry: 005399c3
 * Name: ShockBlast::Init
 * Namespace: ShockBlast
 * Signature: void Init(ShockBlast * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShockBlast::Init(ShockBlast *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  int iVar1;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  Explosion::Init((Explosion *)this,param_1,param_2);
  local_1c.x = (float)param_1->posit_x;
  iVar1 = *(int *)&this->field_0xc;
  local_1c.y = (float)param_1->posit_y;
  local_1c.z = (float)param_1->posit_z;
  local_10 = local_1c.x;
  local_c = local_1c.y;
  local_8 = local_1c.z;
  ShockWaveEffect::AddShockWave
            (&shockwaveEffect,&local_1c,*(float *)(iVar1 + 0x3c),*(float *)(iVar1 + 0x50),
             ((float)*(int *)(iVar1 + 0x34) / *(float *)(iVar1 + 0x38)) * 0.5);
  return;
}
