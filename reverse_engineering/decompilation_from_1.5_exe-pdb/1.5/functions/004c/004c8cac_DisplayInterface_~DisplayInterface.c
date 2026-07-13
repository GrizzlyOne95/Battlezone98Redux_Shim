/*
 * Entry: 004c8cac
 * Name: DisplayInterface::~DisplayInterface
 * Namespace: DisplayInterface
 * Signature: void ~DisplayInterface(DisplayInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DisplayInterface::~DisplayInterface(DisplayInterface *this)

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
  undefined1 local_54 [8];
  undefined1 local_4c [8];
  undefined1 local_44 [8];
  undefined1 local_3c [8];
  _Const_iterator<1> local_34;
  _Const_iterator<1> local_2c;
  _Const_iterator<1> local_24;
  _Const_iterator<1> local_1c;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  this_00 = displayList;
  this->_padding_ = (int)&_vftable_;
  local_c._Ptr = (_Node *)this;
  std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::remove
            (this_00,(DisplayInterface **)&local_c._Ptr);
  iVar9 = 0;
  do {
    plVar1 = *(list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> **)
              ((int)simulateList + iVar9);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_1c,plVar1->_Myhead,plVar1);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_c,plVar1->_Myhead,plVar1);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_14,plVar1->_Myhead->_Next,plVar1);
    _Var2._4_4_ = local_14._padding_;
    _Var2._0_4_ = local_3c;
    _Var6._4_4_ = local_c._padding_;
    _Var6._0_4_ = local_14._Ptr;
    _Var10 = std::
             remove_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
                       (_Var2,_Var6,(IsMyView)local_c._Ptr);
    _Var4._Ptr = (_Node *)*_Var10._0_4_;
    _Var4._padding_ = (int)local_44;
    _Var8._Ptr = (_Node *)local_1c._padding_;
    _Var8._padding_ = _Var10._0_4_[1];
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::erase(plVar1,_Var4,_Var8);
    plVar1 = *(list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> **)
              ((int)renderList + iVar9);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_34,plVar1->_Myhead,plVar1);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_24,plVar1->_Myhead,plVar1);
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<1>::
    _Const_iterator<1>(&local_2c,plVar1->_Myhead->_Next,plVar1);
    _Var10._4_4_ = local_2c._padding_;
    _Var10._0_4_ = local_4c;
    _Var5._4_4_ = local_24._padding_;
    _Var5._0_4_ = local_2c._Ptr;
    _Var10 = std::
             remove_if<std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Iterator<1>,IsMyView>
                       (_Var10,_Var5,(IsMyView)local_24._Ptr);
    _Var3._Ptr = (_Node *)*_Var10._0_4_;
    _Var3._padding_ = (int)local_54;
    _Var7._Ptr = (_Node *)local_34._padding_;
    _Var7._padding_ = _Var10._0_4_[1];
    std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::erase(plVar1,_Var3,_Var7);
    iVar9 = iVar9 + 4;
  } while (iVar9 < 0x30);
  return;
}
