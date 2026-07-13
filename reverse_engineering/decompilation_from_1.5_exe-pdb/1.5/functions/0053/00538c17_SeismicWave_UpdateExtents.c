/*
 * Entry: 00538c17
 * Name: SeismicWave::UpdateExtents
 * Namespace: SeismicWave
 * Signature: void UpdateExtents(SeismicWave * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SeismicWave::UpdateExtents(SeismicWave *this)

{
  int unaff_EDI;
  int in_stack_00000004;
  
  Set_Rounding(unaff_EDI);
  (this->xMin).f =
       (double)(((float)*(double *)(this->_padding_ + 0x48) - *(float *)(this->_padding_ + 0x70)) *
                Terrain.Grid_Scale + (float)Float2Int);
  (this->zMin).f =
       (double)(((float)*(double *)(this->_padding_ + 0x58) - *(float *)(this->_padding_ + 0x70)) *
                Terrain.Grid_Scale + (float)Float2Int);
  Set_Rounding(unaff_EDI);
  (this->xMax).f =
       (double)((*(float *)(this->_padding_ + 0x70) + (float)*(double *)(this->_padding_ + 0x48)) *
                Terrain.Grid_Scale + (float)Float2Int);
  (this->zMax).f =
       (double)((*(float *)(this->_padding_ + 0x70) + (float)*(double *)(this->_padding_ + 0x58)) *
                Terrain.Grid_Scale + (float)Float2Int);
  Set_Rounding(in_stack_00000004);
  return;
}
