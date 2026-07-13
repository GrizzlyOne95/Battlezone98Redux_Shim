/*
 * Entry: 00459a5e
 * Name: RecycleFeature::RecycleFeature
 * Namespace: RecycleFeature
 * Signature: RecycleFeature * RecycleFeature(RecycleFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RecycleFeature * __thiscall RecycleFeature::RecycleFeature(RecycleFeature *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
