/*
 * Entry: 004e16c6
 * Name: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>::_Insert
 * Namespace: std::_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
 * Signature: iterator _Insert(_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_> * this, bool param_1, _Node * param_2, pair<unsigned_short_const_,NetPlayer_*> * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
::_Insert(_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
          *this,bool param_1,_Node *param_2,pair<unsigned_short_const_,NetPlayer_*> *param_3)

{
  _Node *p_Var1;
  _Node *p_Var2;
  _Node **pp_Var3;
  _Node *p_Var4;
  undefined4 extraout_EDX;
  _Node *p_Var5;
  iterator iVar6;
  undefined3 in_stack_00000005;
  pair<unsigned_short_const_,NetPlayer_*> *in_stack_00000010;
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
  p_Var1 = _Buynode(this,this->_Myhead,(_Node *)param_3,this->_Myhead,in_stack_00000010,'\0');
  this->_Mysize = this->_Mysize + 1;
  p_Var5 = p_Var1;
  if ((_Node *)param_3 == this->_Myhead) {
    this->_Myhead->_Parent = p_Var1;
    this->_Myhead->_Left = p_Var1;
    p_Var2 = this->_Myhead;
  }
  else {
    if ((char)param_2 != '\0') {
      *(_Node **)param_3 = p_Var1;
      if ((_Node *)param_3 == this->_Myhead->_Left) {
        this->_Myhead->_Left = p_Var1;
      }
      goto LAB_004e1801;
    }
    *(_Node **)(param_3 + 1) = p_Var1;
    p_Var2 = this->_Myhead;
    if ((_Node *)param_3 != p_Var2->_Right) goto LAB_004e1801;
  }
  p_Var2->_Right = p_Var1;
LAB_004e1801:
  do {
    while( true ) {
      pp_Var3 = &p_Var5->_Parent;
      if ((*pp_Var3)->_Color != '\0') {
        this->_Myhead->_Parent->_Color = '\x01';
        const_iterator::const_iterator(_param_1,p_Var1,this);
        iVar6._4_4_ = extraout_EDX;
        iVar6._0_4_ = _param_1;
        return iVar6;
      }
      p_Var2 = *pp_Var3;
      p_Var4 = p_Var2->_Parent;
      if (p_Var2 != p_Var4->_Left) break;
      p_Var4 = p_Var4->_Right;
      if (p_Var4->_Color == '\0') {
LAB_004e17ba:
        p_Var2->_Color = '\x01';
        p_Var4->_Color = '\x01';
        (*pp_Var3)->_Parent->_Color = '\0';
        p_Var5 = (*pp_Var3)->_Parent;
      }
      else {
        if (p_Var5 == p_Var2->_Right) {
          _Lrotate(this,p_Var2);
          p_Var5 = p_Var2;
        }
        p_Var5->_Parent->_Color = '\x01';
        p_Var5->_Parent->_Parent->_Color = '\0';
        _Rrotate(this,p_Var5->_Parent->_Parent);
      }
    }
    p_Var4 = p_Var4->_Left;
    if (p_Var4->_Color == '\0') goto LAB_004e17ba;
    if (p_Var5 == p_Var2->_Left) {
      _Rrotate(this,p_Var2);
      p_Var5 = p_Var2;
    }
    p_Var5->_Parent->_Color = '\x01';
    p_Var5->_Parent->_Parent->_Color = '\0';
    _Lrotate(this,p_Var5->_Parent->_Parent);
  } while( true );
}
