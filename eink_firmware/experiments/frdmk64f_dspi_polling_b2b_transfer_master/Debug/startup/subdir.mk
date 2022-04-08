################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../startup/startup_mk64f12.c 

OBJS += \
./startup/startup_mk64f12.o 

C_DEPS += \
./startup/startup_mk64f12.d 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.c startup/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MK64FN1M0VLL12 -DFRDM_K64F -DFREEDOM -DMCUXPRESSO_SDK -DCPU_MK64FN1M0VLL12_cm4 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\board" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\source" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\utilities" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\drivers" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\device" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\component\uart" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\component\lists" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\CMSIS" -I"C:\Users\santi09\Documents\MCUXpressoIDE_11.5.0_7232\Arigato_Crypto_Roboto\eink_firmware\experiments\frdmk64f_dspi_polling_b2b_transfer_master\frdmk64f\driver_examples\dspi\polling_b2b_transfer\master" -O0 -fno-common -g3 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


