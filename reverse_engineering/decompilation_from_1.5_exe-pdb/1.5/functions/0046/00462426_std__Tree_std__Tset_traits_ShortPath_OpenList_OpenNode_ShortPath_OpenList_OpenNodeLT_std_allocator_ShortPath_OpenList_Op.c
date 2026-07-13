/*
 * Entry: 00462426
 * Name: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>::_Insert
 * Namespace: std::_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
 * Signature: iterator _Insert(_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_> * this, bool param_1, _Node * param_2, OpenNode * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
::_Insert(_Tree<std::_Tset_traits<ShortPath::OpenList::OpenNode,ShortPath::OpenList::OpenNodeLT,std::allocator<ShortPath::OpenList::OpenNode>,1>_>
          *this,bool param_1,_Node *param_2,OpenNode *param_3)

{
  Node *pNVar1;
  Node *pNVar2;
  _Node *p_Var3;
  _Node **pp_Var4;
  undefined4 extraout_EDX;
  Node *pNVar5;
  iterator iVar6;
  undefined3 in_stack_00000005;
  OpenNode *in_stack_00000010;
  logic_error local_44;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_20;
  
  if (0x15555553 < this->_Mysize) {
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
  pNVar2 = (Node *)_Buynode(this,this->_Myhead,(_Node *)param_3,this->_Myhead,in_stack_00000010,'\0'
                           );
  this->_Mysize = this->_Mysize + 1;
  pNVar5 = pNVar2;
  if ((_Node *)param_3 == this->_Myhead) {
    this->_Myhead->_Parent = (_Node *)pNVar2;
    this->_Myhead->_Left = (_Node *)pNVar2;
    p_Var3 = this->_Myhead;
  }
  else {
    if ((char)param_2 != '\0') {
      param_3->m_Node = pNVar2;
      if ((_Node *)param_3 == this->_Myhead->_Left) {
        this->_Myhead->_Left = (_Node *)pNVar2;
      }
      goto LAB_00462561;
    }
    param_3->h = (float)pNVar2;
    p_Var3 = this->_Myhead;
    if ((_Node *)param_3 != p_Var3->_Right) goto LAB_00462561;
  }
  p_Var3->_Right = (_Node *)pNVar2;
LAB_00462561:
  do {
    while( true ) {
      pp_Var4 = (_Node **)((int)pNVar5->PADDING_TEMP + 4);
      if ((*pp_Var4)->_Color != '\0') {
        this->_Myhead->_Parent->_Color = '\x01';
        const_iterator::const_iterator(_param_1,(_Node *)pNVar2,this);
        iVar6._4_4_ = extraout_EDX;
        iVar6._0_4_ = _param_1;
        return iVar6;
      }
      pNVar1 = (Node *)*pp_Var4;
      p_Var3 = *(_Node **)((int)pNVar1->PADDING_TEMP + 4);
      if (pNVar1 != (Node *)p_Var3->_Left) break;
      p_Var3 = p_Var3->_Right;
      if (p_Var3->_Color == '\0') {
LAB_0046251a:
        pNVar1->open = true;
        p_Var3->_Color = '\x01';
        (*pp_Var4)->_Parent->_Color = '\0';
        pNVar5 = (Node *)(*pp_Var4)->_Parent;
      }
      else {
        if (pNVar5 == (Node *)(pNVar1->pos).x) {
          _Lrotate(this,(_Node *)pNVar1);
          pNVar5 = pNVar1;
        }
        (*(_Node **)((int)pNVar5->PADDING_TEMP + 4))->_Color = '\x01';
        (*(_Node **)((int)pNVar5->PADDING_TEMP + 4))->_Parent->_Color = '\0';
        _Rrotate(this,(*(_Node **)((int)pNVar5->PADDING_TEMP + 4))->_Parent);
      }
    }
    p_Var3 = p_Var3->_Left;
    if (p_Var3->_Color == '\0') goto LAB_0046251a;
    if (pNVar5 == *(Node **)pNVar1->PADDING_TEMP) {
      _Rrotate(this,(_Node *)pNVar1);
      pNVar5 = pNVar1;
    }
    (*(_Node **)((int)pNVar5->PADDING_TEMP + 4))->_Color = '\x01';
    (*(_Node **)((int)pNVar5->PADDING_TEMP + 4))->_Parent->_Color = '\0';
    _Lrotate(this,(*(_Node **)((int)pNVar5->PADDING_TEMP + 4))->_Parent);
  } while( true );
}
