/*
 * Entry: 004c2cc2
 * Name: CockpitTimer::~CockpitTimer
 * Namespace: CockpitTimer
 * Signature: void ~CockpitTimer(CockpitTimer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitTimer::~CockpitTimer(CockpitTimer *this)

{
  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *plVar1;
  _Iterator<1> _Var2;
  _Const_iterator<1> _Var3;
  _Const_iterator<1> _Var4;
  _Iterator<1> _Var5;
  _Iterator<1> _Var6;
  _Const_iterator<1> _Var7;
  _Const_iterator<1> _Var8;
  list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *this_00;
  int iVar9;
  _Iterator<1> _Var10;
  undefined1 auStack_54 [8];
  undefined1 auStack_4c [8];
  undefined1 auStack_44 [8];
  undefined1 auStack_3c [8];
  _Const_iterator<1> _Stack_34;
  _Const_iterator<1> _Stack_2c;
  _Const_iterator<1> _Stack_24;
  _Const_iterator<1> _Stack_1c;
  _Const_iterator<1> _Stack_14;
  _Const_iterator<1> _Stack_c;
  
  this_00 = displayList;
  this->_padding_ = (int)&DisplayInterface::_vftable_;
  _Stack_c._Ptr = (_Node *)this;
  std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::remove
            (this_00,(DisplayInterface **)&_Stack_c._Ptr);
  iVar9 = 0;
  do {
    plVar1 = *(list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> **)
              ((int)simulateList + iVar9);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&_Stack_1c,plVar1->_Myhead,plVar1);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&_Stack_c,plVar1->_Myhead,plVar1);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&_Stack_14,plVar1->_Myhead->_Next,plVar1);
    _Var2._4_4_ = _Stack_14._padding_;
    _Var2._0_4_ = auStack_3c;
    _Var6._4_4_ = _Stack_c._padding_;
    _Var6._0_4_ = _Stack_14._Ptr;
    _Var10 = std::
             remove_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
                       (_Var2,_Var6,(IsMyView)_Stack_c._Ptr);
    _Var4._Ptr = (_Node *)*_Var10._0_4_;
    _Var4._padding_ = (int)auStack_44;
    _Var8._Ptr = (_Node *)_Stack_1c._padding_;
    _Var8._padding_ = _Var10._0_4_[1];
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::erase(plVar1,_Var4,_Var8);
    plVar1 = *(list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> **)
              ((int)renderList + iVar9);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&_Stack_34,plVar1->_Myhead,plVar1);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&_Stack_24,plVar1->_Myhead,plVar1);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&_Stack_2c,plVar1->_Myhead->_Next,plVar1);
    _Var10._4_4_ = _Stack_2c._padding_;
    _Var10._0_4_ = auStack_4c;
    _Var5._4_4_ = _Stack_24._padding_;
    _Var5._0_4_ = _Stack_2c._Ptr;
    _Var10 = std::
             remove_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
                       (_Var10,_Var5,(IsMyView)_Stack_24._Ptr);
    _Var3._Ptr = (_Node *)*_Var10._0_4_;
    _Var3._padding_ = (int)auStack_54;
    _Var7._Ptr = (_Node *)_Stack_34._padding_;
    _Var7._padding_ = _Var10._0_4_[1];
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::erase(plVar1,_Var3,_Var7);
    iVar9 = iVar9 + 4;
  } while (iVar9 < 0x30);
  return;
}
