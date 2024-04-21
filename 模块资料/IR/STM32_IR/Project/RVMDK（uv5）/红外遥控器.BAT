SET PATH=D:\Program Files\Keil_v5\ARM\ARMCC\Bin;D:\Program Files (x86)\VMware\VMware Workstation\bin\;D:\Program Files\Python39\Scripts\;D:\Program Files\Python39\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\mingw64\bin;D:\Program Files\Git\cmd;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\bin;C:\Program Files (x86)\Arm GNU Toolchain arm-none-eabi\12.2 mpacbti-rel1\bin;C:\Renesas\10 2021.10\bin;C:\Users\潘吉拉宝贝儿\AppData\Local\Microsoft\WindowsApps;D:\Program Files\JetBrains\CLion 2023.2.2\bin;;D:\Program Files\Microsoft VS Code\bin
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=红外遥控器
SET CPU_CLOCK=0x00B71B00
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "..\..\output\startup_stm32f10x_hd._ia"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\core_cm3.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\system_stm32f10x.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\misc.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_adc.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_bkp.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_can.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_cec.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_crc.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_dac.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_dbgmcu.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_dma.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_exti.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_flash.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_fsmc.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_gpio.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_i2c.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_iwdg.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_pwr.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_rcc.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_rtc.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_sdio.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_spi.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_tim.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_usart.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_wwdg.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\main.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\stm32f10x_it.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\bsp_led.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\bsp_timbase.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\sys.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\bsp_ir.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\..\output\bsp_usart_dma.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "..\..\Output\TIM—基本定时器定时.lnp"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" "..\..\Output\TIM—基本定时器定时.axf" --i32combined --output "..\..\Output\TIM—基本定时器定时.hex"
