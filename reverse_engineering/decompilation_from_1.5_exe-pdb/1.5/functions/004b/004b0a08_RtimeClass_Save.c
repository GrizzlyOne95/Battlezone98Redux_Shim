/*
 * Entry: 004b0a08
 * Name: RtimeClass::Save
 * Namespace: RtimeClass
 * Signature: bool Save(_iobuf * param_1, SObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __cdecl RtimeClass::Save(_iobuf *param_1,SObject *param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 *puVar3;
  char *pcVar4;
  char *pcVar5;
  SObject *local_34;
  char local_30 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_34 = param_2;
  if (param_2->bDontSave == false) {
    puVar3 = (undefined4 *)(**(code **)(param_2->_padding_ + 0x10))();
    pcVar4 = (char *)*puVar3;
    pcVar5 = local_30;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      *pcVar5 = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    ::out(param_1,local_30,0x28,"name");
    out_ptr(param_1,&local_34,4,"sObject");
    uVar2 = (**(code **)(local_34->_padding_ + 0xc))(param_1);
  }
  else {
    uVar2 = 1;
  }
  return (bool)uVar2;
}
