SET PATH=D:\Program Files\Keil_v5\ARM\ARMCC\Bin;D:\Program Files (x86)\VMware\VMware Workstation\bin\;D:\Program Files\Python39\Scripts\;D:\Program Files\Python39\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\mingw64\bin;D:\Program Files\Git\cmd;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\bin;C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\12.2 mpacbti-rel1\bin;C:\Renesas\10 2021.10\bin;C:\Users\�˼���������\AppData\Local\Microsoft\WindowsApps;D:\Program Files\JetBrains\CLion 2023.2.2\bin;;D:\Program Files\Microsoft VS Code\bin
SET CPU_TYPE=STM32F103RC
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\main.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_it.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\system_stm32f10x.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\oled.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\delay.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\sys.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\usart.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\bsp_key.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\bsp_timer.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\bsp_systick.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\bsp_led.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\bsp_dht11.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\display.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\bsp_generaltim.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\core_cm3.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "..\obj\startup_stm32f10x_hd._ia"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\misc.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_gpio.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_rcc.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_usart.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f10x_tim.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "..\OBJ\demo.lnp"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" "..\OBJ\demo.axf" --i32combined --output "..\OBJ\demo.hex"
