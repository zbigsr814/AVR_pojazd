################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include motor/subdir.mk
-include LCD/subdir.mk
-include IR/subdir.mk
-include ADC/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
17_ZDALNY_POJAZD.lss \

FLASH_IMAGE += \
17_ZDALNY_POJAZD.hex \

EEPROM_IMAGE += \
17_ZDALNY_POJAZD.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 17_ZDALNY_POJAZD.elf secondary-outputs

# Tool invocations
17_ZDALNY_POJAZD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,17_ZDALNY_POJAZD.map -mmcu=atmega8 -o "17_ZDALNY_POJAZD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

17_ZDALNY_POJAZD.lss: 17_ZDALNY_POJAZD.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 17_ZDALNY_POJAZD.elf  >"17_ZDALNY_POJAZD.lss"
	@echo 'Finished building: $@'
	@echo ' '

17_ZDALNY_POJAZD.hex: 17_ZDALNY_POJAZD.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 17_ZDALNY_POJAZD.elf  "17_ZDALNY_POJAZD.hex"
	@echo 'Finished building: $@'
	@echo ' '

17_ZDALNY_POJAZD.eep: 17_ZDALNY_POJAZD.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 17_ZDALNY_POJAZD.elf  "17_ZDALNY_POJAZD.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 17_ZDALNY_POJAZD.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 17_ZDALNY_POJAZD.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 17_ZDALNY_POJAZD.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
