
void FUN_006d45f0(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  tm *ptVar4;
  undefined1 local_98 [36];
  undefined8 local_74;
  size_t local_6c;
  char *local_68;
  int local_64 [9];
  tm local_40;
  char local_1c [20];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_74 = FUN_0056f760(0);
  piVar1 = (int *)FUN_006ba840(local_98,&local_74);
  piVar3 = local_64;
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = *piVar1;
    piVar1 = piVar1 + 1;
    piVar3 = piVar3 + 1;
  }
  piVar1 = local_64;
  ptVar4 = &local_40;
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    ptVar4->tm_sec = *piVar1;
    piVar1 = piVar1 + 1;
    ptVar4 = (tm *)&ptVar4->tm_min;
  }
  local_6c = strftime(local_1c,0x14,"%Y-%m-%d %H:%M:%S",&local_40);
  if (local_6c == 0) {
    local_68 = "Unknown";
  }
  else {
    local_68 = local_1c;
  }
  FUN_004bc590(param_1,local_68);
  FUN_0083e885();
  return;
}

