
void __fastcall FUN_004aeb80(_Order_node_base<enum_Concurrency::agent_status> *param_1)

{
  char cVar1;
  bool bVar2;
  float10 fVar3;
  float fVar4;
  
  if (*(int *)(param_1 + 0xf4) != 0) {
    if (*(float *)(param_1 + 0x290) <= 0.0) {
      cVar1 = FUN_00417dd0();
      if ((cVar1 == '\0') && (cVar1 = FUN_004aef60(), cVar1 != '\0')) {
        FUN_004ae9f0();
      }
      switch(*(undefined4 *)(param_1 + 0x298)) {
      case 0:
        FUN_0062e780(*(undefined4 *)(param_1 + 0xf4),0);
        break;
      case 1:
        fVar3 = (float10)FUN_00822d80();
        fVar4 = ((float)fVar3 - *(float *)(param_1 + 0x29c)) /
                (*(float *)(param_1 + 0x2a0) - *(float *)(param_1 + 0x29c));
        if (fVar4 < 1.0) {
          FUN_0062e780(*(undefined4 *)(param_1 + 0xf4),fVar4);
        }
        else {
          FUN_0062e780(*(undefined4 *)(param_1 + 0xf4),0x3f800000);
          *(undefined4 *)(param_1 + 0x298) = 2;
        }
        break;
      case 2:
        FUN_0062e780(*(undefined4 *)(param_1 + 0xf4),0x3f800000);
        break;
      case 3:
        fVar3 = (float10)FUN_00822d80();
        fVar4 = ((float)fVar3 - *(float *)(param_1 + 0x29c)) /
                (*(float *)(param_1 + 0x2a0) - *(float *)(param_1 + 0x29c));
        if (fVar4 < 1.0) {
          FUN_0062e780(*(undefined4 *)(param_1 + 0xf4),1.0 - fVar4);
        }
        else {
          FUN_0062e780(*(undefined4 *)(param_1 + 0xf4),0);
          *(undefined4 *)(param_1 + 0x298) = 0;
        }
      }
      bVar2 = Concurrency::_Order_node_base<enum_Concurrency::agent_status>::has_value(param_1);
      if (bVar2) {
        *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) =
             *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) | 0x400;
        *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) = *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) | 1;
      }
      else {
        if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x40000000) == 0) {
          *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) =
               *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0xfffffbff;
        }
        if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x30000000) == 0) {
          *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) =
               *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0xfffffffe;
        }
      }
    }
    else {
      fVar3 = (float10)FUN_0047b6f0(*(undefined4 *)(param_1 + 0x290),0x3f800000);
      FUN_0062e780(*(undefined4 *)(param_1 + 0xf4),(float)fVar3);
      if ((float)fVar3 < 1.0) {
        *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) =
             *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0xfffffbff;
        *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) =
             *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0xfffffffe;
      }
      else {
        *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) =
             *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) | 0x400;
        *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) = *(uint *)(*(int *)(param_1 + 0xf4) + 0x14) | 1;
      }
    }
  }
  return;
}

