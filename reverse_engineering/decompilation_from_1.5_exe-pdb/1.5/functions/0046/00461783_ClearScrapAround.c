/*
 * Entry: 00461783
 * Name: ClearScrapAround
 * Namespace: Global
 * Signature: void ClearScrapAround(float param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClearScrapAround(float param_1,VECTOR_3D *param_2)

{
  float fVar1;
  float fVar2;
  VECTOR_3D *pVVar3;
  bool bVar4;
  float *pfVar5;
  Scrap **ppSVar6;
  Range_Search_Results local_58;
  vector<Scrap_*,std::allocator<Scrap_*>_> local_2c;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_14;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_c;
  
  Scrap_UpdateRange();
  pVVar3 = param_2;
  Range::Search(Scrap::scrapRange,(double)param_2->x,(double)param_2->z,(double)param_1,&local_58);
  std::vector<Scrap_*,std::allocator<Scrap_*>_>::vector<Scrap_*,std::allocator<Scrap_*>_>(&local_2c)
  ;
  std::vector<Scrap_*,std::allocator<Scrap_*>_>::reserve(&local_2c,0x40);
  while( true ) {
    bVar4 = Range_Search_Results::Get_Next_Object(&local_58,(int **)&param_2);
    if (!bVar4) break;
    local_c._Myptr = (Scrap **)GameObject::GetObj((int)param_2->x);
    if ((GameObject *)local_c._Myptr != (GameObject *)0x0) {
      pfVar5 = (float *)(**(code **)(((GameObject *)local_c._Myptr)->_padding_ + 0xc))();
      fVar1 = pVVar3->x - *pfVar5;
      fVar2 = pVVar3->z - pfVar5[2];
      if (fVar2 * fVar2 + fVar1 * fVar1 < param_1 * param_1) {
        std::vector<Scrap_*,std::allocator<Scrap_*>_>::push_back
                  (&local_2c,(Scrap **)&local_c._Myptr);
      }
    }
  }
  std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
            (&local_c,local_2c._Myfirst,(_Container_base_aux *)&local_2c);
  std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
            (&local_14,local_2c._Mylast,(_Container_base_aux *)&local_2c);
  bVar4 = std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator==
                    (&local_c,&local_14);
  while (bVar4 == false) {
    ppSVar6 = std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator*(&local_c);
    (**(code **)((*ppSVar6)->_padding_ + 0x10))();
    std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator++(&local_c);
    std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
    _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
              (&local_14,local_2c._Mylast,(_Container_base_aux *)&local_2c);
    bVar4 = std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator==
                      (&local_c,&local_14);
  }
  std::vector<Scrap_*,std::allocator<Scrap_*>_>::_Tidy(&local_2c);
  operator_delete((void *)local_2c._padding_);
  return;
}
