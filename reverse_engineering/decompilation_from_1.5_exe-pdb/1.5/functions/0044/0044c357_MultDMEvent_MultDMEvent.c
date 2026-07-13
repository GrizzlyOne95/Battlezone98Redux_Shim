/*
 * Entry: 0044c357
 * Name: MultDMEvent::MultDMEvent
 * Namespace: MultDMEvent
 * Signature: MultDMEvent * MultDMEvent(MultDMEvent * this, AiMission * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MultDMEvent * __thiscall MultDMEvent::MultDMEvent(MultDMEvent *this,AiMission *param_1)

{
  int *piVar1;
  AiPath *pAVar2;
  bool bVar3;
  AiPath **ppAVar4;
  int iVar5;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  AiProcess::AiProcess((AiProcess *)this,param_1,(GameObject *)0x0);
  this->fTimeInZone = 0.0;
  this->dwLastTime = 0;
  this->fTimeInZoneLast = 0.0;
  this->doing_king_of_the_hill = 0;
  this->_padding_ = (int)&_vftable_;
  this->starttimer = 1;
  king_of_the_hill_game = 0;
  stratgy_game = 0;
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,(AiPath::pathList._Myhead)->_Next,&AiPath::pathList);
  local_c._padding_ = local_14._padding_;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,AiPath::pathList._Myhead,&AiPath::pathList);
    bVar3 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar3) {
      return this;
    }
    ppAVar4 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*(&local_c)
    ;
    pAVar2 = *ppAVar4;
    iVar5 = strncmp(pAVar2->label,"king",4);
    if (iVar5 == 0) break;
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator++(&local_c);
  }
  this->doing_king_of_the_hill = 1;
  king_of_the_hill_game = 1;
  this->king_x = pAVar2->points->x;
  this->king_z = pAVar2->points->z;
  iVar5 = atoi(pAVar2->label + 4);
  piVar1 = &this->king_dist;
  *piVar1 = iVar5;
  if (iVar5 < 1) {
    *piVar1 = 1;
  }
  *piVar1 = *piVar1 * *piVar1;
  return this;
}
