/*
 * Entry: 0047c87a
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::empty
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: bool empty(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::empty
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this)

{
  return (bool)('\x01' - (((int)this->_Mylast - (int)this->_Myfirst & 0xfffffffcU) != 0));
}
