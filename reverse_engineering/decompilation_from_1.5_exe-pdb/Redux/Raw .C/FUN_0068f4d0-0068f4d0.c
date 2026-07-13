
void FUN_0068f4d0(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  undefined1 local_58 [8];
  undefined1 local_50 [8];
  char *local_48;
  char *local_44;
  char *local_40;
  char local_3b;
  char local_3a;
  undefined1 local_39;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_0093d164 != '\0') {
    FUN_004fbb60();
    FUN_0069e880(param_1,&DAT_0093d164,0,0,param_2,0);
    FUN_004fed90(&param_1,0);
    local_3b = FUN_004fbbf0(local_38,local_58);
    FUN_004180b0();
    if (local_3b != '\0') goto LAB_0068f618;
  }
  if (DAT_00937157 != '\0') {
    FUN_004fbb60();
    FUN_0069e880(param_1,&DAT_00937157,0,0,param_2,0);
    FUN_004fed90(&param_1,0);
    local_3a = FUN_004fbbf0(local_20,local_50);
    FUN_004180b0();
    if (local_3a != '\0') goto LAB_0068f618;
  }
  iVar2 = FUN_00481f10(param_2);
  if (iVar2 == 0) {
    *param_1 = '\0';
  }
  else {
    local_44 = param_2;
    local_40 = param_1;
    local_48 = param_1;
    do {
      cVar1 = *local_44;
      *local_40 = cVar1;
      local_44 = local_44 + 1;
      local_40 = local_40 + 1;
    } while (cVar1 != '\0');
    local_39 = 0;
  }
LAB_0068f618:
  FUN_0083e885();
  return;
}

