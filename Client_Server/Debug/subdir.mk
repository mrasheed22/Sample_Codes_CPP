################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Socket_Pro2.cpp 

OBJS += \
./Socket_Pro2.o 

CPP_DEPS += \
./Socket_Pro2.d 


# Each subdirectory must supply rules for building sources it contributes
Socket_Pro2.o: ../Socket_Pro2.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -w -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


