/*
 * Entry: 00481903
 * Name: NewGASObject
 * Namespace: Global
 * Signature: _gas_object * NewGASObject(char * param_1, _OBJ76 * param_2, GAS_CTRL * param_3, _gas_object * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_gas_object * __cdecl
NewGASObject(char *param_1,_OBJ76 *param_2,GAS_CTRL *param_3,_gas_object *param_4)

{
  ulong *puVar1;
  char cVar2;
  uint uVar3;
  undefined4 *in_EAX;
  _gas_object *p_Var4;
  int iVar5;
  _gas_object *p_Var6;
  
  p_Var4 = malloc(0x84);
  p_Var4->next = firstSound;
  firstSound = p_Var4;
  InitGASObject(p_Var4);
  if (in_EAX != (undefined4 *)0x0) {
    p_Var6 = p_Var4;
    for (iVar5 = 0xb; p_Var6 = (_gas_object *)&p_Var6->gc, iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined4 *)((GAS_CTRL *)p_Var6)->name = *in_EAX;
      in_EAX = in_EAX + 1;
    }
  }
  if ((param_2 != (_OBJ76 *)0x0) && ((param_2->flags & 0x10) != 0)) {
    puVar1 = &(p_Var4->gc).flags;
    *puVar1 = *puVar1 | 0x400;
  }
  p_Var4->obj76 = param_2;
  if (param_2 == (_OBJ76 *)0x0) {
    p_Var4->objHandle = 0;
  }
  else {
    p_Var4->objHandle = (int)param_2->objHandle;
  }
  if (param_1 != (char *)0x0) {
    iVar5 = 4 - (int)param_1;
    do {
      cVar2 = *param_1;
      param_1[(int)p_Var4 + iVar5] = cVar2;
      param_1 = param_1 + 1;
    } while (cVar2 != '\0');
  }
  uVar3 = (p_Var4->gc).flags;
  if ((uVar3 & 6) == 0) {
    (p_Var4->gc).flags = uVar3 | 2;
  }
  return p_Var4;
}
