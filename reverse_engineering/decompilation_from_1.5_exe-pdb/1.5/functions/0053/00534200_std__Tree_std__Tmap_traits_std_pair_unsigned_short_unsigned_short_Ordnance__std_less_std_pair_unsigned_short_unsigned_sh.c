/*
 * Entry: 00534200
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::_Insert
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: iterator _Insert(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, bool param_1, _Node * param_2, pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::_Insert(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
          *this,bool param_1,_Node *param_2,
         pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *param_3)

{
  pair<unsigned_short,unsigned_short> pVar1;
  pair<unsigned_short,unsigned_short> pVar2;
  _Node *p_Var3;
  _Node **pp_Var4;
  undefined4 extraout_EDX;
  pair<unsigned_short,unsigned_short> pVar5;
  iterator iVar6;
  undefined3 in_stack_00000005;
  pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *in_stack_00000010;
  logic_error local_44;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_20;
  
  if (0x1ffffffd < this->_Mysize) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &local_20,"map/set<T> too long");
    logic_error::logic_error(&local_44,&local_20);
    local_44._padding_ = (int)&length_error::_vftable_;
    stdext::exception::_Raise((exception *)&local_44);
    local_44._padding_ = (int)&length_error::_vftable_;
    logic_error::~logic_error(&local_44);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &local_20);
  }
  pVar2 = (pair<unsigned_short,unsigned_short>)
          _Buynode(this,this->_Myhead,(_Node *)param_3,this->_Myhead,in_stack_00000010,'\0');
  this->_Mysize = this->_Mysize + 1;
  pVar5 = pVar2;
  if ((_Node *)param_3 == this->_Myhead) {
    this->_Myhead->_Parent = (_Node *)pVar2;
    this->_Myhead->_Left = (_Node *)pVar2;
    p_Var3 = this->_Myhead;
  }
  else {
    if ((char)param_2 != '\0') {
      param_3->first = pVar2;
      if ((_Node *)param_3 == this->_Myhead->_Left) {
        this->_Myhead->_Left = (_Node *)pVar2;
      }
      goto LAB_0053433b;
    }
    param_3[1].first = pVar2;
    p_Var3 = this->_Myhead;
    if ((_Node *)param_3 != p_Var3->_Right) goto LAB_0053433b;
  }
  p_Var3->_Right = (_Node *)pVar2;
LAB_0053433b:
  do {
    while( true ) {
      pp_Var4 = (_Node **)((int)pVar5 + 4);
      if ((*pp_Var4)->_Color != '\0') {
        this->_Myhead->_Parent->_Color = '\x01';
        const_iterator::const_iterator(_param_1,(_Node *)pVar2,this);
        iVar6._4_4_ = extraout_EDX;
        iVar6._0_4_ = _param_1;
        return iVar6;
      }
      pVar1 = (pair<unsigned_short,unsigned_short>)*pp_Var4;
      p_Var3 = *(_Node **)((int)pVar1 + 4);
      if (pVar1 != (pair<unsigned_short,unsigned_short>)p_Var3->_Left) break;
      p_Var3 = p_Var3->_Right;
      if (p_Var3->_Color == '\0') {
LAB_005342f4:
        *(char *)((int)pVar1 + 0x14) = '\x01';
        p_Var3->_Color = '\x01';
        (*pp_Var4)->_Parent->_Color = '\0';
        pVar5 = (pair<unsigned_short,unsigned_short>)(*pp_Var4)->_Parent;
      }
      else {
        if (pVar5 == *(pair<unsigned_short,unsigned_short> *)((int)pVar1 + 8)) {
          _Lrotate(this,(_Node *)pVar1);
          pVar5 = pVar1;
        }
        (*(_Node **)((int)pVar5 + 4))->_Color = '\x01';
        (*(_Node **)((int)pVar5 + 4))->_Parent->_Color = '\0';
        _Rrotate(this,(*(_Node **)((int)pVar5 + 4))->_Parent);
      }
    }
    p_Var3 = p_Var3->_Left;
    if (p_Var3->_Color == '\0') goto LAB_005342f4;
    if (pVar5 == *(pair<unsigned_short,unsigned_short> *)pVar1) {
      _Rrotate(this,(_Node *)pVar1);
      pVar5 = pVar1;
    }
    (*(_Node **)((int)pVar5 + 4))->_Color = '\x01';
    (*(_Node **)((int)pVar5 + 4))->_Parent->_Color = '\0';
    _Lrotate(this,(*(_Node **)((int)pVar5 + 4))->_Parent);
  } while( true );
}
