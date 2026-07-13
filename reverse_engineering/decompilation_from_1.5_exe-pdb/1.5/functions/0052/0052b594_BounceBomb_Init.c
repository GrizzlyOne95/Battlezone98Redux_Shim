/*
 * Entry: 0052b594
 * Name: BounceBomb::Init
 * Namespace: BounceBomb
 * Signature: void Init(BounceBomb * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BounceBomb::Init(BounceBomb *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  uint *puVar1;
  
  Bullet::Init((Bullet *)this,param_1,param_2);
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 | 8;
  *(undefined4 *)&this->field_0xe0 = 0;
  return;
}
