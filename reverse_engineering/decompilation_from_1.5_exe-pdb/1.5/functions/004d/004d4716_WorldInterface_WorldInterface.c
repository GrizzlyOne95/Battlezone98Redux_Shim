/*
 * Entry: 004d4716
 * Name: WorldInterface::WorldInterface
 * Namespace: WorldInterface
 * Signature: WorldInterface * WorldInterface(WorldInterface * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WorldInterface * __thiscall WorldInterface::WorldInterface(WorldInterface *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
