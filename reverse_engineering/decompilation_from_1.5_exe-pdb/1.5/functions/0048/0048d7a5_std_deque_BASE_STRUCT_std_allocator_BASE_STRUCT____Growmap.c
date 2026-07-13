/*
 * Entry: 0048d7a5
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::_Growmap
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: void _Growmap(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::_Growmap
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this,uint param_1)

{
  uint uVar1;
  BASE_STRUCT **ppBVar2;
  uint uVar3;
  deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *local_c;
  deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *local_8;
  
  local_c = this;
  local_8 = this;
  if (0x15555555 - this->_Mapsize < param_1) {
    _Xlen();
  }
  uVar1 = this->_Mapsize;
  uVar3 = uVar1 >> 1;
  if (uVar3 < 8) {
    uVar3 = 8;
  }
  if ((param_1 < uVar3) && (uVar1 <= 0x15555555 - uVar3)) {
    param_1 = uVar3;
  }
  uVar3 = this->_Myoff >> 1;
  local_8 = (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *)
            _Allocate<BASE_STRUCT_*>(uVar1 + param_1,(BASE_STRUCT **)0x0);
  ppBVar2 = stdext::
            unchecked_uninitialized_copy<BASE_STRUCT_*_*,BASE_STRUCT_*_*,std::allocator<BASE_STRUCT_*>_>
                      (this->_Map + uVar3,this->_Map + this->_Mapsize,
                       (BASE_STRUCT **)((int)local_8 + uVar3 * 4),
                       (allocator<BASE_STRUCT_*> *)&this->_padding_);
  if (param_1 < uVar3) {
    stdext::
    unchecked_uninitialized_copy<BASE_STRUCT_*_*,BASE_STRUCT_*_*,std::allocator<BASE_STRUCT_*>_>
              (this->_Map,this->_Map + param_1,ppBVar2,(allocator<BASE_STRUCT_*> *)&this->_padding_)
    ;
    local_c = (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *)0x0;
    ppBVar2 = stdext::
              unchecked_uninitialized_copy<BASE_STRUCT_*_*,BASE_STRUCT_*_*,std::allocator<BASE_STRUCT_*>_>
                        (this->_Map + param_1,this->_Map + uVar3,(BASE_STRUCT **)local_8,
                         (allocator<BASE_STRUCT_*> *)&this->_padding_);
    stdext::unchecked_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*>
              (ppBVar2,param_1,(BASE_STRUCT **)&local_c);
  }
  else {
    local_c = (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *)0x0;
    ppBVar2 = stdext::
              unchecked_uninitialized_copy<BASE_STRUCT_*_*,BASE_STRUCT_*_*,std::allocator<BASE_STRUCT_*>_>
                        (this->_Map,this->_Map + uVar3,ppBVar2,
                         (allocator<BASE_STRUCT_*> *)&this->_padding_);
    stdext::unchecked_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*>
              (ppBVar2,param_1 - uVar3,(BASE_STRUCT **)&local_c);
    local_c = (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *)0x0;
    stdext::unchecked_fill_n<BASE_STRUCT_*_*,unsigned_int,BASE_STRUCT_*>
              ((BASE_STRUCT **)local_8,uVar3,(BASE_STRUCT **)&local_c);
  }
  if (this->_Map != (BASE_STRUCT **)0x0) {
    operator_delete(this->_Map);
  }
  this->_Map = (BASE_STRUCT **)local_8;
  this->_Mapsize = this->_Mapsize + param_1;
  return;
}
