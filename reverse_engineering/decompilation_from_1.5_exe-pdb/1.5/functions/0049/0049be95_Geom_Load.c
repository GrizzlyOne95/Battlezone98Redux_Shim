/*
 * Entry: 0049be95
 * Name: Geom_Load
 * Namespace: Global
 * Signature: _GEOMETRY * Geom_Load(long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

_GEOMETRY * __cdecl Geom_Load(long64 param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  _GEOMETRY *p_Var4;
  _CACHE_INFO *p_Var5;
  uint uVar6;
  _CACHE_INFO *p_Var7;
  long unaff_EDI;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  uVar6 = 0;
  p_Var7 = (_CACHE_INFO *)0x0;
  iVar2 = 0;
  local_1c = 0;
  p_Var5 = gcache;
  do {
    if (p_Var5->data == (char *)0x0) {
      p_Var7 = p_Var5;
      if (iVar2 == gcacheCount) break;
    }
    else {
      iVar2 = iVar2 + 1;
      if (((int)p_Var5->id == (int)param_1) && (*(int *)((int)&p_Var5->id + 4) == param_1._4_4_)) {
        gcache[local_1c].refCount = gcache[local_1c].refCount + 1;
        return (_GEOMETRY *)gcache[local_1c].data;
      }
    }
    local_1c = local_1c + 1;
    uVar6 = uVar6 + 0x18;
    p_Var5 = p_Var5 + 1;
  } while (uVar6 < 0x6000);
  if (p_Var7 == (_CACHE_INFO *)0x0) {
    iVar2 = 0;
    p_Var7 = (_CACHE_INFO *)0x0;
    uVar6 = 0;
    do {
      if (((*(int *)((int)&gcache[0].data + uVar6) != 0) &&
          (*(int *)((int)&gcache[0].refCount + uVar6) < 1)) &&
         (iVar1 = *(int *)((int)&gcache[0].size + uVar6), iVar2 < iVar1)) {
        p_Var7 = (_CACHE_INFO *)((int)&gcache[0].id + uVar6);
        iVar2 = iVar1;
      }
      uVar6 = uVar6 + 0x18;
    } while (uVar6 < 0x6000);
    if (p_Var7 != (_CACHE_INFO *)0x0) {
      operator_delete__(p_Var7->data);
      gcacheCount = gcacheCount + -1;
      p_Var7->data = (char *)0x0;
    }
  }
  MakePrjFile(local_18,CONCAT44(0x6f65672e,param_1._4_4_),unaff_EDI);
  pcVar3 = zixReadFile(local_18,&local_1c);
  if (pcVar3 == (char *)0x0) {
    p_Var4 = (_GEOMETRY *)0x0;
  }
  else {
    p_Var4 = load_geometry(pcVar3);
    zixFree(pcVar3);
    gcacheCount = gcacheCount + 1;
    p_Var4->cache_info = p_Var7;
    p_Var7->id = param_1;
    p_Var7->size = local_1c;
    p_Var7->data = (char *)p_Var4;
    p_Var7->refCount = 1;
  }
  return p_Var4;
}
