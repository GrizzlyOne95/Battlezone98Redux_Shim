/*
 * Entry: 004e6c08
 * Name: SpawnPoint::GetClosestEnemy
 * Namespace: SpawnPoint
 * Signature: float GetClosestEnemy(VECTOR_3D param_1, int param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl SpawnPoint::GetClosestEnemy(VECTOR_3D param_1,int param_2,float param_3)

{
  Craft *this;
  bool bVar1;
  Craft **ppCVar2;
  int iVar3;
  VECTOR_3D *pVVar4;
  float fVar5;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_14;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_c;
  
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_c,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
  while( true ) {
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_14,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
    bVar1 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar1) break;
    ppCVar2 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(&local_c);
    this = *ppCVar2;
    bVar1 = GameObject::EnemyP((GameObject *)this,param_2);
    if ((bVar1) && ((AiProcess *)this->_padding_ != (AiProcess *)0x0)) {
      iVar3 = (**(code **)(this->_padding_ + 0x30))();
      if ((*(int *)(iVar3 + 0xac) != 4) || ((*(byte *)(iVar3 + 0x14) & 0x30) != 0)) {
        pVVar4 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
        fVar5 = Dist3D_Squared(param_1,*pVVar4);
        if (fVar5 < param_3) {
          param_3 = fVar5;
        }
      }
    }
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_c);
  }
  return param_3;
}
