
void __fastcall FUN_004e8f50(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_3c [12];
  int local_30;
  int local_2c;
  char local_26;
  undefined1 local_25;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = param_1;
  if (*(int *)(param_1 + 8) != 0xd) {
    uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(local_24 + 0x18) = uVar2;
    if (((*(int *)(local_24 + 0x18) == 0) ||
        (cVar1 = FUN_004db510(*(undefined4 *)(local_24 + 0x18)), cVar1 != '\0')) ||
       (iVar3 = FUN_00417ca0(), iVar3 == 0)) {
      *(undefined4 *)(local_24 + 0xc) = 0xd;
    }
    else {
      local_26 = FUN_00603ad0();
      local_2c = *(int *)(local_24 + 8);
      if (local_2c == 5) {
        local_30 = *(int *)(*(int *)(local_24 + 0x10) + 0x230) + 0xc4;
        puVar4 = (undefined4 *)FUN_00440000(local_3c,0,0,0);
        local_20 = *puVar4;
        local_1c = puVar4[1];
        local_18 = puVar4[2];
        local_14 = local_20;
        local_10 = local_1c;
        local_c = local_18;
        FUN_00607110(local_24 + 200,local_24 + 0xe4);
        FUN_00606f70(&local_20);
        fVar5 = (float10)FUN_00447ed0(*(float *)(local_24 + 0xdc) * 0.2 +
                                      *(float *)(local_24 + 0xb0),0xbf800000,0x3f800000);
        *(float *)(local_24 + 0xb0) = (float)fVar5;
        *(undefined4 *)(local_30 + 4) = *(undefined4 *)(local_24 + 0xb0);
      }
      cVar1 = FUN_00608460();
      if (cVar1 == '\0') {
        if ((local_26 == '\0') ||
           (cVar1 = FUN_00462b60(*(undefined4 *)(local_24 + 0x10),*(undefined4 *)(local_24 + 0xd4),
                                 0x3e99999a,0x3f800000), cVar1 != '\0')) {
          local_25 = 0;
        }
        else {
          local_25 = 1;
        }
        FUN_00604130(local_25);
      }
      else {
        cVar1 = FUN_00608490();
        if (cVar1 != '\0') {
          FUN_006084c0();
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

