/*
 * Entry: 0048142f
 * Name: GAS_ObjInfo
 * Namespace: Global
 * Signature: void GAS_ObjInfo(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl GAS_ObjInfo(_gas_object *param_1)

{
  int iVar1;
  int in_ECX;
  char *pcVar2;
  char *pcVar3;
  char local_98 [128];
  char local_18 [8];
  undefined1 local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = *(int *)(in_ECX + 0x5c);
  if (iVar1 == 0) {
    pcVar2 = "null";
    pcVar3 = local_18;
  }
  else {
    if ((*(int *)(iVar1 + 8) != 0x6c6c756e) || (*(int *)(iVar1 + 0xc) != 0)) {
      strncpy(local_18,(char *)(iVar1 + 8),8);
      local_10 = 0;
      goto LAB_0048148a;
    }
    pcVar3 = local_18 + 4;
    pcVar2 = " ID ";
    builtin_strncpy(local_18,"NULL",4);
  }
  *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
  pcVar3[4] = pcVar2[4];
LAB_0048148a:
  sprintf(local_98,"%16s %16s  %3d    %2d  go_flg(%4x) gc_flg(%4x)",in_ECX + 4,local_18,
          *(undefined4 *)(in_ECX + 0x34),*(undefined4 *)(in_ECX + 0x38),
          *(undefined4 *)(in_ECX + 0x78),*(undefined4 *)(in_ECX + 0x14));
  iVar1 = monoLine;
  monoLine = monoLine + 1;
  Mono_Line(mHdl,0,(short)iVar1,7,local_98);
  return;
}
