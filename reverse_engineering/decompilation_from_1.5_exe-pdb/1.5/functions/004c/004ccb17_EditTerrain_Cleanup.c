/*
 * Entry: 004ccb17
 * Name: EditTerrain::Cleanup
 * Namespace: EditTerrain
 * Signature: void Cleanup(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::Cleanup(EditTerrain *this)

{
  TEXTURE *_Memory;
  
  Graphic_Buffer_Close(&this->gbMap);
  _Memory = this->txMap;
  if (_Memory != (TEXTURE *)0x0) {
    free(_Memory);
  }
  this->txMap = (TEXTURE *)0x0;
  return;
}
