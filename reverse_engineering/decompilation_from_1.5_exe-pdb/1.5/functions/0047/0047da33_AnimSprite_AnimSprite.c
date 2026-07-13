/*
 * Entry: 0047da33
 * Name: AnimSprite::AnimSprite
 * Namespace: AnimSprite
 * Signature: AnimSprite * AnimSprite(AnimSprite * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite * __thiscall AnimSprite::AnimSprite(AnimSprite *this,_OBJ76 *param_1)

{
  float fVar1;
  float fVar2;
  
  this->obj = param_1;
  fVar1 = (param_1->bBox).max.y;
  this->geometry[0].x = (param_1->bBox).min.x;
  this->geometry[0].y = fVar1;
  this->geometry[0].z = 0.0;
  fVar1 = (param_1->bBox).max.y;
  this->geometry[1].x = (param_1->bBox).max.x;
  this->geometry[1].y = fVar1;
  this->geometry[1].z = 0.0;
  fVar1 = (param_1->bBox).min.y;
  this->geometry[2].x = (param_1->bBox).max.x;
  this->geometry[2].y = fVar1;
  this->geometry[2].z = 0.0;
  fVar1 = (param_1->bBox).min.x;
  fVar2 = (param_1->bBox).min.y;
  this->frame = (FrameInfo (*) [8])0x0;
  this->geometry[3].x = fVar1;
  this->geometry[3].y = fVar2;
  this->geometry[3].z = 0.0;
  param_1 = (_OBJ76 *)this;
  std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::push_back
            (&spriteList,(AnimSprite **)&param_1);
  return this;
}
