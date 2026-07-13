/*
 * Entry: 004d74a1
 * Name: PathDisplay::DrawPaths
 * Namespace: PathDisplay
 * Signature: void DrawPaths(PathDisplay * this, bool param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawPaths(PathDisplay *this,bool param_1)

{
  AiPath *pAVar1;
  bool bVar2;
  AiPath **ppAVar3;
  long lVar4;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,(AiPath::pathList._Myhead)->_Next,&AiPath::pathList);
  local_c._padding_ = local_14._padding_;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,AiPath::pathList._Myhead,&AiPath::pathList);
    bVar2 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar2) break;
    ppAVar3 = std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator*(&local_c)
    ;
    pAVar1 = *ppAVar3;
    if ((param_1) || (pAVar1->label != (char *)0x0)) {
      lVar4 = DisplayInterface::colorWhite;
      if (pAVar1->label == (char *)0x0) {
        lVar4 = DisplayInterface::colorCyan;
      }
      DrawPath(this,pAVar1,-1,lVar4);
    }
    std::list<AiPath_*,std::allocator<AiPath_*>_>::_Const_iterator<1>::operator++(&local_c);
  }
  return;
}
