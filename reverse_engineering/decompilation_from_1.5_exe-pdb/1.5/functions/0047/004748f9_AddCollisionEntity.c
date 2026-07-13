/*
 * Entry: 004748f9
 * Name: AddCollisionEntity
 * Namespace: Global
 * Signature: void AddCollisionEntity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddCollisionEntity(tagENTITY *param_1)

{
  int iVar1;
  tagENTITY *unaff_ESI;
  
  InitCollisionType(unaff_ESI);
  if (param_1->cType != CLSN_TYPE_NONCOLLIDE) {
    iVar1 = dynamic_object(param_1->obj76);
    if (iVar1 == 0) {
      StaticEnts = NewWrapper(StaticEnts,(wrap_struct *)0x0,param_1);
      CreateBBoxe(param_1);
    }
    else {
      DynamicEnts = NewWrapper(DynamicEnts,(wrap_struct *)0x0,param_1);
    }
  }
  Floor_AddEntity(param_1);
  return;
}
