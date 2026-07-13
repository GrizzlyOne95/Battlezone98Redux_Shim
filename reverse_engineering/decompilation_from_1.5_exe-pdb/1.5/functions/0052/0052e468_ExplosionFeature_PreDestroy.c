/*
 * Entry: 0052e468
 * Name: ExplosionFeature::PreDestroy
 * Namespace: ExplosionFeature
 * Signature: void PreDestroy(ExplosionFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ExplosionFeature::PreDestroy(ExplosionFeature *this)

{
  bool bVar1;
  Explosion **ppEVar2;
  _Const_iterator<1> _Stack_1c;
  _Const_iterator<1> _Stack_14;
  _Const_iterator<1> _Stack_c;
  
  std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&_Stack_c,(Explosion::explosionList._Myhead)->_Next,&Explosion::explosionList);
  while( true ) {
    std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&_Stack_14,Explosion::explosionList._Myhead,&Explosion::explosionList);
    bVar1 = std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator==
                      (&_Stack_c,&_Stack_14);
    if (bVar1) break;
    _Stack_1c._padding_ = _Stack_c._padding_;
    _Stack_1c._Ptr = _Stack_c._Ptr;
    std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator++(&_Stack_c);
    ppEVar2 = std::list<Explosion_*,std::allocator<Explosion_*>_>::_Const_iterator<1>::operator*
                        (&_Stack_1c);
    (**(code **)((*ppEVar2)->_padding_ + 8))();
  }
  return;
}
