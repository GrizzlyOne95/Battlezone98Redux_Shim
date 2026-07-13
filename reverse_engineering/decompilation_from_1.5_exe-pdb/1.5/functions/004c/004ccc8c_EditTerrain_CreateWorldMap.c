/*
 * Entry: 004ccc8c
 * Name: EditTerrain::CreateWorldMap
 * Namespace: EditTerrain
 * Signature: void CreateWorldMap(EditTerrain * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::CreateWorldMap(EditTerrain *this,int param_1)

{
  if (this->mapInitialized == 0) {
    CreateWorldMap(this);
  }
  this->mapInitialized = param_1;
  return;
}
