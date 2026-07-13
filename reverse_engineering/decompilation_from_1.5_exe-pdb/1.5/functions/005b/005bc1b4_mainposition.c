/*
 * Entry: 005bc1b4
 * Name: mainposition
 * Namespace: Global
 * Signature: Node * mainposition(Table * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Node * __cdecl mainposition(Table *param_1,lua_TValue *param_2)

{
  int in_EAX;
  Node *pNVar1;
  byte bVar2;
  uint *in_EDX;
  uint uVar3;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  
  uVar3 = in_EDX[2];
  if (uVar3 == 1) {
    uVar3 = (1 << (*(byte *)(in_EAX + 7) & 0x1f)) - 1U & *in_EDX;
  }
  else {
    if (uVar3 == 2) {
      bVar2 = *(byte *)(in_EAX + 7);
    }
    else {
      if (uVar3 == 3) {
        pNVar1 = hashnum((Table *)*(undefined8 *)in_EDX,(double)CONCAT44(unaff_ESI,unaff_EDI));
        return pNVar1;
      }
      bVar2 = *(byte *)(in_EAX + 7);
      if (uVar3 == 4) {
        uVar3 = (1 << (bVar2 & 0x1f)) - 1U & *(uint *)(*in_EDX + 8);
        goto LAB_005bc20a;
      }
    }
    uVar3 = *in_EDX % ((1 << (bVar2 & 0x1f)) - 1U | 1);
  }
LAB_005bc20a:
  return (Node *)(uVar3 * 0x20 + *(int *)(in_EAX + 0x10));
}
