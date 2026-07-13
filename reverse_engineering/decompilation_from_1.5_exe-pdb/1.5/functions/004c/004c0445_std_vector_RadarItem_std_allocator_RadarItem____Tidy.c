/*
 * Entry: 004c0445
 * Name: std::vector<RadarItem,std::allocator<RadarItem>_>::_Tidy
 * Namespace: std::vector<RadarItem,std::allocator<RadarItem>_>
 * Signature: void _Tidy(vector<RadarItem,std::allocator<RadarItem>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<RadarItem,std::allocator<RadarItem>_>::_Tidy
          (vector<RadarItem,std::allocator<RadarItem>_> *this)

{
  if (this->_Myfirst != (RadarItem *)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (RadarItem *)0x0;
  this->_Mylast = (RadarItem *)0x0;
  this->_Myend = (RadarItem *)0x0;
  return;
}
