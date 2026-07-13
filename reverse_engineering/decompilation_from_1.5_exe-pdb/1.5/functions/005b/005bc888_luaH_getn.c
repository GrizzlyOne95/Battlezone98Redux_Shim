/*
 * Entry: 005bc888
 * Name: luaH_getn
 * Namespace: Global
 * Signature: int luaH_getn(Table * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaH_getn(Table *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint unaff_ESI;
  
  uVar2 = param_1->sizearray;
  if ((uVar2 != 0) && (param_1->array[uVar2 - 1].tt == 0)) {
    uVar1 = 0;
    uVar4 = uVar2;
    while (1 < uVar4) {
      uVar3 = uVar1 + uVar2 >> 1;
      if (param_1->array[uVar3 - 1].tt == 0) {
        uVar2 = uVar3;
        uVar3 = uVar1;
      }
      uVar1 = uVar3;
      uVar4 = uVar2 - uVar3;
    }
    return uVar1;
  }
  if (param_1->node != &dummynode_) {
    uVar2 = unbound_search(param_1,unaff_ESI);
  }
  return uVar2;
}
