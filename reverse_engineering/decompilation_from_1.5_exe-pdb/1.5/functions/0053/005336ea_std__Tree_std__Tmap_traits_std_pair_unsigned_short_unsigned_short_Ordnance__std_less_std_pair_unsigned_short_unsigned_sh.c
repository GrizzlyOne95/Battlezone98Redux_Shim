/*
 * Entry: 005336ea
 * Name: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::erase
 * Namespace: std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
 * Signature: iterator erase(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_> * this, const_iterator param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Removing unreachable block (ram,0x005337e4) */
/* WARNING: Removing unreachable block (ram,0x005337f4) */
/* WARNING: Removing unreachable block (ram,0x005337fd) */
/* WARNING: Removing unreachable block (ram,0x00533800) */
/* WARNING: Removing unreachable block (ram,0x005337f0) */
/* WARNING: Removing unreachable block (ram,0x0053380d) */
/* WARNING: Removing unreachable block (ram,0x0053381d) */
/* WARNING: Removing unreachable block (ram,0x00533828) */
/* WARNING: Removing unreachable block (ram,0x00533824) */
/* WARNING: Removing unreachable block (ram,0x00533818) */
/* WARNING: Removing unreachable block (ram,0x0053382b) */

iterator __thiscall
std::
_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
::erase(_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
        *this,const_iterator param_1)

{
  const_iterator cVar1;
  _Node *p_Var2;
  _Node *p_Var3;
  _Node *p_Var4;
  _Node *p_Var5;
  _Node *p_Var6;
  iterator iVar7;
  _Node *in_stack_0000000c;
  logic_error local_48;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_24;
  _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
  *local_8;
  
  local_8 = this;
  if (in_stack_0000000c->_Isnil != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &local_24,"invalid map/set<T> iterator");
    logic_error::logic_error(&local_48,&local_24);
    local_48._padding_ = (int)&out_of_range::_vftable_;
    stdext::exception::_Raise((exception *)&local_48);
    local_48._padding_ = (int)&out_of_range::_vftable_;
    logic_error::~logic_error(&local_48);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &local_24);
  }
  const_iterator::_Inc((const_iterator *)&param_1._Ptr);
  p_Var6 = in_stack_0000000c->_Left;
  if (p_Var6->_Isnil == '\0') {
    if (in_stack_0000000c->_Right->_Isnil == '\0') {
      p_Var6 = in_stack_0000000c->_Right;
    }
  }
  else {
    p_Var6 = in_stack_0000000c->_Right;
  }
  p_Var4 = in_stack_0000000c->_Parent;
  if (p_Var6->_Isnil == '\0') {
    p_Var6->_Parent = p_Var4;
  }
  if (local_8->_Myhead->_Parent == in_stack_0000000c) {
    local_8->_Myhead->_Parent = p_Var6;
  }
  else if (p_Var4->_Left == in_stack_0000000c) {
    p_Var4->_Left = p_Var6;
  }
  else {
    p_Var4->_Right = p_Var6;
  }
  if (local_8->_Myhead->_Left == in_stack_0000000c) {
    p_Var5 = p_Var4;
    if (p_Var6->_Isnil == '\0') {
      p_Var2 = p_Var6->_Left;
      p_Var5 = p_Var6;
      while (p_Var3 = p_Var2, p_Var3->_Isnil == '\0') {
        p_Var5 = p_Var3;
        p_Var2 = p_Var3->_Left;
      }
    }
    local_8->_Myhead->_Left = p_Var5;
  }
  if (local_8->_Myhead->_Right == in_stack_0000000c) {
    p_Var5 = p_Var4;
    if (p_Var6->_Isnil == '\0') {
      p_Var2 = p_Var6->_Right;
      p_Var5 = p_Var6;
      while (p_Var3 = p_Var2, p_Var3->_Isnil == '\0') {
        p_Var5 = p_Var3;
        p_Var2 = p_Var3->_Right;
      }
    }
    local_8->_Myhead->_Right = p_Var5;
  }
  if (in_stack_0000000c->_Color != '\x01') {
LAB_0053394d:
    operator_delete(in_stack_0000000c);
    if (local_8->_Mysize != 0) {
      local_8->_Mysize = local_8->_Mysize - 1;
    }
    cVar1._Ptr = param_1._Ptr;
    cVar1._padding_ = param_1._padding_;
    iVar7 = _Make_iter(local_8,cVar1);
    iVar7._0_4_ = param_1._padding_;
    return iVar7;
  }
LAB_00533901:
  p_Var5 = p_Var4;
  if ((p_Var6 == local_8->_Myhead->_Parent) || (p_Var6->_Color != '\x01')) goto LAB_00533949;
  p_Var4 = p_Var5->_Left;
  if (p_Var6 == p_Var4) {
    p_Var4 = p_Var5->_Right;
    if (p_Var4->_Color == '\0') {
      p_Var4->_Color = '\x01';
      p_Var5->_Color = '\0';
      _Lrotate(local_8,p_Var5);
      p_Var4 = p_Var5->_Right;
    }
    if (p_Var4->_Isnil == '\0') {
      if ((p_Var4->_Left->_Color != '\x01') || (p_Var4->_Right->_Color != '\x01')) {
        if (p_Var4->_Right->_Color == '\x01') {
          p_Var4->_Left->_Color = '\x01';
          p_Var4->_Color = '\0';
          _Rrotate(local_8,p_Var4);
          p_Var4 = p_Var5->_Right;
        }
        p_Var4->_Color = p_Var5->_Color;
        p_Var5->_Color = '\x01';
        p_Var4->_Right->_Color = '\x01';
        _Lrotate(local_8,p_Var5);
        goto LAB_00533949;
      }
LAB_005338f8:
      p_Var4->_Color = '\0';
    }
  }
  else {
    if (p_Var4->_Color == '\0') {
      p_Var4->_Color = '\x01';
      p_Var5->_Color = '\0';
      _Rrotate(local_8,p_Var5);
      p_Var4 = p_Var5->_Left;
    }
    if (p_Var4->_Isnil == '\0') {
      if ((p_Var4->_Right->_Color == '\x01') && (p_Var4->_Left->_Color == '\x01'))
      goto LAB_005338f8;
      if (p_Var4->_Left->_Color == '\x01') {
        p_Var4->_Right->_Color = '\x01';
        p_Var4->_Color = '\0';
        _Lrotate(local_8,p_Var4);
        p_Var4 = p_Var5->_Left;
      }
      p_Var4->_Color = p_Var5->_Color;
      p_Var5->_Color = '\x01';
      p_Var4->_Left->_Color = '\x01';
      _Rrotate(local_8,p_Var5);
LAB_00533949:
      p_Var6->_Color = '\x01';
      goto LAB_0053394d;
    }
  }
  p_Var4 = p_Var5->_Parent;
  p_Var6 = p_Var5;
  goto LAB_00533901;
}
