/*
 * Entry: 004b24b6
 * Name: Texture_Init
 * Namespace: Global
 * Signature: void Texture_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Texture_Init(void)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  
  TexCache_Init();
  memset(tcache,0,0x1450);
  iVar3 = 0;
  uVar2 = 0;
  do {
    pcVar1 = tcache[0].group + uVar2 + 0x10;
    pcVar1[0] = -1;
    pcVar1[1] = -1;
    pcVar1[2] = -1;
    pcVar1[3] = -1;
    iVar3 = iVar3 + 1;
    *(int *)((int)tcache[0].size_dims + uVar2 + 0x10) = iVar3;
    uVar2 = uVar2 + 0x34;
  } while (uVar2 < 0x1450);
  tcache[99].next = -1;
  tcacheFree = 0;
  tcacheUsed = -1;
  return;
}
