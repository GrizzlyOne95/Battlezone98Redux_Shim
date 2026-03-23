
void FUN_004fdab0(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_68 [8];
  undefined4 local_60;
  char *local_5c;
  char *local_58;
  char local_51;
  undefined1 local_50 [24];
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00426a60(&DAT_02ceefe0,0);
  FUN_004fbb90(local_38);
  FUN_00426af0("auto.sav");
  FUN_00426af0("auto2.sav");
  FUN_004fbb60();
  FUN_004fbc40(local_20,local_68);
  cVar1 = FUN_004fbbf0(local_38,local_68);
  if (cVar1 == '\0') {
    local_60 = 0;
    FUN_004180b0();
    FUN_004180b0();
  }
  else {
    FUN_004fbc60(local_38,local_20,local_68);
    DAT_009467b4 = 0;
    FUN_00417fd0(local_50);
    local_5c = (char *)FUN_0041f870();
    local_58 = &DAT_00945708;
    puVar3 = &DAT_00945708;
    do {
      local_51 = *local_5c;
      *local_58 = local_51;
      local_5c = local_5c + 1;
      local_58 = local_58 + 1;
    } while (local_51 != '\0');
    ~basic_string<>(&DAT_00945708);
    FUN_0081e0c0("Auto Load Game: Run state set to bookmark\n");
    FUN_00434170(8);
    FUN_004fc490(&DAT_00945708,1);
    uVar2 = FUN_00572a70(&DAT_00915540);
    FUN_007647c0(uVar2);
    FUN_004180b0(puVar3,1);
    FUN_004180b0();
  }
  FUN_0083e885();
  return;
}

