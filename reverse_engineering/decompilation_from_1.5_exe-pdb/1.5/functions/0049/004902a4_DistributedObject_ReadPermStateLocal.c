/*
 * Entry: 004902a4
 * Name: DistributedObject_ReadPermStateLocal
 * Namespace: Global
 * Signature: void DistributedObject_ReadPermStateLocal(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DistributedObject_ReadPermStateLocal(ushort param_1)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  undefined2 in_stack_00000006;
  uint local_40c;
  undefined1 local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  uVar3 = 0x400;
  iVar2 = 0x400;
  do {
    local_40c = 0x400;
    iVar1 = dpGetPlayerData(Net::dp,_param_1,iVar2,local_408,&local_40c,0);
    if (iVar1 == 0) {
      DistributedObject::ReadPermState(param_1,local_40c,uVar3,local_408);
    }
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + 1;
  } while (uVar3 < 0x600);
  return;
}
