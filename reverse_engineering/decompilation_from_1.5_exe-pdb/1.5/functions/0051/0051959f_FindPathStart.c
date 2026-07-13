/*
 * Entry: 0051959f
 * Name: FindPathStart
 * Namespace: Global
 * Signature: void FindPathStart(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FindPathStart(void)

{
  Geizer *pGVar1;
  bool bVar2;
  Geizer **ppGVar3;
  VECTOR_3D *pVVar4;
  float *pfVar5;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_14;
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> local_c;
  
  std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
            (&local_c,Geizer::geizerList._Myfirst,(_Container_base_aux *)&Geizer::geizerList);
  while( true ) {
    std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::
    _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>
              (&local_14,Geizer::geizerList._Mylast,(_Container_base_aux *)&Geizer::geizerList);
    bVar2 = std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar2) break;
    ppGVar3 = std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator*(&local_c);
    pGVar1 = *ppGVar3;
    pVVar4 = (VECTOR_3D *)(**(code **)(pGVar1->_padding_ + 0xc))();
    bVar2 = OnBlocked(pVVar4);
    if (!bVar2) goto LAB_0051960d;
    std::_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator++(&local_c);
  }
  pGVar1 = (Geizer *)GameObject::userObject;
  if (GameObject::userObject != (GameObject *)0x0) {
LAB_0051960d:
    pfVar5 = (float *)(**(code **)(pGVar1->_padding_ + 0xc))();
    pathStart.x = *pfVar5;
    pathStart.y = pfVar5[1];
    pathStart.z = pfVar5[2];
  }
  return;
}
