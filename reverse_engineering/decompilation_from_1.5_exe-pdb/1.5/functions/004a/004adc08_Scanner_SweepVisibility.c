/*
 * Entry: 004adc08
 * Name: Scanner::SweepVisibility
 * Namespace: Scanner
 * Signature: void SweepVisibility(Scanner * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scanner::SweepVisibility(Scanner *this)

{
  VECTOR_3D VVar1;
  bool bVar2;
  float *pfVar3;
  GameObject *pGVar4;
  int iVar5;
  VECTOR_3D *pVVar6;
  uint uVar7;
  float fVar8;
  Range_Search_Results local_48;
  float local_1c;
  float fStack_18;
  float local_14;
  float local_10;
  int *local_c;
  undefined4 local_8;
  
  pfVar3 = (float *)(**(code **)(this->owner->_padding_ + 0xc))();
  local_1c = *pfVar3;
  fStack_18 = pfVar3[1];
  local_14 = pfVar3[2];
  local_8 = (**(code **)(this->owner->_padding_ + 4))();
  pGVar4 = GameObject::GetObj(this->owner->targetHandle);
  if (pGVar4 != (GameObject *)0x0) {
    uVar7 = 1 << ((byte)local_8 & 0x1f);
    pGVar4->isVisible = pGVar4->isVisible | uVar7;
    pGVar4->seen = pGVar4->seen | uVar7;
  }
  if (0.0 < this->period) {
    fVar8 = TimeStep();
    fVar8 = fVar8 + this->sweep;
    this->sweep = fVar8;
    if (fVar8 <= 0.0) {
      this->active = false;
      return;
    }
    this->sweep = fVar8 - this->period;
  }
  this->active = true;
  Range::Search(GameObject::objectRange,(double)local_1c,(double)local_14,(double)this->range,
                &local_48);
  local_10 = this->range * this->range;
  while (bVar2 = Range_Search_Results::Get_Next_Object(&local_48,&local_c), bVar2) {
    pGVar4 = GameObject::GetObj(*local_c);
    if ((pGVar4 != (GameObject *)0x0) && ((pGVar4->obj->flags & 1) == 0)) {
      iVar5 = (**(code **)pGVar4->_padding_)();
      if ((*(int *)(iVar5 + 0x28) != 4) &&
         ((pGVar4->jammer == (Jammer *)0x0 || (bVar2 = Jammer::IsJamming(pGVar4->jammer), !bVar2))))
      {
        pVVar6 = (VECTOR_3D *)(**(code **)(pGVar4->_padding_ + 0xc))();
        VVar1.y = fStack_18;
        VVar1.x = local_1c;
        VVar1.z = local_14;
        fVar8 = Dist3D_Squared(*pVVar6,VVar1);
        if (fVar8 < local_10) {
          uVar7 = 1 << ((byte)local_8 & 0x1f);
          pGVar4->isVisible = pGVar4->isVisible | uVar7;
          pGVar4->seen = pGVar4->seen | uVar7;
        }
      }
    }
  }
  return;
}
