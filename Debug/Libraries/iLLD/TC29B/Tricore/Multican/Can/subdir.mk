################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC29B/Tricore/Multican/Can/IfxMultican_Can.c 

COMPILED_SRCS += \
./Libraries/iLLD/TC29B/Tricore/Multican/Can/IfxMultican_Can.src 

C_DEPS += \
./Libraries/iLLD/TC29B/Tricore/Multican/Can/IfxMultican_Can.d 

OBJS += \
./Libraries/iLLD/TC29B/Tricore/Multican/Can/IfxMultican_Can.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC29B/Tricore/Multican/Can/%.src: ../Libraries/iLLD/TC29B/Tricore/Multican/Can/%.c Libraries/iLLD/TC29B/Tricore/Multican/Can/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc29xb "-fC:/Users/simos/AURIX-v1.9.4-workspace/MULTICAN_RX_FIFO_1_KIT_TC297_TFT/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc29xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/Libraries\/iLLD\/TC29B\/Tricore\/Multican\/Can\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

Libraries/iLLD/TC29B/Tricore/Multican/Can/%.o: ./Libraries/iLLD/TC29B/Tricore/Multican/Can/%.src Libraries/iLLD/TC29B/Tricore/Multican/Can/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Libraries-2f-iLLD-2f-TC29B-2f-Tricore-2f-Multican-2f-Can

clean-Libraries-2f-iLLD-2f-TC29B-2f-Tricore-2f-Multican-2f-Can:
	-$(RM) ./Libraries/iLLD/TC29B/Tricore/Multican/Can/IfxMultican_Can.d ./Libraries/iLLD/TC29B/Tricore/Multican/Can/IfxMultican_Can.o ./Libraries/iLLD/TC29B/Tricore/Multican/Can/IfxMultican_Can.src

.PHONY: clean-Libraries-2f-iLLD-2f-TC29B-2f-Tricore-2f-Multican-2f-Can

