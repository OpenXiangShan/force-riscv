#
# Copyright (C) [2020] Futurewei Technologies, Inc.
#
# FORCE-RISCV is licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
# FIT FOR A PARTICULAR PURPOSE.
# See the License for the specific language governing permissions and
# limitations under the License.
#
control_items = [
                #{"fname":"api_genVA_01_force.py",                    "options":{"max-instr":50000,}, "generator" : {"--cfg" : "config/riscv.config", "--noiss":None, "--max-instr" : 50000}},
                #{"fname":"api_genVA_02_force.py",                    "options":{"max-instr":50000,}, "generator" : {"--cfg" : "config/riscv.config", "--noiss":None, "--max-instr" : 50000}},
                #{"fname":"api_genVA_01_force.py",                    "options":{"max-instr":50000,}, "generator" : {"--cfg" : "config/riscv.config", "--noiss":None, "--max-instr" : 50000, "--options":"\"PrivilegeLevel=1\""}},
                #{"fname":"api_genVA_02_force.py",                    "options":{"max-instr":50000,}, "generator" : {"--cfg" : "config/riscv.config", "--noiss":None, "--max-instr" : 50000, "--options":"\"PrivilegeLevel=1\""}},
                #{"fname":"api_genPA_01_force.py",                    "options":{"max-instr":50000,}, "generator" : {"--cfg" : "config/riscv.config", "--noiss":None, "--max-instr" : 50000, "--options":"\"PrivilegeLevel=1\""}},
                #{"fname":"api_genVAforPA_01_force.py",               "options":{"max-instr":50000,}, "generator" : {"--cfg" : "config/riscv.config", "--noiss":None, "--max-instr" : 50000, "--options":"\"PrivilegeLevel=1\""}},
                {"fname":"api_getPageInfo_01_force.py",               "options":{"max-instr":50000,}, "generator" : {"--cfg" : "config/riscv.config", "--noiss":None, "--max-instr" : 50000, "--options":"\"PrivilegeLevel=1\""}},
                #{"fname":"api_verifyVirtualAddress_01_force.py",     "options":{"max-instr":50000,}, "generator" : {"--cfg" : "config/riscv.config", "--noiss":None, "--max-instr" : 50000, "--options":"\"PrivilegeLevel=1\""}},
                #{"fname":"api_genFreePagesRange_01_force.py",        "options":{"max-instr":50000,}, "generator" : {"--cfg" : "config/riscv.config", "--noiss":None, "--max-instr" : 50000, "--options":"\"PrivilegeLevel=1\""}},
                {"fname":"Constraint_force.py",                      "generator" : {"--cfg" : "config/riscv.config", "--noiss":None,}},
                {"fname":"InitializeRegisterTest_force.py",          "generator" : {"--cfg" : "config/riscv.config", "--noiss":None,}},
                {"fname":"LoadImmediate_force.py",                   "generator" : {"--cfg" : "config/riscv.config", "--noiss":None,}},
                {"fname":"State_force.py",                           "generator" : {"--cfg" : "config/riscv.config", "--noiss":None,}},
                {"fname":"WriteRegisterTest_force.py",               "generator" : {"--cfg" : "config/riscv.config", "--noiss":None,}},
                #{ "fname":"*_force.py", "options":{"max-instr":50000,}, "generator":{,"--noiss":None,"--max-instr":50000,} },
                ]
