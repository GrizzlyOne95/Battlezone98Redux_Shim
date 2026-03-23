
int __thiscall FUN_005df0e0(undefined4 param_1,int param_2)

{
  float fVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  undefined4 *puVar6;
  float10 fVar7;
  
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    uVar3 = FUN_0045c4b0(param_1);
    if ((uVar3 & 0x201) == 0) {
      iVar4 = FUN_00417c70();
      cVar2 = FUN_004db510(param_2);
      if (cVar2 == '\0') {
        pfVar5 = (float *)FUN_00492d40();
        fVar1 = *pfVar5;
        puVar6 = (undefined4 *)(**(code **)(*(int *)(param_2 + 0x18) + 0xc))();
        puVar6 = (undefined4 *)
                 (**(code **)(*(int *)(iVar4 + 0x18) + 0xc))(*puVar6,puVar6[1],puVar6[2]);
        fVar7 = (float10)FUN_004620b0(*puVar6,puVar6[1],puVar6[2]);
        if (fVar1 * fVar1 < (float)fVar7) {
          param_2 = 0;
        }
      }
    }
    else {
      param_2 = 0;
    }
  }
  return param_2;
}

