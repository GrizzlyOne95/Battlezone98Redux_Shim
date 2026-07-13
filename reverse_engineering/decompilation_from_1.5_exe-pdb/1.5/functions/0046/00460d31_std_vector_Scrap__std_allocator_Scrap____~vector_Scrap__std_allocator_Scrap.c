/*
 * Entry: 00460d31
 * Name: std::vector<Scrap_*,std::allocator<Scrap_*>_>::~vector<Scrap_*,std::allocator<Scrap_*>_>
 * Namespace: std::vector<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: void ~vector<Scrap_*,std::allocator<Scrap_*>_>(vector<Scrap_*,std::allocator<Scrap_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<Scrap_*,std::allocator<Scrap_*>_>::~vector<Scrap_*,std::allocator<Scrap_*>_>
          (vector<Scrap_*,std::allocator<Scrap_*>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
