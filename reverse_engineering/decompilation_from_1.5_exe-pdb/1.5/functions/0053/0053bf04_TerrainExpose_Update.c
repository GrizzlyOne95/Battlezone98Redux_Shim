/*
 * Entry: 0053bf04
 * Name: TerrainExpose::Update
 * Namespace: TerrainExpose
 * Signature: void Update(TerrainExpose * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TerrainExpose::Update(TerrainExpose *this,float param_1)

{
  tagENTITY *ptVar1;
  tagENTITY *ptVar2;
  
  ptVar1 = (tagENTITY *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0x2c))();
  ptVar2 = Get_Camera_Owner();
  if (ptVar2 == ptVar1) {
    TerrainExposeMode = 1;
  }
  return;
}
