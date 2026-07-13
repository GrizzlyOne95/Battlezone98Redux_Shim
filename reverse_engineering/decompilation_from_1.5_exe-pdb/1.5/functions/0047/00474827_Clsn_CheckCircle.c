/*
 * Entry: 00474827
 * Name: Clsn_CheckCircle
 * Namespace: Global
 * Signature: _OBJ76 * Clsn_CheckCircle(CIRCLE param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl Clsn_CheckCircle(CIRCLE param_1,_OBJ76 *param_2)

{
  tagENTITY *ptVar1;
  CIRCLE *pCVar2;
  int iVar3;
  CIRCLE local_10;
  
  ptVar1 = FirstCollidable();
  do {
    if (ptVar1 == (tagENTITY *)0x0) {
      return (_OBJ76 *)0x0;
    }
    if (ptVar1->obj76 != param_2) {
      pCVar2 = Entity_WorldCircle(&local_10,ptVar1);
      iVar3 = Clsn_CircleCircle(param_1,*pCVar2);
      if (iVar3 != 0) {
        return ptVar1->obj76;
      }
    }
    ptVar1 = NextCollidable();
  } while( true );
}
