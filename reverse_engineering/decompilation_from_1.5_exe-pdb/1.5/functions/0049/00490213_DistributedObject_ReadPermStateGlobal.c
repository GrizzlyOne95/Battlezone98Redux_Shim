/*
 * Entry: 00490213
 * Name: DistributedObject_ReadPermStateGlobal
 * Namespace: Global
 * Signature: void DistributedObject_ReadPermStateGlobal(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DistributedObject_ReadPermStateGlobal(ushort param_1)

{
  uint uVar1;
  int iVar2;
  ushort uVar3;
  undefined2 in_stack_00000006;
  uint local_40c;
  undefined1 local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  uVar1 = 0x200;
  uVar3 = 0x200;
  if (0x200 < DistributedObject::dwGlobalIDCounter + 0x200) {
    do {
      local_40c = 0x400;
      iVar2 = dpGetPlayerData(Net::dp,_param_1,uVar1,local_408,&local_40c,0);
      if (iVar2 == 0) {
        DistributedObject::ReadPermState(param_1,local_40c,uVar3,local_408);
      }
      uVar3 = uVar3 + 1;
      uVar1 = (uint)uVar3;
    } while (uVar1 < DistributedObject::dwGlobalIDCounter + 0x200);
  }
  return;
}
