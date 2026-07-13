/*
 * Entry: 005cb815
 * Name: `dynamic_initializer_for_'boundingBox''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'boundingBox''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__boundingBox__(void)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)&boundingBox);
  boundingBox._padding_ = (int)&BoundingBox::_vftable_;
  boundingBox.showCollision = false;
  atexit(_dynamic_atexit_destructor_for__boundingBox__);
  return;
}
