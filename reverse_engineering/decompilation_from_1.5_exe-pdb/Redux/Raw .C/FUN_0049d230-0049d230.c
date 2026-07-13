
void FUN_0049d230(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  float *pfVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  float10 fVar7;
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  float local_4c;
  undefined *local_48;
  float local_44;
  uint local_40;
  undefined4 local_3c;
  int local_38;
  char local_31;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_40 = FUN_0046fc10();
  if ((((*(int *)(local_30 + 0x228) == 0) && (local_40 != 0)) && (local_40 != 1)) &&
     (0x1a < local_40)) {
    uVar2 = FUN_00462490();
    FUN_0049cf90(param_1,uVar2);
    pfVar3 = (float *)FUN_0049c560();
    local_1c = pfVar3[1];
    local_10 = pfVar3[4];
    local_20 = *pfVar3 - 10.0;
    local_18 = pfVar3[2] - 10.0;
    local_14 = pfVar3[3] + 10.0;
    local_c = pfVar3[5] + 10.0;
    FUN_0049c5e0(&local_20,local_30 + 0x378);
    cVar1 = FUN_00466e50(&local_20,local_30 + 0x378);
    if (cVar1 == '\0') {
      cVar1 = FUN_004db510(DAT_00917afc);
      if (cVar1 != '\0') {
        FUN_0049c8d0();
      }
    }
    else {
      if (((*(int *)(*(int *)(local_30 + 0x370) + 0x14) == 0x434f4d4d) ||
          (*(int *)(*(int *)(local_30 + 0x370) + 0x14) == 0x54555252)) ||
         (*(int *)(*(int *)(local_30 + 0x370) + 0x14) == 0x53484c44)) {
        local_31 = '\0';
        uVar2 = FUN_0049c590(1,local_30 + 0x378);
        FUN_00820180(&local_2c,uVar2);
        local_48 = &DAT_025cce7c;
        FUN_00422170();
        puVar4 = (undefined4 *)FID_conflict_begin(local_58);
        local_3c = *puVar4;
        while( true ) {
          uVar2 = FID_conflict_end(local_50);
          cVar1 = FID_conflict_operator__(uVar2);
          if (cVar1 == '\0') break;
          piVar5 = (int *)FUN_00421ec0();
          local_38 = *piVar5;
          cVar1 = FUN_004db510(local_38);
          if (cVar1 != '\0') {
            puVar4 = (undefined4 *)(**(code **)(*(int *)(local_38 + 0x18) + 0xc))();
            fVar7 = (float10)FUN_004620b0(local_2c,local_28,local_24,*puVar4,puVar4[1],puVar4[2]);
            local_4c = (float)fVar7;
            iVar6 = (*(code *)**(undefined4 **)(local_38 + 0x18))();
            local_44 = *(float *)(iVar6 + 0x160);
            if (local_4c < local_44 * local_44) {
              local_31 = '\x01';
              break;
            }
          }
          FUN_0046b260(local_54,0);
        }
      }
      else {
        local_31 = '\x01';
      }
      if (local_31 == '\0') {
        cVar1 = FUN_004db510(DAT_00917afc);
        if (cVar1 != '\0') {
          FUN_0049c8b0();
        }
      }
      else {
        cVar1 = FUN_004db510(DAT_00917afc);
        if (cVar1 != '\0') {
          FUN_0049c890();
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

