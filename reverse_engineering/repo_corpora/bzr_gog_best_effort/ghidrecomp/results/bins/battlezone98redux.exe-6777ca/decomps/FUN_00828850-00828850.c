
void FUN_00828850(undefined4 param_1)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  uint local_38;
  int local_2c;
  undefined1 local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00827640(local_28,param_1);
  pvVar1 = bsearch(local_28,DAT_009468cc,DAT_009468c0,0x20,FUN_00828260);
  if (pvVar1 == (void *)0x0) {
    sprintf(&DAT_009467c0,"Couldn\'t find file \"%.16s\"",param_1);
  }
  else {
    local_38 = 0xffffffff;
    iVar2 = FUN_00829680();
    local_2c = 1;
    while ((uVar3 = local_38, local_2c <= (int)(uint)*(ushort *)((int)pvVar1 + 0x10) &&
           (uVar3 = (uint)*(ushort *)((int)pvVar1 + local_2c * 2 + 0x10), iVar2 <= (int)uVar3))) {
      local_2c = local_2c + 1;
    }
    local_38 = uVar3;
    if (-1 < (int)local_38) {
      FUN_008296a0(local_38);
    }
  }
  FUN_0083e885();
  return;
}

