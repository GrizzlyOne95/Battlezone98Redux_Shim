/*
 * Entry: 004c2d52
 * Name: CockpitTimer::Init
 * Namespace: CockpitTimer
 * Signature: void Init(CockpitTimer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitTimer::Init(CockpitTimer *this)

{
  int iVar1;
  
  iVar1 = GetSpriteIndex("Mission Time");
  this->title = iVar1;
  iVar1 = GetSpriteIndex("bignum_G.0");
  this->index[0] = iVar1;
  iVar1 = GetSpriteIndex("bignum_Y.0");
  this->index[1] = iVar1;
  iVar1 = GetSpriteIndex("bignum_R.0");
  this->frac = 0.0;
  this->index[2] = iVar1;
  this->timer = 0;
  this->warn = -0x80000000;
  this->alert = -0x80000000;
  this->countdown = true;
  this->active = false;
  this->show = false;
  this->hours = false;
  return;
}
