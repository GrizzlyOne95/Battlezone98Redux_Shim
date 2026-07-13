/*
 * Entry: 004c7e11
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Incsize
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>
 * Signature: void _Incsize(list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Incsize
          (list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *this,uint param_1)

{
  logic_error local_44;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_20;
  
  if (0x3fffffff - this->_Mysize < param_1) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &local_20,"list<T> too long");
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
  this->_Mysize = this->_Mysize + param_1;
  return;
}
