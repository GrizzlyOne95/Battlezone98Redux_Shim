
void FUN_00691660(undefined4 *param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  undefined2 *puVar2;
  int iVar3;
  int local_41c;
  float local_418;
  int local_414;
  int local_40c;
  int aiStack_408 [128];
  float afStack_208 [128];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_40c = 0;
  local_414 = 0;
  do {
    puVar2 = (undefined2 *)(local_40c * 0xc + *(int *)(param_2 + 0xc));
    cVar1 = FUN_006a01f0(*puVar2,*(undefined1 *)param_1);
    if (cVar1 == '\0') {
      iVar3 = FUN_00691230(*puVar2,*param_1);
      if (iVar3 != 0) goto LAB_006916da;
      aiStack_408[local_40c] = 0;
    }
    else {
LAB_006916da:
      aiStack_408[local_40c] = 1;
      afStack_208[local_40c] = (float)*(int *)(puVar2 + 4) / (float)*(int *)(puVar2 + 2);
      if ((local_414 == 0) || (local_418 < afStack_208[local_40c])) {
        local_418 = afStack_208[local_40c];
        local_41c = local_40c;
      }
      local_414 = local_414 + 1;
    }
    local_40c = local_40c + 1;
    if (*(int *)(param_2 + 8) <= local_40c) {
      if (0 < local_414) {
        local_40c = 0;
        do {
          puVar2 = (undefined2 *)(local_40c * 0xc + *(int *)(param_2 + 0xc));
          if ((aiStack_408[local_40c] != 0) && ((local_40c != local_41c || (local_414 == 1)))) {
            FUN_00690df0(param_1,*puVar2,param_3,1,2,puVar2 + 4);
          }
          local_40c = local_40c + 1;
        } while (local_40c < *(int *)(param_2 + 8));
      }
      FUN_0083e885();
      return;
    }
  } while( true );
}

