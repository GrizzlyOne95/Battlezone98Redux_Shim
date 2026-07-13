/*
 * Entry: 0054d9c5
 * Name: CheckGDefaultsExceeded
 * Namespace: Global
 * Signature: int CheckGDefaultsExceeded(i76_graphicDetail * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckGDefaultsExceeded(i76_graphicDetail *param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  i76_graphicDetail *piVar9;
  i76_graphicDetail local_24 [2];
  
  piVar9 = GetMachineDefaults(local_24);
  uVar1 = piVar9->resolution;
  uVar2 = piVar9->clouds;
  uVar5 = piVar9->shadow;
  uVar7 = piVar9->terrain;
  uVar3 = piVar9->objDetail;
  uVar6 = piVar9->visibility;
  uVar8 = piVar9->terTex;
  uVar4 = piVar9->scrounge;
  if ((((((byte)uVar1 <= param_1->resolution) && (param_1->clouds <= (byte)uVar2)) &&
       (param_1->scrounge <= (byte)uVar4)) &&
      ((param_1->shadow <= (byte)uVar5 && (param_1->terrain <= (byte)uVar7)))) &&
     ((param_1->objDetail <= (byte)uVar3 &&
      ((param_1->visibility <= (byte)uVar6 && (param_1->terTex <= (byte)uVar8)))))) {
    return 0;
  }
  return 1;
}
