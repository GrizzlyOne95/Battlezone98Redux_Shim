/*
 * Entry: 004cd6df
 * Name: EngineFlame::Control
 * Namespace: EngineFlame
 * Signature: void Control(EngineFlame * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EngineFlame::Control(EngineFlame *this)

{
  long *plVar1;
  
  plVar1 = &this->flameIndex;
  *plVar1 = *plVar1 + 1;
  if (this->flameFrames <= *plVar1) {
    *plVar1 = 0;
  }
  this->flamePtr = this->flameList;
  return;
}
