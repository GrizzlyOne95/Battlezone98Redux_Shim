/*
 * Entry: 004b25de
 * Name: find_texture
 * Namespace: Global
 * Signature: _texcache * find_texture(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_texcache * __cdecl find_texture(char *param_1)

{
  byte bVar1;
  ulong uVar2;
  _texcache *p_Var3;
  _texcache *p_Var4;
  int iVar5;
  byte *pbVar6;
  char *unaff_EBX;
  bool bVar7;
  
  uVar2 = thash(unaff_EBX);
  p_Var3 = texcache[uVar2];
  do {
    p_Var4 = p_Var3;
    pbVar6 = (byte *)param_1;
    if (p_Var3 == (_texcache *)0x0) {
      return (_texcache *)0x0;
    }
    do {
      bVar1 = p_Var4->name[0];
      bVar7 = bVar1 < *pbVar6;
      if (bVar1 != *pbVar6) {
LAB_004b2615:
        iVar5 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_004b261a;
      }
      if (bVar1 == 0) break;
      bVar1 = p_Var4->name[1];
      bVar7 = bVar1 < pbVar6[1];
      if (bVar1 != pbVar6[1]) goto LAB_004b2615;
      p_Var4 = (_texcache *)(p_Var4->name + 2);
      pbVar6 = pbVar6 + 2;
    } while (bVar1 != 0);
    iVar5 = 0;
LAB_004b261a:
    if (iVar5 == 0) {
      return p_Var3;
    }
    p_Var3 = p_Var3->next;
  } while( true );
}
