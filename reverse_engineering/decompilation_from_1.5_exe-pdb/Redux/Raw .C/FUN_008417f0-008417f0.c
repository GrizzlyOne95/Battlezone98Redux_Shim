
void FUN_008417f0(char *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  longlong lVar1;
  uint uVar2;
  char *pcVar3;
  void *pvVar4;
  undefined4 local_21c;
  undefined4 local_218;
  void *local_214;
  undefined1 local_210 [512];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0086591b;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_21c;
  ExceptionList = &local_c;
  local_21c = param_3;
  local_218 = param_4;
  pcVar3 = param_1;
  if (param_2 == (char *)0x0) {
    do {
      param_2 = pcVar3;
      pcVar3 = param_2 + 1;
    } while (*param_2 != '\0');
  }
  if (param_1 != param_2) {
    uVar2 = ((int)param_2 - (int)param_1) * 3;
    if (uVar2 < 0x101) {
      FUN_00841a30(param_1,param_2,local_210,&local_10,param_3,param_4,
                   DAT_008e7000 ^ (uint)&stack0xfffffdd4);
    }
    else {
      lVar1 = (ulonglong)uVar2 * 2;
      pvVar4 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
      local_4 = 0;
      local_214 = pvVar4;
      FUN_00841a30(param_1,param_2,pvVar4,(void *)((int)pvVar4 + ((int)param_2 - (int)param_1) * 6),
                   local_21c,local_218);
      operator_delete__(pvVar4);
    }
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

