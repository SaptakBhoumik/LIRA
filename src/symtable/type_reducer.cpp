#include "symtable/symtable.hpp"
#include "ast/ast.hpp"
#include <cstddef>
#include <iostream>
#include <unordered_set>

namespace LIRA {
TypeExprPtr reduce_type_expr(TypeExprPtr type, TypeSymTablePtr symtable){
    switch(type->get_kind()){
        case TypeExprKind::NamedTypeExpr:{
            auto named_type = std::dynamic_pointer_cast<NamedTypeExpr>(type);
            return symtable->lookup(named_type->get_name());//symtable stores reduced type expressions so we dont need to recursively reduce here 
        }
        case TypeExprKind::ArrayTypeExpr:{
            auto array_type = std::dynamic_pointer_cast<ArrayTypeExpr>(type);
            auto reduced_base_type = reduce_type_expr(array_type->get_base_type(), symtable);
            return std::make_shared<ArrayTypeExpr>(array_type->get_token(), reduced_base_type, array_type->get_size(), array_type->get_attributes());
        }
        case TypeExprKind::SIMDTypeExpr:{
            auto simd_type = std::dynamic_pointer_cast<SIMDTypeExpr>(type);
            auto reduced_base_type = reduce_type_expr(simd_type->get_base_type(), symtable);
            return std::make_shared<SIMDTypeExpr>(simd_type->get_token(), reduced_base_type, simd_type->get_size(), simd_type->get_attributes());
        }
        case TypeExprKind::StructTypeExpr:{
            auto struct_type = std::dynamic_pointer_cast<StructTypeExpr>(type);
            std::vector<TypeExprPtr> reduced_field_types;
            const auto& field_types = struct_type->get_fields();
            for(auto field_type : field_types) {
                reduced_field_types.push_back(reduce_type_expr(field_type, symtable));
            }
            return std::make_shared<StructTypeExpr>(struct_type->get_token(), reduced_field_types, struct_type->is_packed(), struct_type->get_attributes());
        }
        case TypeExprKind::FuncTypeExpr:{
            auto func_type = std::dynamic_pointer_cast<FuncTypeExpr>(type);
            std::vector<TypeExprPtr> reduced_param_types;
            const auto& param_types = func_type->get_param_types();
            for(const auto& param_type : param_types) {
                reduced_param_types.push_back(reduce_type_expr(param_type, symtable));
            }
            auto reduced_return_type = reduce_type_expr(func_type->get_return_type(), symtable);
            return std::make_shared<FuncTypeExpr>(func_type->get_token(), reduced_param_types, func_type->has_varargs(), reduced_return_type, func_type->get_attributes());
        }
        case TypeExprKind::AnyTypeExpr:{
            return type;
        }
    }
}
}