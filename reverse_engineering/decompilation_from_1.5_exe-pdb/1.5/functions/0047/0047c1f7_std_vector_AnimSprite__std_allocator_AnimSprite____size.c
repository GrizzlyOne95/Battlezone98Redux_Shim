/*
 * Entry: 0047c1f7
 * Name: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::size
 * Namespace: std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: uint size(vector<AnimSprite_*,std::allocator<AnimSprite_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::size
          (vector<AnimSprite_*,std::allocator<AnimSprite_*>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 2;
}
