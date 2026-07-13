/*
 * Entry: 0047c1e4
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::capacity
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: uint capacity(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::capacity
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this)

{
  if (this->_Myfirst == (AnimSprite **)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 2;
}
