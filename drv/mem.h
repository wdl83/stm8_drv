#pragma once

#define M1(I1) (UINT8_C(1) << I1)
#define M2(I1, I2) (M1(I1) | UINT8_C(1) << I2)
#define M3(I1, I2, I3) (M2(I1, I2) | UINT8_C(1) << I3)
#define M4(I1, I2, I3, I4) (M3(I1, I2, I3) | UINT8_C(1) << I4)
#define M5(I1, I2, I3, I4, I5) (M4(I1, I2, I3, I4) | UINT8_C(1) << I5)
#define M6(I1, I2, I3, I4, I5, I6) (M5(I1, I2, I3, I4, I5) | UINT8_C(1) << I6)
#define M7(I1, I2, I3, I4, I5, I6, I7) (M6(I1, I2, I3, I4, I5, I6) | UINT8_C(1) << I7)
