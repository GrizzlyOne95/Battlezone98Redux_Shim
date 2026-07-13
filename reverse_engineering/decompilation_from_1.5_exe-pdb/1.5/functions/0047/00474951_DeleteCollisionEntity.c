/*
 * Entry: 00474951
 * Name: DeleteCollisionEntity
 * Namespace: Global
 * Signature: void DeleteCollisionEntity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DeleteCollisionEntity(tagENTITY *param_1)

{
  int iVar1;
  wrap_struct **ppwVar2;
  wrap_struct *pwVar3;
  
  if ((param_1 == (tagENTITY *)0x0) || (param_1->obj76 == (_OBJ76 *)0x0)) {
    Trace("DeleteCollisionEntity called with NULL entity or obj76\n");
  }
  else {
    if (param_1->cType != CLSN_TYPE_NONCOLLIDE) {
      iVar1 = dynamic_object(param_1->obj76);
      ppwVar2 = &DynamicEnts;
      if (iVar1 == 0) {
        ppwVar2 = &StaticEnts;
      }
      for (pwVar3 = *ppwVar2; pwVar3 != (wrap_struct *)0x0; pwVar3 = pwVar3->next) {
        if (pwVar3->ptr == param_1) {
          if (pwVar3 == currentWrap) {
            NextCollidable();
          }
          if (param_1->cType == CLSN_TYPE_CHILDREN) {
            ClearObjCollision(param_1->obj76);
          }
          StillThere = 0;
          DeleteWrapper(ppwVar2,pwVar3);
          break;
        }
      }
    }
    Floor_DeleteEntity(param_1);
  }
  return;
}
