/*
 * Entry: 0054bc65
 * Name: GetMachineDefaults
 * Namespace: Global
 * Signature: i76_graphicDetail * GetMachineDefaults(i76_graphicDetail * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

i76_graphicDetail * __cdecl GetMachineDefaults(i76_graphicDetail *__return_storage_ptr__)

{
  uchar uVar1;
  uchar uVar2;
  uchar uVar3;
  
  uVar1 = GraphicDefaults[3].clouds;
  uVar2 = GraphicDefaults[3].lineskip;
  uVar3 = GraphicDefaults[3].cockpit;
  __return_storage_ptr__->resolution = GraphicDefaults[3].resolution;
  __return_storage_ptr__->clouds = uVar1;
  __return_storage_ptr__->lineskip = uVar2;
  __return_storage_ptr__->cockpit = uVar3;
  uVar1 = GraphicDefaults[3].objTex;
  uVar2 = GraphicDefaults[3].shadow;
  uVar3 = GraphicDefaults[3].terrain;
  __return_storage_ptr__->hardware = GraphicDefaults[3].hardware;
  __return_storage_ptr__->objTex = uVar1;
  __return_storage_ptr__->shadow = uVar2;
  __return_storage_ptr__->terrain = uVar3;
  uVar1 = GraphicDefaults[3].objDetail;
  uVar2 = GraphicDefaults[3].visibility;
  uVar3 = GraphicDefaults[3].terTex;
  __return_storage_ptr__->pit3D = GraphicDefaults[3].pit3D;
  __return_storage_ptr__->objDetail = uVar1;
  __return_storage_ptr__->visibility = uVar2;
  __return_storage_ptr__->terTex = uVar3;
  uVar1 = GraphicDefaults[3].scrounge;
  uVar2 = GraphicDefaults[3].road;
  uVar3 = GraphicDefaults[3].vehTex;
  __return_storage_ptr__->brightness = GraphicDefaults[3].brightness;
  __return_storage_ptr__->scrounge = uVar1;
  __return_storage_ptr__->road = uVar2;
  __return_storage_ptr__->vehTex = uVar3;
  return __return_storage_ptr__;
}
