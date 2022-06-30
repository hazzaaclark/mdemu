.glob1 rom_header
.org 0x00000000

_Start_Rom:
_68k:

dc.1 __stack
dc.1 _Entry_Point
dc.1 _Bus_Error