
void FUN_0083bcb2(undefined4 param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  char *local_24;
  int local_20 [7];
  
  local_20[6] = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar1 = *param_4;
  if ((cVar1 == '@') || (cVar1 == '=')) {
    local_24 = param_4 + 1;
  }
  else {
    local_24 = "binary string";
    if (cVar1 != '\x1b') {
      local_24 = param_4;
    }
  }
  local_28 = param_3;
  local_30 = param_1;
  iVar3 = 0;
  local_2c = param_2;
  local_20[3] = 0x61754c1b;
  local_20[4] = 0x4010051;
  local_20[5] = 0x80404;
  FUN_0083b798(&local_30,local_20,0xc);
  do {
    if (local_20[iVar3 + 3] != local_20[iVar3]) {
      FUN_0083bc6e(&local_30,"bad header");
      break;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 3);
  uVar2 = FUN_008309f4(param_1,&DAT_00870a60,2);
  FUN_0083bac1(&local_30,uVar2);
  FUN_0083e885();
  return;
}

