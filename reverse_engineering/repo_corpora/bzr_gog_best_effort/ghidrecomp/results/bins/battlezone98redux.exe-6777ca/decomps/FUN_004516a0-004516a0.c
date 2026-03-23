
void FUN_004516a0(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_12c [4];
  undefined4 local_128;
  undefined4 local_124;
  undefined1 local_11c [4];
  int *local_118;
  undefined1 local_114 [64];
  undefined1 local_d4 [64];
  char local_94 [64];
  char local_54 [64];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846acb;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  local_128 = FUN_00446460(param_1,0x811c9dc5,uVar2);
  FUN_0044eb20(local_11c,&local_128);
  uVar3 = FUN_0044eaa0(local_12c);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    FUN_00588c30(param_1,local_114,local_d4,0x40,0x40);
    sprintf(local_54,"%.*s.odf",0x3b,local_114);
    local_118 = (int *)0x0;
    iVar4 = FUN_00481f10(local_54);
    if (iVar4 == 0) {
      FUN_007d6c70("ERROR: ParticleSimulateClass \"%s.odf\" does not exist\n",local_54);
    }
    else {
      FUN_00589430(local_54);
      local_8 = 0;
      uVar3 = FUN_00446460(local_54,0x811c9dc5);
      local_124 = FUN_00446460(local_d4,0x811c9dc5,uVar2,uVar3);
      FUN_00449f30(local_124,0x9899c12,local_94,0);
      if (local_94[0] == '\0') {
        FUN_007d6c70("ERROR: ParticleSimulateClass \"%s\" has no base class specified",param_1);
      }
      else {
        local_118 = (int *)FUN_004516a0(local_94);
        if (local_118 == (int *)0x0) {
          FUN_007d6c70("ERROR: ParticleSimulateClass \"%s\" cannot find base class \"%s\"",param_1,
                       local_94);
        }
        else {
          local_118 = (int *)(**(code **)(*local_118 + 4))(param_1);
        }
      }
      local_8 = 0xffffffff;
      FUN_00589530();
    }
  }
  else {
    FUN_0042da60();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

