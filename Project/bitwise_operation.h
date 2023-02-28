#ifndef bitwise
#define bitwise
// Set the desired bit to 1
#define Set_Bit(reg,bit) (reg|=(1<<bit))

// Set the desired bit to 0
#define Clear_Bit(reg,bit) (reg&=~(1<<bit))

// Toggle the desired bit
#define Toggle_Bit(reg,bit) (reg^=(1<<bit))

// return the desired bit
#define Get_Bit(reg,bit) (reg&(1<<bit))>>(bit)
#endif
