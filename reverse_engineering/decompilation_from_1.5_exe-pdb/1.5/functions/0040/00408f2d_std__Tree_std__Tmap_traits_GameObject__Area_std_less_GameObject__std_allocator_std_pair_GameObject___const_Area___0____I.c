/*
 * Entry: 00408f2d
 * Name: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>::_Insert
 * Namespace: std::_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
 * Signature: iterator _Insert(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_> * this, bool param_1, _Node * param_2, pair<GameObject_*_const,Area> * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
::_Insert(_Tree<std::_Tmap_traits<GameObject_*,Area,std::less<GameObject_*>,std::allocator<std::pair<GameObject_*_const,Area>_>,0>_>
          *this,bool param_1,_Node *param_2,pair<GameObject_*_const,Area> *param_3)

{
  GameObject *pGVar1;
  GameObject *pGVar2;
  _Node *p_Var3;
  _Node **pp_Var4;
  undefined4 extraout_EDX;
  GameObject *pGVar5;
  iterator iVar6;
  undefined3 in_stack_00000005;
  pair<GameObject_*_const,Area> *in_stack_00000010;
  logic_error local_44;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_20;
  
  if (0xcccccca < this->_Mysize) {
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
  pGVar2 = (GameObject *)
           _Buynode(this,this->_Myhead,(_Node *)param_3,this->_Myhead,in_stack_00000010,'\0');
  this->_Mysize = this->_Mysize + 1;
  pGVar5 = pGVar2;
  if ((_Node *)param_3 == this->_Myhead) {
    this->_Myhead->_Parent = (_Node *)pGVar2;
    this->_Myhead->_Left = (_Node *)pGVar2;
    p_Var3 = this->_Myhead;
  }
  else {
    if ((char)param_2 != '\0') {
      param_3->first = pGVar2;
      if ((_Node *)param_3 == this->_Myhead->_Left) {
        this->_Myhead->_Left = (_Node *)pGVar2;
      }
      goto LAB_00409068;
    }
    (param_3->second).z0 = (float)pGVar2;
    p_Var3 = this->_Myhead;
    if ((_Node *)param_3 != p_Var3->_Right) goto LAB_00409068;
  }
  p_Var3->_Right = (_Node *)pGVar2;
LAB_00409068:
  do {
    while( true ) {
      pp_Var4 = (_Node **)&pGVar5->_padding_;
      if ((*pp_Var4)->_Color != '\0') {
        this->_Myhead->_Parent->_Color = '\x01';
        const_iterator::const_iterator(_param_1,(_Node *)pGVar2,this);
        iVar6._4_4_ = extraout_EDX;
        iVar6._0_4_ = _param_1;
        return iVar6;
      }
      pGVar1 = (GameObject *)*pp_Var4;
      p_Var3 = (_Node *)pGVar1->_padding_;
      if (pGVar1 != (GameObject *)p_Var3->_Left) break;
      p_Var3 = p_Var3->_Right;
      if (p_Var3->_Color == '\0') {
LAB_00409021:
        *(char *)&pGVar1->_padding_ = '\x01';
        p_Var3->_Color = '\x01';
        (*pp_Var4)->_Parent->_Color = '\0';
        pGVar5 = (GameObject *)(*pp_Var4)->_Parent;
      }
      else {
        if (pGVar5 == (GameObject *)pGVar1->_padding_) {
          _Lrotate(this,(_Node *)pGVar1);
          pGVar5 = pGVar1;
        }
        ((_Node *)pGVar5->_padding_)->_Color = '\x01';
        ((_Node *)pGVar5->_padding_)->_Parent->_Color = '\0';
        _Rrotate(this,((_Node *)pGVar5->_padding_)->_Parent);
      }
    }
    p_Var3 = p_Var3->_Left;
    if (p_Var3->_Color == '\0') goto LAB_00409021;
    if (pGVar5 == (GameObject *)pGVar1->_padding_) {
      _Rrotate(this,(_Node *)pGVar1);
      pGVar5 = pGVar1;
    }
    ((_Node *)pGVar5->_padding_)->_Color = '\x01';
    ((_Node *)pGVar5->_padding_)->_Parent->_Color = '\0';
    _Lrotate(this,((_Node *)pGVar5->_padding_)->_Parent);
  } while( true );
}
