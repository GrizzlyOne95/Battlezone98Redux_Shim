/*
 * Entry: 0047cba3
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Tidy
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: void _Tidy(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Tidy
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this)

{
  if (this->_Myfirst != (AnimSprite **)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (AnimSprite **)0x0;
  this->_Mylast = (AnimSprite **)0x0;
  this->_Myend = (AnimSprite **)0x0;
  return;
}
