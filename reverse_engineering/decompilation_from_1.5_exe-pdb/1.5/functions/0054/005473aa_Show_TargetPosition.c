/*
 * Entry: 005473aa
 * Name: Show_TargetPosition
 * Namespace: Global
 * Signature: void Show_TargetPosition(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Show_TargetPosition(void)

{
  int iVar1;
  tagENTITY *ptVar2;
  SPHERE *pSVar3;
  SPHERE local_24;
  float local_14;
  float local_10;
  float local_c;
  float fStack_8;
  
  iVar1 = Mono_IsActive(Mono_Handle);
  if (iVar1 != 0) {
    ptVar2 = Get_Camera_Owner();
    pSVar3 = Entity_WorldSphere(&local_24,ptVar2);
    local_14 = (pSVar3->origin).x;
    local_10 = (pSVar3->origin).y;
    local_c = (pSVar3->origin).z;
    fStack_8 = pSVar3->radius;
    Mono_Line(Mono_Handle,1,0x11,7,"%7.2f  %7.2f  %7.2f");
  }
  return;
}
