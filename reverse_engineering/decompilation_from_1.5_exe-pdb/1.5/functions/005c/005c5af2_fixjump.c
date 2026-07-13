/*
 * Entry: 005c5af2
 * Name: fixjump
 * Namespace: Global
 * Signature: void fixjump(FuncState * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl fixjump(FuncState *param_1,int param_2,int param_3)

{
  uint *puVar1;
  int in_EAX;
  uint uVar2;
  int in_ECX;
  uint uVar3;
  int *unaff_EDI;
  
  uVar2 = (in_EAX - in_ECX) - 1;
  puVar1 = (uint *)(*(int *)(*unaff_EDI + 0xc) + in_ECX * 4);
  uVar3 = (int)uVar2 >> 0x1f;
  if (0x1ffff < (int)((uVar2 ^ uVar3) - uVar3)) {
    luaX_syntaxerror((LexState *)unaff_EDI[3],"control structure too long");
  }
  *puVar1 = ((in_EAX - in_ECX) + 0x1fffe) * 0x4000 ^ *puVar1 & 0x3fff;
  return;
}
