/*
 * Entry: 004d7bd1
 * Name: PathDisplay::SelectPath
 * Namespace: PathDisplay
 * Signature: void SelectPath(PathDisplay * this, AiPath * * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::SelectPath(PathDisplay *this,AiPath **param_1,int *param_2)

{
  AiPath *pAVar1;
  bool bVar2;
  AiPath **ppAVar3;
  uint uVar4;
  int iVar5;
  _Const_iterator<1> local_20;
  _Const_iterator<1> local_18;
  int local_10;
  int local_c;
  PathDisplay *local_8;
  
  local_8 = this;
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_20,(AiPath::pathList._Myhead)->_Next,&AiPath::pathList);
  local_18._padding_ = local_20._padding_;
  local_18._Ptr = local_20._Ptr;
  do {
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_20,AiPath::pathList._Myhead,&AiPath::pathList);
    bVar2 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                      (&local_18,&local_20);
    if (bVar2) {
      *param_1 = (AiPath *)0x0;
      *param_2 = -1;
      return;
    }
    ppAVar3 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*
                        (&local_18);
    pAVar1 = *ppAVar3;
    iVar5 = 0;
    if ((pAVar1->label != (char *)0x0) && (0 < pAVar1->pointCount)) {
      do {
        (**(code **)(local_8->_padding_ + 0x20))
                  (pAVar1->points[iVar5].x,pAVar1->points[iVar5].z,&local_c,&local_10);
        uVar4 = local_c - DisplayInterface::mousePos.x >> 0x1f;
        if (((int)((local_c - DisplayInterface::mousePos.x ^ uVar4) - uVar4) < 4) &&
           (uVar4 = local_10 - DisplayInterface::mousePos.y >> 0x1f,
           (int)((local_10 - DisplayInterface::mousePos.y ^ uVar4) - uVar4) < 4)) {
          *param_1 = pAVar1;
          *param_2 = iVar5;
          return;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < pAVar1->pointCount);
    }
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator++(&local_18);
  } while( true );
}
