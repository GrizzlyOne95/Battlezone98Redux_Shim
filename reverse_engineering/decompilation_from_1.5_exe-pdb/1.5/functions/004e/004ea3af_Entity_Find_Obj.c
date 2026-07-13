/*
 * Entry: 004ea3af
 * Name: Entity_Find_Obj
 * Namespace: Global
 * Signature: _OBJ76 * Entity_Find_Obj(tagENTITY * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl Entity_Find_Obj(tagENTITY *param_1,long param_2)

{
  int *piVar1;
  OBJECT_CLASS_T OVar2;
  _OBJ76 *p_Var3;
  int iVar4;
  int aiStack_408 [257];
  
  p_Var3 = param_1->obj76;
  iVar4 = 0;
  do {
    OVar2 = p_Var3->class_id;
    aiStack_408[iVar4 + 1] = (int)p_Var3;
    iVar4 = iVar4 + 1;
    if (OVar2 == param_2) {
      return p_Var3;
    }
    p_Var3 = p_Var3->child;
    while (p_Var3 == (_OBJ76 *)0x0) {
      if (iVar4 == 0) {
        return (_OBJ76 *)0x0;
      }
      piVar1 = aiStack_408 + iVar4;
      iVar4 = iVar4 + -1;
      p_Var3 = *(_OBJ76 **)(*piVar1 + 0xa4);
    }
  } while( true );
}
