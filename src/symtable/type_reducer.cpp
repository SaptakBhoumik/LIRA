#include "symtable/symtable.hpp"
#include "ast/ast.hpp"
#include <cstddef>
#include <iostream>
#include <unordered_set>

namespace LIRA {
namespace Utils {
IR::TypeExprPtr reduce_type_expr(IR::TypeExprPtr type, TypeSymTablePtr symtable){
    //TODO:What if the attribute contains type expression?We have to reduce them also
    switch(type->get_kind()){
        case IR::TypeExprKind::NamedTypeExpr:{
            auto named_type = std::dynamic_pointer_cast<IR::NamedTypeExpr>(type);
            return symtable->lookup(named_type->get_name());//symtable stores reduced type expressions so we dont need to recursively reduce here 
        }
        case IR::TypeExprKind::IntTypeExpr:
        case IR::TypeExprKind::FloatTypeExpr:
        case IR::TypeExprKind::VoidTypeExpr:
        case IR::TypeExprKind::PtrTypeExpr:
        case IR::TypeExprKind::MetaTypeExpr:{
            return type;//These types are already reduced and dont contain any named types inside them so we can just return them
        }
        case IR::TypeExprKind::LabelTypeExpr:{
            auto label_type = std::dynamic_pointer_cast<IR::LabelTypeExpr>(type);
            std::vector<IR::TypeExprPtr> reduced_param_types;
            const auto& param_types = label_type->get_params();
            for(const auto& param_type : param_types) {
                reduced_param_types.push_back(reduce_type_expr(param_type, symtable));
            }
            return std::make_shared<IR::LabelTypeExpr>(label_type->get_token(), reduced_param_types, label_type->get_attributes());
        }
        case IR::TypeExprKind::ArrayTypeExpr:{
            auto array_type = std::dynamic_pointer_cast<IR::ArrayTypeExpr>(type);
            auto reduced_base_type = reduce_type_expr(array_type->get_basetype(), symtable);
            return std::make_shared<IR::ArrayTypeExpr>(array_type->get_token(), reduced_base_type, array_type->get_size(), array_type->get_attributes());
        }
        case IR::TypeExprKind::SIMDTypeExpr:{
            auto simd_type = std::dynamic_pointer_cast<IR::SIMDTypeExpr>(type);
            auto reduced_base_type = reduce_type_expr(simd_type->get_basetype(), symtable);
            return std::make_shared<IR::SIMDTypeExpr>(simd_type->get_token(), reduced_base_type, simd_type->get_size(), simd_type->get_attributes());
        }
        case IR::TypeExprKind::StructTypeExpr:{
            auto struct_type = std::dynamic_pointer_cast<IR::StructTypeExpr>(type);
            std::vector<IR::TypeExprPtr> reduced_field_types;
            const auto& field_types = struct_type->get_fields();
            for(auto field_type : field_types) {
                reduced_field_types.push_back(reduce_type_expr(field_type, symtable));
            }
            return std::make_shared<IR::StructTypeExpr>(struct_type->get_token(), reduced_field_types, struct_type->is_packed(), struct_type->get_attributes());
        }
        case IR::TypeExprKind::FuncTypeExpr:{
            auto func_type = std::dynamic_pointer_cast<IR::FuncTypeExpr>(type);
            std::vector<IR::TypeExprPtr> reduced_param_types;
            const auto& param_types = func_type->get_param_types();
            for(const auto& param_type : param_types) {
                reduced_param_types.push_back(reduce_type_expr(param_type, symtable));
            }
            auto reduced_return_type = reduce_type_expr(func_type->get_return_type(), symtable);
            return std::make_shared<IR::FuncTypeExpr>(func_type->get_token(), reduced_param_types, func_type->has_varargs(), reduced_return_type, func_type->get_attributes());
        }
        case IR::TypeExprKind::AnyTypeExpr:{
            return type;
        }
    }
}
}
}