/*
 * Entry: 004c1980
 * Name: BoundingBox::DrawSphere
 * Namespace: BoundingBox
 * Signature: void DrawSphere(BoundingBox * this, VECTOR_3D * param_1, float param_2, MAT_3D * param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
BoundingBox::DrawSphere
          (BoundingBox *this,VECTOR_3D *param_1,float param_2,MAT_3D *param_3,long param_4)

{
  tagPOINT tVar1;
  undefined1 local_10 [12];
  
  if (param_3 == (MAT_3D *)0x0) {
    tVar1 = WorldToScreen(param_1,DisplayInterface::currentCamera,(float *)&param_3);
  }
  else {
    Vector_Transform((VECTOR_3D *)local_10,param_1,1,param_3);
    tVar1 = WorldToScreen((VECTOR_3D *)local_10,DisplayInterface::currentCamera,(float *)&param_3);
  }
  local_10._4_8_ = (undefined8)((float)param_3 * param_2 + (float)Float2Int);
  Graphic_Circle(DisplayInterface::currentBuffer,tVar1.x,tVar1.y,local_10._4_4_,0x10,param_4,
                 SOLID_PIXELS);
  return;
}
