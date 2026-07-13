/*
 * Entry: 0044e40a
 * Name: WorldRect
 * Namespace: Global
 * Signature: void WorldRect(float param_1, float param_2, float param_3, float param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WorldRect(float param_1,float param_2,float param_3,float param_4,long param_5)

{
  long local_14;
  long local_10;
  long local_c;
  long local_8;
  
  (**(code **)(*(int *)WorldInterface::currentDisplay + 0x20))(param_1,param_2,&local_14,&local_8);
  (**(code **)(*(int *)WorldInterface::currentDisplay + 0x20))(param_3,param_4,&local_c,&local_10);
  Graphic_Rect_Filled(&Device.Viewport,local_14,local_10,local_c,local_8,param_5,SOLID_PIXELS);
  return;
}
