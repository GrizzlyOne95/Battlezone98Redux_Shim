
void FUN_00763ab0(void)

{
  uint uStack_968;
  undefined1 local_958 [16];
  undefined1 local_948 [12];
  int local_93c;
  undefined4 local_938;
  int *local_934;
  int *local_92c;
  int *local_928;
  int *local_924;
  uint local_920;
  char local_91a;
  char local_919;
  undefined1 local_918 [2304];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085d010;
  local_10 = ExceptionList;
  uStack_968 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_968;
  ExceptionList = &local_10;
  local_920 = 0;
  local_8 = 0;
  local_18 = uStack_968;
  while (local_93c = FUN_007508e0(), local_93c != 0) {
    local_92c = (int *)FUN_007508e0();
    local_928 = local_92c;
    local_91a = (**(code **)(*local_92c + 4))(&local_920,0);
    if (local_91a == '\0') break;
    if (0x900 < local_920) {
      local_920 = 0x900;
    }
    FUN_0073a530();
    local_938 = 0;
    local_934 = (int *)FUN_007508e0();
    local_924 = local_934;
    local_919 = (**(code **)(*local_934 + 8))(local_918,local_920,&local_938,local_948,0);
    if (local_919 != '\0') {
      FUN_0073a6e0(local_948);
      FUN_00758c90(local_918,local_920,local_958);
    }
  }
  FUN_00763c50();
  return;
}

