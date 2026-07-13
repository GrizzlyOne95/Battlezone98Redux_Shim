
void FUN_005d7580(undefined4 param_1,int *param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 *puVar3;
  char *local_3c;
  char *local_38;
  char local_30 [40];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((char)param_2[1] == '\0') {
    puVar3 = (undefined4 *)(**(code **)(*param_2 + 0x10))();
    local_3c = (char *)*puVar3;
    local_38 = local_30;
    do {
      cVar2 = *local_3c;
      *local_38 = cVar2;
      local_3c = local_3c + 1;
      local_38 = local_38 + 1;
    } while (cVar2 != '\0');
    cVar2 = FUN_004cce90(param_1,local_30,0x28,&DAT_00879d2c,local_30);
    if ((cVar2 == '\0') || (cVar2 = FUN_004cf520(param_1,&param_2,4,"sObject"), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      (**(code **)(*param_2 + 0xc))(param_1);
    }
  }
  FUN_0083e885();
  return;
}

