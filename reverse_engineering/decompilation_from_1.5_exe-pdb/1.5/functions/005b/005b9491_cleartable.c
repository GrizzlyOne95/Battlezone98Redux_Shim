/*
 * Entry: 005b9491
 * Name: cleartable
 * Namespace: Global
 * Signature: void cleartable(GCObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl cleartable(GCObject *param_1)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int iVar3;
  int iVar4;
  int unaff_EDI;
  
  for (; in_EAX != 0; in_EAX = *(int *)(in_EAX + 0x18)) {
    iVar4 = *(int *)(in_EAX + 0x1c);
    if ((*(byte *)(in_EAX + 5) & 0x10) != 0) {
      while (iVar4 != 0) {
        iVar4 = iVar4 + -1;
        iVar1 = iscleared((lua_TValue *)0x0,unaff_EDI);
        if (iVar1 != 0) {
          *(undefined4 *)(extraout_EDX + 8) = 0;
        }
      }
    }
    iVar4 = 1 << (*(byte *)(in_EAX + 7) & 0x1f);
    if (iVar4 != 0) {
      iVar1 = iVar4 << 5;
      do {
        iVar1 = iVar1 + -0x20;
        iVar4 = iVar4 + -1;
        if ((*(int *)(*(int *)(in_EAX + 0x10) + iVar1 + 8) != 0) &&
           (((iVar2 = iscleared((lua_TValue *)0x1,unaff_EDI), iVar3 = extraout_EDX_00, iVar2 != 0 ||
             (iVar2 = iscleared((lua_TValue *)0x0,unaff_EDI), iVar3 = extraout_EDX_01, iVar2 != 0))
            && (*(undefined4 *)(iVar3 + 8) = 0, 3 < *(int *)(iVar3 + 0x18))))) {
          *(undefined4 *)(iVar3 + 0x18) = 0xb;
        }
      } while (iVar4 != 0);
    }
  }
  return;
}
