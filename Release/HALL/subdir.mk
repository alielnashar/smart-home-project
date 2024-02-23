################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HALL/Keypad.c \
../HALL/LCD.c \
../HALL/eeprom.c 

OBJS += \
./HALL/Keypad.o \
./HALL/LCD.o \
./HALL/eeprom.o 

C_DEPS += \
./HALL/Keypad.d \
./HALL/LCD.d \
./HALL/eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
HALL/%.o: ../HALL/%.c HALL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


