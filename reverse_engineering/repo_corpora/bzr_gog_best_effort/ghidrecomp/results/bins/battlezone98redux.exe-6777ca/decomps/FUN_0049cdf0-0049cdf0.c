
void __thiscall FUN_0049cdf0(int param_1,float param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  iVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0x3bc));
  if (iVar1 == 0) {
    FUN_005aed80();
  }
  else {
    *(float *)(param_1 + 0x304) = *(float *)(param_1 + 0x304) - param_2;
    if (0.0 < *(float *)(param_1 + 0x304) || *(float *)(param_1 + 0x304) == 0.0) {
      puVar2 = (undefined4 *)FUN_00462400();
      local_18 = *puVar2;
      local_14 = puVar2[1];
      local_10 = puVar2[2];
      local_c = puVar2[3];
      uVar3 = FUN_0045c4d0();
      FUN_00820180(&local_18,&local_18,1,uVar3);
      FUN_0049c0a0(&local_18,
                   *(float *)(param_1 + 0x304) / *(float *)(*(int *)(param_1 + 0x370) + 0x54));
    }
    else {
      FUN_0049cee0(iVar1);
    }
  }
  FUN_0083e885();
  return;
}

