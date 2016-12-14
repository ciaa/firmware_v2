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

lpcusblib_PATH := modules/lpc4337_m4/lpcusblib

lpcusblib_SRC_FILES += $(wildcard $(lpcusblib_PATH)/Drivers/USB/Class/Common/*.c) \
                       $(wildcard $(lpcusblib_PATH)/Drivers/USB/Class/Host/*.c) \
                       $(wildcard $(lpcusblib_PATH)/Drivers/USB/Core/*.c) \
                       $(wildcard $(lpcusblib_PATH)/Drivers/USB/Core/HAL/LPC18XX/*.c) \
                       $(wildcard $(lpcusblib_PATH)/Drivers/USB/Core/HCD/*.c) \
                       $(wildcard $(lpcusblib_PATH)/Drivers/USB/Core/HCD/EHCI/*.c) \

lpcusblib_SRC_FOLDERS += $(lpcusblib_PATH)/Drivers/USB/Class/Common \
                         $(lpcusblib_PATH)/Drivers/USB/Class/Host \
                         $(lpcusblib_PATH)/Drivers/USB/Core \
                         $(lpcusblib_PATH)/Drivers/USB/Core/HAL/LPC18XX \
                         $(lpcusblib_PATH)/Drivers/USB/Core/HCD \
                         $(lpcusblib_PATH)/Drivers/USB/Core/HCD/EHCI

lpcusblib_INC_FOLDERS += $(lpcusblib_PATH) \
                         $(lpcusblib_PATH)/Common \
                         $(lpcusblib_PATH)/Drivers/USB \
                         $(lpcusblib_PATH)/Drivers/USB/Class \
                         $(lpcusblib_PATH)/Drivers/USB/Class/Common \
                         $(lpcusblib_PATH)/Drivers/USB/Class/Host \
                         $(lpcusblib_PATH)/Drivers/USB/Core \
                         $(lpcusblib_PATH)/Drivers/USB/Core/HAL \
                         $(lpcusblib_PATH)/Drivers/USB/Core/HAL/LPC18XX \
                         $(lpcusblib_PATH)/Drivers/USB/Core/HCD \
                         $(lpcusblib_PATH)/Drivers/USB/Core/HCD/EHCI
