
void FUN_00583f30(undefined4 param_1)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined1 local_224 [4];
  undefined1 local_220 [4];
  undefined2 *local_21c;
  undefined2 *local_218;
  undefined1 local_214 [4];
  undefined2 *local_210;
  int *local_20c;
  undefined2 local_208;
  undefined2 local_206 [255];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_218 = &local_208;
  local_208 = 0x6f78;
  local_21c = local_206;
  local_210 = local_21c;
  FUN_0042d8c0(local_214);
  while( true ) {
    uVar3 = FID_conflict_begin(local_220);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    FUN_00438c10(local_224,0);
    puVar4 = (undefined4 *)FUN_0042de50();
    local_20c = (int *)*puVar4;
    cVar1 = FUN_00583dc0();
    if (cVar1 == '\0') {
      (**(code **)(*local_20c + 0xc))(param_1);
    }
    else {
      iVar5 = local_20c[0x1f];
      sVar2 = FUN_00572d90();
      if ((((short)iVar5 != sVar2) && (cVar1 = FUN_00583e00(), cVar1 != '\0')) &&
         (*(char *)(local_20c[3] + 0x5e) != '\0')) {
        *local_210 = (short)local_20c[0x1f];
        local_210[1] = *(undefined2 *)((int)local_20c + 0x7e);
        local_210 = local_210 + 2;
      }
      FUN_00585680();
    }
  }
  iVar5 = FUN_00572a70();
  if ((iVar5 != 0) && (local_21c < local_210)) {
    FUN_00575890(&local_208,(int)local_210 - (int)&local_208,1,1);
  }
  FUN_0083e885();
  return;
}

