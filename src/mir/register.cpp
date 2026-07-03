#include "mir/register.hpp"

namespace LIRA {
namespace MIR{
LocalDestRegister::LocalDestRegister(std::string dest_register_name, IR::TypeExprPtr type,bool artificial, bool synthetic, bool nonnull, bool nopoison, 
                                     bool nnan, bool ninf, bool noalias, std::string original_name, std::string scope, std::size_t dereferenceable_bytes, 
                                     std::size_t alignment){
    this->dest_register_name = dest_register_name;
    this->type = type;

    this->artificial = artificial;
    this->synthetic = synthetic;
    this->nonnull = nonnull;
    this->nopoison = nopoison;
    this->nnan = nnan;
    this->ninf = ninf;
    this->noalias = noalias;

    this->original_name = original_name;
    this->scope = scope;
    this->dereferenceable_bytes = dereferenceable_bytes;
    this->alignment = alignment;    
}

void LocalDestRegister::set_alignment(std::size_t alignment){
    this->alignment = alignment;
}

std::string LocalDestRegister::get_dest_register_name() const{
    return dest_register_name;
}
IR::TypeExprPtr LocalDestRegister::get_type() const{
    return type;
}

bool LocalDestRegister::is_artificial() const{
    return artificial;
}
bool LocalDestRegister::is_synthetic() const{
    return synthetic;
}
bool LocalDestRegister::is_nonnull() const{
    return nonnull;
}
bool LocalDestRegister::is_nopoison() const{
    return nopoison;
}
bool LocalDestRegister::is_nnan() const{
    return nnan;
}
bool LocalDestRegister::is_ninf() const{
    return ninf;
}
bool LocalDestRegister::is_noalias() const{
    return noalias;
}

std::string LocalDestRegister::get_original_name() const{
    return original_name;
}
std::string LocalDestRegister::get_scope() const{
    return scope;
}
std::size_t LocalDestRegister::get_dereferenceable_bytes() const{
    return dereferenceable_bytes;
}
std::size_t LocalDestRegister::get_alignment() const{
    return alignment;
}

std::string LocalDestRegister::to_string() const{
    std::string result = type->to_string() + ":" + dest_register_name;
    if(artificial){
        result += " #[artificial]";
    }
    if(synthetic){
        result += " #[synthetic]";
    }
    if(nonnull){
        result += " #[nonnull]";
    }
    if(nopoison){
        result += " #[nopoison]";
    }
    if(nnan){
        result += " #[nnan]";
    }
    if(ninf){
        result += " #[ninf]";
    }
    if(noalias){
        result += " #[noalias]";
    }

    if(!original_name.empty()){
        result += " #[name(str:" + original_name + ")]";
    }
    if(!scope.empty()){
        result += " #[set_scope(scope:" + scope + ")]";
    }
    if(dereferenceable_bytes > 0){
        result += " #[dereferenceable_bytes(i64:" + std::to_string(dereferenceable_bytes) + ")]";
    }
    if(alignment > 0){
        result += " #[alignment(i64:" + std::to_string(alignment) + ")]";
    }
    return result;
}
}
}