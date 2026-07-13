/*
 * Entry: 00539ca1
 * Name: SniperShell::Init
 * Namespace: SniperShell
 * Signature: void Init(SniperShell * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SniperShell::Init(SniperShell *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  VECTOR_3D *pVVar4;
  VECTOR_3D VStack_1c;
  float fStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  Ordnance::Init((Ordnance *)this,param_1,param_2);
  iVar3 = *(int *)&this->field_0x18;
  fStack_10 = ((VECTOR_3D *)(iVar3 + 0x38))->x;
  uStack_c = *(undefined4 *)(iVar3 + 0x3c);
  uStack_8 = *(undefined4 *)(iVar3 + 0x40);
  pVVar4 = ScaleVector(&VStack_1c,*(float *)(*(int *)&this->field_0x10 + 0x50),
                       *(VECTOR_3D *)(iVar3 + 0x38));
  fVar1 = pVVar4->y;
  fVar2 = pVVar4->z;
  *(float *)&this->field_0x34 = pVVar4->x;
  *(float *)&this->field_0x38 = fVar1;
  *(float *)&this->field_0x3c = fVar2;
  fVar1 = *(float *)(*(int *)&this->field_0x10 + 0x50);
  *(float *)&this->field_0x24 = fVar1;
  if (fVar1 <= 0.0) {
    fVar1 = 1e+30;
  }
  else {
    fVar1 = 1.0 / fVar1;
  }
  *(float *)&this->field_0x28 = fVar1;
  this->field_0xd8 = 1;
  return;
}
