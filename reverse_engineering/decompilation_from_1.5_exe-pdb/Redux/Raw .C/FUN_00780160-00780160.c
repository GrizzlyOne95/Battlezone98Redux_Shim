
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00780160(void)

{
  int iVar1;
  undefined2 *puVar2;
  undefined1 *puVar3;
  char *local_3068;
  uint local_3064;
  uint local_3060;
  uint local_305c;
  uint local_3058;
  uint local_3054;
  char *local_3050;
  uint local_304c;
  undefined2 *local_3048;
  char *local_3044;
  char *local_3040;
  int local_303c;
  int local_3038;
  undefined4 local_3034;
  int local_3030;
  char local_302a;
  char local_3029;
  undefined1 local_3028 [4096];
  undefined1 local_2028 [4096];
  char local_1028 [4096];
  char local_28 [32];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00829390(&DAT_02cc40c0);
  if (iVar1 == 0) {
    FUN_007d6830("Could not load terrain %s",&DAT_02cc40c0);
  }
  else {
    local_3030 = FUN_00787ac0("World","MusicTrack",0xffffffff,&DAT_02cc40c0);
    if (local_3030 < 0x11) {
      local_303c = 2;
      if (local_3030 == 0xc) {
        local_3034 = 0xffffffff;
      }
      else {
        local_3034 = 0xc;
      }
      local_3038 = 0x10;
    }
    else if (local_3030 < 0x1c) {
      local_303c = 0x11;
      if (local_3030 == 0x1b) {
        local_3034 = 0xffffffff;
      }
      else {
        local_3034 = 0x1b;
      }
      local_3038 = 0x1b;
    }
    else {
      local_3034 = 0xffffffff;
      local_303c = local_3030;
      local_3038 = local_3030;
    }
    local_303c = FUN_00787ac0("World","MusicLoopFirst",local_303c,&DAT_02cc40c0);
    local_3034 = FUN_00787ac0("World","MusicLoopSkip",local_3034,&DAT_02cc40c0);
    local_3038 = FUN_00787ac0("World","MusicLoopLast",local_3038,&DAT_02cc40c0);
    FUN_004377c0(local_3030,local_303c,local_3034,local_3038);
    FUN_00787a30("World","IntroMovie",&DAT_008a1ad8,local_1028,0x1000,&DAT_02cc40c0);
    local_3050 = local_1028;
    local_3040 = &DAT_00915530;
    puVar3 = &DAT_00915530;
    do {
      local_302a = *local_3050;
      *local_3040 = local_302a;
      local_3050 = local_3050 + 1;
      local_3040 = local_3040 + 1;
    } while (local_302a != '\0');
    FUN_00787a30("World","OutroMovie",&DAT_008a1ad8,local_1028,0x1000,&DAT_02cc40c0);
    local_3068 = local_1028;
    local_3044 = &DAT_00915558;
    do {
      local_3029 = *local_3068;
      *local_3044 = local_3029;
      local_3068 = local_3068 + 1;
      local_3044 = local_3044 + 1;
    } while (local_3029 != '\0');
    DAT_02cd94e4 = FUN_00787ac0("NormalView",&DAT_0088d780,0x4b0,&DAT_02cc40c0,&DAT_00915558,puVar3)
    ;
    FUN_0068a230(DAT_02cd94e4 / 100);
    DAT_008f05c8 = FUN_00787ac0("NormalView",&DAT_0089d424,0xffffffff,&DAT_02cc40c0);
    _DAT_008f0594 = FUN_00787ac0("NormalView",&DAT_0089d478,0xffffffff,&DAT_02cc40c0);
    DAT_02cd9122 = 0;
    _DAT_02cd9120 = 0;
    DAT_02cd510a = 0;
    _DAT_02cd5108 = 0;
    FUN_00787a30("Color","Palette",&DAT_008a1ad8,local_3028,0x1000,&DAT_02cc40c0);
    local_3048 = (undefined2 *)FUN_00481af0(local_3028);
    if (local_3048 != (undefined2 *)0x0) {
      iVar1 = FUN_00787ac0("NormalView","FogDirection",1,&DAT_02cc40c0);
      if (iVar1 == 0) {
        _DAT_02cd5108 = *local_3048;
        DAT_02cd510a = *(byte *)(local_3048 + 1);
        _DAT_02cd9120 = _DAT_02cd5108;
        DAT_02cd9122 = DAT_02cd510a;
      }
      else {
        _DAT_02cd5108 = *(undefined2 *)((int)local_3048 + 0x29d);
        DAT_02cd510a = *(byte *)((int)local_3048 + 0x29f);
        FUN_00787a30("Color",&DAT_0089d460,&DAT_008a1ad8,local_2028,0x1000,&DAT_02cc40c0);
        iVar1 = FUN_00481af0(local_2028);
        if (iVar1 == 0) {
          _DAT_02cd9120 = _DAT_02cd5108;
          DAT_02cd9122 = DAT_02cd510a;
        }
        else {
          puVar2 = (undefined2 *)((uint)*(byte *)(iVar1 + 0xdf) * 3 + (int)local_3048);
          _DAT_02cd9120 = *puVar2;
          DAT_02cd9122 = *(byte *)(puVar2 + 1);
          FUN_00481990(local_2028);
        }
      }
      FUN_00481990(local_3028);
    }
    FUN_00787a30("Color","FogColor",&DAT_008a1ad8,local_28,0x20,&DAT_02cc40c0);
    if (local_28[0] != '\0') {
      local_3054 = (uint)DAT_02cd9120;
      local_304c = (uint)DAT_02cd9121;
      local_3058 = (uint)DAT_02cd9122;
      iVar1 = sscanf(local_28,"\"%d %d %d\"",&local_3054,&local_304c,&local_3058);
      if (iVar1 < 1) {
        sscanf(local_28,"%d %d %d",&local_3054,&local_304c,&local_3058);
      }
      _DAT_02cd9120 = CONCAT11((undefined1)local_304c,(undefined1)local_3054);
      DAT_02cd9122 = (byte)local_3058;
    }
    FUN_00787a30("Color","SkyColor",&DAT_008a1ad8,local_28,0x20,&DAT_02cc40c0);
    if (local_28[0] != '\0') {
      local_3060 = (uint)DAT_02cd5108;
      local_3064 = (uint)DAT_02cd5109;
      local_305c = (uint)DAT_02cd510a;
      iVar1 = sscanf(local_28,"\"%d %d %d\"",&local_3060,&local_3064,&local_305c);
      if (iVar1 < 1) {
        sscanf(local_28,"%d %d %d",&local_3060,&local_3064,&local_305c);
      }
      _DAT_02cd5108 = CONCAT11((undefined1)local_3064,(undefined1)local_3060);
      DAT_02cd510a = (byte)local_305c;
    }
  }
  FUN_0083e885();
  return;
}

