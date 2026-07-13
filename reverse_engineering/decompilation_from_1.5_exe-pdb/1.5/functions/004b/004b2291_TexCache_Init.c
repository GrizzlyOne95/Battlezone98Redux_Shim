/*
 * Entry: 004b2291
 * Name: TexCache_Init
 * Namespace: Global
 * Signature: void TexCache_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TexCache_Init(void)

{
  MACHINE_CAPS *pMVar1;
  int iVar2;
  ulong *puVar3;
  _texcache **pp_Var4;
  MACHINE_CAPS local_34;
  ulong local_1c [6];
  
  pMVar1 = GetMachineCaps(&local_34);
  puVar3 = local_1c;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = pMVar1->PhysicalRAM;
    pMVar1 = (MACHINE_CAPS *)&pMVar1->VideoRAM;
    puVar3 = puVar3 + 1;
  }
  hTexCacheHeap = (void *)0x1;
  hTextureHeap = (void *)0x1;
  purge_tail = (_texcache *)0x0;
  purge_head = (_texcache *)0x0;
  pp_Var4 = texcache;
  for (iVar2 = 0x6d; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pp_Var4 = (_texcache *)0x0;
    pp_Var4 = pp_Var4 + 1;
  }
  return;
}
