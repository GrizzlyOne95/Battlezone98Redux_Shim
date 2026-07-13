/*
 * Entry: 0045f99e
 * Name: SetAIP
 * Namespace: Global
 * Signature: void SetAIP(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetAIP(char *param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  _loaded_aip *p_Var3;
  int iVar4;
  void *pvVar5;
  byte *pbVar6;
  int iVar7;
  char *pcVar8;
  bool bVar9;
  
  iVar7 = 0;
  if (param_1 == (char *)0x0) {
    current_aip[param_2] = -1;
    AISchedule_SwitchAIP(param_2,(void *)0x0);
  }
  else {
    bVar9 = loaded_aip_count == 0;
    if (0 < loaded_aip_count) {
      do {
        p_Var3 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar7);
        pbVar6 = (byte *)param_1;
        do {
          bVar1 = *pbVar6;
          bVar9 = bVar1 < (byte)p_Var3->name[0];
          if (bVar1 != p_Var3->name[0]) {
LAB_0045f9fb:
            iVar4 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
            goto LAB_0045fa00;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar6[1];
          bVar9 = bVar1 < (byte)p_Var3->name[1];
          if (bVar1 != p_Var3->name[1]) goto LAB_0045f9fb;
          pbVar6 = pbVar6 + 2;
          p_Var3 = (_loaded_aip *)(p_Var3->name + 2);
        } while (bVar1 != 0);
        iVar4 = 0;
LAB_0045fa00:
      } while ((iVar4 != 0) && (iVar7 = iVar7 + 1, iVar7 < loaded_aip_count));
      bVar9 = iVar7 == loaded_aip_count;
    }
    if (bVar9) {
      p_Var3 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar7);
      pcVar8 = param_1;
      do {
        cVar2 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        p_Var3->name[0] = cVar2;
        p_Var3 = (_loaded_aip *)(p_Var3->name + 1);
      } while (cVar2 != '\0');
      pvVar5 = AISchedule_LoadAIP(-1,param_1);
      p_Var3 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar7);
      p_Var3->aip = pvVar5;
      p_Var3 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar7);
      if (p_Var3->aip == (void *)0x0) {
        DEBUG_systemWarning("Could not load AIP \"%s\"");
      }
      loaded_aip_count = loaded_aip_count + 1;
    }
    p_Var3 = ExpandingArray<_loaded_aip>::operator[](&loaded_aips,iVar7);
    if (p_Var3->aip != (void *)0x0) {
      AISchedule_SwitchAIP(param_2,p_Var3->aip);
      current_aip[param_2] = iVar7;
    }
  }
  return;
}
