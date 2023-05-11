################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IR_ODBIORNIK/ir.c 

OBJS += \
./IR_ODBIORNIK/ir.o 

C_DEPS += \
./IR_ODBIORNIK/ir.d 


# Each subdirectory must supply rules for building sources it contributes
IR_ODBIORNIK/%.o: ../IR_ODBIORNIK/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


