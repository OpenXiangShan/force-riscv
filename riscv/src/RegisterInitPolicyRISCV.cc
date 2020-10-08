//
// Copyright (C) [2020] Futurewei Technologies, Inc.
//
// FORCE-RISCV is licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
// FIT FOR A PARTICULAR PURPOSE.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <RegisterInitPolicyRISCV.h>
#include <VmasControlBlockRISCV.h>
#include <ChoicesFilter.h>
#include <Choices.h>
#include <Config.h>
#include <Constraint.h>
#include <Generator.h>
#include <Log.h>
#include <PageTable.h>
#include <PagingChoicesAdapter.h>
#include <Random.h>
#include <Register.h>
#include <UtilityFunctions.h>

#include <memory>

using namespace std;

/*!
  \file RegisterInitPolicyRISCV.cc
  \brief Code handling register or register fields with special randomization needs.
*/

namespace Force {

  void PpnInitPolicy::InitializeRegisterField(RegisterField* pRegField, const ChoiceTree* pChoiceTree) const
  {
    MemoryManager* mem_mgr = mpGenerator->GetMemoryManager();
    // Get the usable constraint specified in the variable.xml
    string var_name = EMemBankType_to_string(EMemBankType::Default) + " page table physical memory range";
    auto page_table_var = mpGenerator->GetVariable(var_name, EVariableType::String);
    ConstraintSet* usable_constr = new ConstraintSet(page_table_var);
    // Apply the physical address limit size constraint.
    uint64 max_phys = Config::Instance()->LimitValue(ELimitType::PhysicalAddressLimit);
    ConstraintSet phys_limit_constr(0, max_phys);
    usable_constr->ApplyConstraintSet(phys_limit_constr);
    std::unique_ptr<ConstraintSet> usable_constr_ptr(usable_constr);

    RootPageTable root_table;

    if (Config::Instance()->GetGlobalStateValue(EGlobalStateType::RV32) != 0)
      root_table.Setup(10, 31, 22, "", 2, 1);  // Sv32
    else
      root_table.Setup(9, 47, 39, "", 3, 3);   // Sv48
    uint32 tb_size = root_table.RootTableSize();

    SetupRootPageTableRISCV setup_page_table;
    setup_page_table.SetupRootPageTable(tb_size, mem_mgr, EMemBankType::Default, mpRegisterFile, pRegField->PhysicalRegisterName(), usable_constr_ptr.get());
  }

  uint64 PpnInitPolicy::RegisterFieldReloadValue(RegisterField* pRegField) const
  {
    LOG(notice) << "{PpnInitPolicy::RegisterFieldReloadValue} reloading " << pRegField->Name() << " of " << pRegField->PhysicalRegisterName() << endl;
    return 0;
  }

  void VlInitPolicy::InitializeRegister(Register* pRegister) const
  {
    SetRegisterInitialValue(pRegister, GetVlmax());
  }

  uint64 VlInitPolicy::RegisterReloadValue(Register* pRegister) const
  {
    LOG(notice) << "{VlInitPolicy::RegisterFieldReloadValue} reloading " << pRegister->Name() << endl;

    return GetVlmax();
  }

  uint64 VlInitPolicy::GetVlmax() const
  {
    const RegisterFile* reg_file = mpGenerator->GetRegisterFile();
    Register* vtype_reg = reg_file->RegisterLookup("vtype");
    RegisterField* vsew_field = vtype_reg->RegisterFieldLookup("VSEW");
    uint64 sew = (1 << vsew_field->FieldValue()) * 8;

    // TODO(Noah): Update this to account for fractional LMUL values when there is time to do so.
    RegisterField* vlmul_field = vtype_reg->RegisterFieldLookup("VLMUL");
    uint64 lmul = (1 << vlmul_field->FieldValue());

    uint64 vlmax = lmul * Config::Instance()->LimitValue(ELimitType::MaxPhysicalVectorLen) / sew;
    return vlmax;
  }

  void VstartInitPolicy::InitializeRegister(Register* pRegister) const
  {
    SetRegisterInitialValue(pRegister, 0);
  }

  uint64 VstartInitPolicy::RegisterReloadValue(Register* pRegister) const
  {
    LOG(notice) << "{VstartInitPolicy::RegisterFieldReloadValue} reloading " << pRegister->Name() << endl;

    return 0;
  }

  void VtypeInitPolicy::InitializeRegisterField(RegisterField* pRegField, const ChoiceTree* pChoiceTree) const
  {
    SetRegisterFieldInitialValue(pRegField, 0);
  }

  uint64 VtypeInitPolicy::RegisterFieldReloadValue(RegisterField* pRegField) const
  {
    LOG(notice) << "{VtypeInitPolicy::RegisterFieldReloadValue} reloading " << pRegField->Name() << " of " << pRegField->PhysicalRegisterName() << endl;

    return 0;
  }

}
