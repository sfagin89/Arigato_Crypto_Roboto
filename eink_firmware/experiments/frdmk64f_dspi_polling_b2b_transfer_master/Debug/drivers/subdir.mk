################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dspi.c \
../drivers/fsl_ftfx_cache.c \
../drivers/fsl_ftfx_controller.c \
../drivers/fsl_ftfx_flash.c \
../drivers/fsl_ftfx_flexnvm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dspi.o \
./drivers/fsl_ftfx_cache.o \
./drivers/fsl_ftfx_controller.o \
./drivers/fsl_ftfx_flash.o \
./drivers/fsl_ftfx_flexnvm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dspi.d \
./drivers/fsl_ftfx_cache.d \
./drivers/fsl_ftfx_controller.d \
./drivers/fsl_ftfx_flash.d \
./drivers/fsl_ftfx_flexnvm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DFRDM_K64F -DFREEDOM -DMCUXPRESSO_SDK -DCPU_MK64FN1M0VLL12_cm4 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\board" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\source" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\utilities" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\drivers" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\device" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\component\uart" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\component\lists" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\CMSIS" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\frdmk64f\driver_examples\dspi\polling_b2b_transfer\master" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


