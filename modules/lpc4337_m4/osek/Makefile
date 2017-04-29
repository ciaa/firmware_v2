# Copyright 2016, Pablo Ridolfi
# All rights reserved.
#
# This file is part of Workspace.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from this
#    software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

osek_PATH := modules/lpc4337_m4/osek

osek_SRC_FILES := $(wildcard $(osek_PATH)/src/cortexM4/*.c) \
                  $(wildcard $(osek_PATH)/src/cortexM4/*.S) \
                  $(wildcard $(osek_PATH)/src/*.c) \
                  $(wildcard $(PROJECT)/gen/src/cortexM4/*.c) \
                  $(wildcard $(PROJECT)/gen/src/*.c)

osek_INC_FOLDERS := $(osek_PATH)/inc $(osek_PATH)/inc/cortexM4 $(osek_PATH)/inc/cortexM4/lpc43xx \
                    $(PROJECT)/gen/inc $(PROJECT)/gen/inc/cortexM4

osek_SRC_FOLDERS := $(osek_PATH)/src $(osek_PATH)/src/cortexM4 \
                    $(PROJECT)/gen/src $(PROJECT)/gen/src/cortexM4

osek_GEN_FILES := $(wildcard $(osek_PATH)/gen/inc/Os_Internal_Cfg.h.php) \
                  $(wildcard $(osek_PATH)/gen/inc/Os_Cfg.h.php) \
                  $(wildcard $(osek_PATH)/gen/inc/cortexM4/Os_Internal_Arch_Cfg.h.php) \
                  $(wildcard $(osek_PATH)/gen/src/Os_Internal_Cfg.c.php) \
                  $(wildcard $(osek_PATH)/gen/src/Os_Cfg.c.php) \
                  $(wildcard $(osek_PATH)/gen/src/cortexM4/Os_Internal_Arch_Cfg.c.php)

SYMBOLS += -DCPU=lpc43xx -DUSING_OSEK_RTOS

