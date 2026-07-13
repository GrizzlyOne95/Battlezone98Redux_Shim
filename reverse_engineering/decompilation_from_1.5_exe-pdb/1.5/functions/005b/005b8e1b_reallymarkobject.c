/*
 * Entry: 005b8e1b
 * Name: reallymarkobject
 * Namespace: Global
 * Signature: void reallymarkobject(global_State * param_1, GCObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl reallymarkobject(global_State *param_1,GCObject *param_2)

{
  uchar uVar1;
  GCObject *pGVar2;
  
  while( true ) {
    uVar1 = (param_2->gch).tt;
    (param_2->gch).marked = (param_2->gch).marked & 0xfc;
    if (uVar1 == '\x04') {
      return;
    }
    if (uVar1 == '\x05') break;
    if (uVar1 == '\x06') {
      (param_2->h).metatable = (Table *)param_1->gray;
      goto LAB_005b8eb7;
    }
    if (uVar1 != '\a') {
      if (uVar1 == '\b') {
        (param_2->th).gclist = param_1->gray;
      }
      else {
        if (uVar1 != '\t') {
          if (uVar1 != '\n') {
            return;
          }
          if ((3 < (int)((param_2->h).metatable)->metatable) &&
             (pGVar2 = ((param_2->h).metatable)->next, ((pGVar2->gch).marked & 3) != 0)) {
            reallymarkobject(param_1,pGVar2);
          }
          if ((param_2->h).metatable != (Table *)&(param_2->h).node) {
            return;
          }
          (param_2->gch).marked = (param_2->gch).marked | 4;
          return;
        }
        (param_2->p).gclist = param_1->gray;
      }
      goto LAB_005b8eb7;
    }
    pGVar2 = (GCObject *)(param_2->h).metatable;
    (param_2->gch).marked = (param_2->gch).marked | 4;
    if ((pGVar2 != (GCObject *)0x0) && (((pGVar2->gch).marked & 3) != 0)) {
      reallymarkobject(param_1,pGVar2);
    }
    param_2 = (GCObject *)(param_2->h).array;
    if (((param_2->gch).marked & 3) == 0) {
      return;
    }
  }
  (param_2->h).gclist = param_1->gray;
LAB_005b8eb7:
  param_1->gray = param_2;
  return;
}
