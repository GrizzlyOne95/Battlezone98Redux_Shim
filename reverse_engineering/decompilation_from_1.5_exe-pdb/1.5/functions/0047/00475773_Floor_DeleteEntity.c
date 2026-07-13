/*
 * Entry: 00475773
 * Name: Floor_DeleteEntity
 * Namespace: Global
 * Signature: void Floor_DeleteEntity(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Floor_DeleteEntity(tagENTITY *param_1)

{
  int iVar1;
  tagENTITY *extraout_ECX;
  wrap_struct *pwVar2;
  
  iVar1 = OwnsFloor(param_1->obj76);
  pwVar2 = FloorList;
  if (iVar1 != 0) {
    while( true ) {
      if (pwVar2 == (wrap_struct *)0x0) {
        return;
      }
      if (pwVar2->ptr == extraout_ECX) break;
      pwVar2 = pwVar2->next;
    }
    Floor_ClearEntity(extraout_ECX);
    DeleteWrapper(&FloorList,pwVar2);
  }
  return;
}
