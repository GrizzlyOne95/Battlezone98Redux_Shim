/*
 * Entry: 00526b24
 * Name: LoadVehicle
 * Namespace: Global
 * Signature: long LoadVehicle(ObjectType * param_1, ENTITY_LOADER * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

long __cdecl LoadVehicle(ObjectType *param_1,ENTITY_LOADER *param_2,char *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  char local_6d4 [4];
  undefined1 local_6d0 [968];
  char local_308 [256];
  char local_208 [255];
  undefined4 uStack_109;
  undefined1 auStack_104 [252];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  memset(local_6d0,0,0x3c8);
  param_2->entData = local_6d0;
  _splitpath(param_3,local_6d4,local_308,(char *)((int)&uStack_109 + 1),local_208);
  puVar1 = &uStack_109;
  do {
    puVar3 = puVar1;
    puVar1 = (undefined4 *)((int)puVar3 + 1);
  } while (*(char *)((int)puVar3 + 1) != '\0');
  *(undefined4 *)((int)puVar3 + 1) = 0x6664762e;
  *(undefined1 *)((int)puVar3 + 5) = 0;
  iVar2 = ReadBWD2File((char *)((int)&uStack_109 + 1),VDFChunkDefs,0xe,param_2);
  return iVar2;
}
